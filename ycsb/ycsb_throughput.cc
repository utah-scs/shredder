#include "core/print.hh"
#include "core/reactor.hh"
#include "core/app-template.hh"
#include "core/future-util.hh"
#include "core/distributed.hh"
#include "core/semaphore.hh"
#include "core/future-util.hh"
#include <chrono>
#include <iostream>
#include <new>
#include <fstream>
#include <string>

using namespace seastar;
using namespace std;

vector<uint32_t> keys;

template<typename ElementType>
class Tub {
  public:
    /// The type of the object to be stored within the Tub.
    typedef ElementType element_type;

    /**
     * Default constructor: the object starts off uninitialized.
     */
    Tub()
        : occupied(false)
    {}

    /**
     * Construct an occupied Tub, whose contained object is initialized
     * with a copy of the given object.
     * \pre
     *      ElementType is CopyConstructible.
     * \param other
     *      Source of the copy.
     */
    Tub(const ElementType& other) // NOLINT
        : occupied(false)
    {
        construct(other);
    }

    /**
     * Copy constructor.
     * The object will be initialized if and only if the source of the copy is
     * initialized.
     * \pre
     *      ElementType is CopyConstructible.
     * \param other
     *      Source of the copy.
     */
    Tub(const Tub<ElementType>& other) // NOLINT
        : occupied(false)
    {
        if (other.occupied)
            construct(*other.object); // use ElementType's copy constructor
    }

    /**
     * Destructor: destroy the object if it was initialized.
     */
    ~Tub() {
        destroy();
    }

    /**
     * Assignment: destroy current object if initialized, replace with
     * source.  Result will be uninitialized if source is uninitialized.
     * \pre
     *      ElementType is Assignable.
     */
    Tub<ElementType>&
    operator=(const Tub<ElementType>& other) {
        if (this != &other) {
            if (other.occupied) {
                if (occupied) {
#if __GNUC__ && ((__GNUC__ >= 4 && __GNUC_MINOR__ >= 7) || (__GNUC__ > 4))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
                    *object = *other.object; // use ElementType's assignment
#if __GNUC__ && ((__GNUC__ >= 4 && __GNUC_MINOR__ >= 7) || (__GNUC__ > 4))
#pragma GCC diagnostic pop
#endif
                } else {
                    construct(*other.object);
                }
            } else {
                destroy();
            }
        }
        return *this;
    }

    /**
     * Initialize the object.
     * If the object was already initialized, it will be destroyed first.
     * \param args
     *      Arguments to ElementType's constructor.
     * \return
     *      A pointer to the newly initialized object.
     * \post
     *      The object is initialized.
     */
    template<typename... Args>
    ElementType*
    construct(Args&&... args) {
        destroy();
        new(object) ElementType(static_cast<Args&&>(args)...);
        occupied = true;
        return object;
    }

    /**
     * Destroy the object, leaving the Tub in the same state
     * as after the no-argument constructor.
     * If the object was not initialized, this will have no effect.
     * \post
     *      The object is uninitialized.
     */

    void
    destroy() {
        if (occupied) {
            object->~ElementType();
            occupied = false;
        }
    }

    /// See #get().
    const ElementType&
    operator*() const {
        return *get();
    }

    /// See #get().
    ElementType&
    operator*() {
        return *get();
    }

    /// See #get().
    const ElementType*
    operator->() const {
        return get();
    }

    /// See #get().
    ElementType*
    operator->() {
        return get();
    }

    /**
     * Return a pointer to the object.
     * \pre
     *      The object is initialized.
     */
    ElementType*
    get() {
        if (!occupied)
            return NULL;
        return object;
    }

    /// See #get().
    const ElementType*
    get() const {
        if (!occupied)
            return NULL;
        return object;
    }

    /**
     * Return whether the object is initialized.
     */
    operator bool() const {
        return occupied;
    }

  private:
    /**
     * A pointer to where the object is, if it is initialized.
     * This must directly precede #raw in the struct.
     */
    ElementType object[0];

    /**
     * A storage area to back the object while it is initialized.
     */
    char raw[sizeof(ElementType)];

    /**
     * Whether the object is initialized.
     */
    bool occupied;
};

template <typename... Args>
void http_debug(const char* fmt, Args&&... args) {
#if HTTP_DEBUG
    print(fmt, std::forward<Args>(args)...);
#endif
}

std::string
build_redis_command(const std::vector<std::string>& redis_cmd) {
  std::string cmd = "*" + std::to_string(redis_cmd.size()) + "\r\n";

  for (const auto& cmd_part : redis_cmd)
    cmd += "$" + std::to_string(cmd_part.length()) + "\r\n" + cmd_part + "\r\n";

  return cmd;
}

uint64_t
generateRandom()
{
    // Internal scratch state used by random_r 128 is the same size as
    // initstate() uses for regular random(), see manpages for details.
    // statebuf is malloc'ed and this memory is leaked, it could be a __thread
    // buffer, but after running into linker issues with large thread local
    // storage buffers, we thought better.
    enum { STATE_BYTES = 128 };
    static __thread char* statebuf;
    // random_r's state, must be handed to each call, and seems to refer to
    // statebuf in some undocumented way.
    static __thread random_data buf;

    if (statebuf == NULL) {
        int fd = open("/dev/urandom", O_RDONLY);
        assert(fd >= 0);
        unsigned int seed;
        ssize_t bytesRead = read(fd, &seed, sizeof(seed));
        close(fd);
        if (bytesRead != sizeof(seed)) {
            assert(bytesRead == sizeof(seed));
        }
        statebuf = static_cast<char*>(malloc(STATE_BYTES));
        initstate_r(seed, statebuf, STATE_BYTES, &buf);
    }

    // Each call to random returns 31 bits of randomness,
    // so we need three to get 64 bits of randomness.
    static_assert(RAND_MAX >= (1 << 31), "RAND_MAX too small");
    int32_t lo, mid, hi;
    random_r(&buf, &lo);
    random_r(&buf, &mid);
    random_r(&buf, &hi);
    uint64_t r = (((uint64_t(hi) & 0x7FFFFFFF) << 33) | // NOLINT
                  ((uint64_t(mid) & 0x7FFFFFFF) << 2)  | // NOLINT
                  (uint64_t(lo) & 0x00000003)); // NOLINT
    return r;
}

void
genRandomString(char* str, const int length) {
    static const char alphanum[] =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length; ++i) {
        str[i] = alphanum[generateRandom() % (sizeof(alphanum) - 1)];
    }
}

/**
 * Used to generate zipfian distributed random numbers where the distribution is
 * skewed toward the lower integers; e.g. 0 will be the most popular, 1 the next
 * most popular, etc.
 *
 * This class implements the core algorithm from YCSB's ZipfianGenerator; it, in
 * turn, uses the algorithm from "Quickly Generating Billion-Record Synthetic
 * Databases", Jim Gray et al, SIGMOD 1994.
 */
class ZipfianGenerator {
  public:
    /**
     * Construct a generator.  This may be expensive if n is large.
     *
     * \param n
     *      The generator will output random numbers between 0 and n-1.
     * \param theta
     *      The zipfian parameter where 0 < theta < 1 defines the skew; the
     *      smaller the value the more skewed the distribution will be. Default
     *      value of 0.99 comes from the YCSB default value.
     */
    explicit ZipfianGenerator(uint64_t n, double theta = 0.99)
        : n(n)
        , theta(theta)
        , alpha(1 / (1 - theta))
        , zetan(zeta(n, theta))
        , eta((1 - pow(2.0 / static_cast<double>(n), 1 - theta)) /
              (1 - zeta(2, theta) / zetan))
    {}

    /**
     * Return the zipfian distributed random number between 0 and n-1.
     */
    uint64_t nextNumber()
    {
        double u = static_cast<double>(generateRandom()) /
                   static_cast<double>(~0UL);
        double uz = u * zetan;
        if (uz < 1)
            return 0;
        if (uz < 1 + std::pow(0.5, theta))
            return 1;
        return 0 + static_cast<uint64_t>(static_cast<double>(n) *
                                         std::pow(eta*u - eta + 1.0, alpha));
    }

  private:
    const uint64_t n;       // Range of numbers to be generated.
    const double theta;     // Parameter of the zipfian distribution.
    const double alpha;     // Special intermediate result used for generation.
    const double zetan;     // Special intermediate result used for generation.
    const double eta;       // Special intermediate result used for generation.

    /**
     * Returns the nth harmonic number with parameter theta; e.g. H_{n,theta}.
     */
    static double zeta(uint64_t n, double theta)
    {
        double sum = 0;
        for (uint64_t i = 0; i < n; i++) {
            sum = sum + 1.0/(std::pow(i+1, theta));
        }
        return sum;
    }
};

/**
 * Used to generate a run workloads of a specific read/write distribution.  For
 * the most part, the workloads are modeled after the YCSB workload generator.
 */
class ycsb_client {
  public:
    /**
     * Constructor for the workload generator.
     *
     * \param workloadName
     *      Name of the workload to be generated.
     */
    ycsb_client(std::string workloadName, unsigned duration, unsigned total_conn, unsigned reqs_per_conn, unsigned objectSize)
        : workload(workloadName)
        , recordCount(262142)
//        , recordCount(4031)
        , recordSizeB(objectSize)
        , readPercent(100)
        , generator()
        , _duration(duration)
        , _conn_per_core(total_conn / smp::count)
        , _reqs_per_conn(reqs_per_conn)
    {
        if (workloadName == "YCSB-A") {
            readPercent = 50;
        } else if (workloadName == "YCSB-B") {
            readPercent = 95;
        } else if (workloadName == "YCSB-C") {
            readPercent = 100;
        } else if (workloadName == "WRITE-ONLY") {
            readPercent = 0;
        } else {
            printf("WARNING, Unknown workload type %s - Using default",
                workloadName.c_str());
        }

        // All lines that don't start with 'x.x ' get parsed by the CDF
        // generator.
        generator.construct(recordCount);
    }

    class connection {
    private:
        connected_socket _fd;
        input_stream<char> _read_buf;
        output_stream<char> _write_buf;
        ycsb_client* _ycsb_client;
        uint64_t _nr_done{0};
        uint64_t _nr_rec{0};
        unsigned _nr_count{0};

    public:
        uint64_t _client_id;
        connection(connected_socket&& fd, ycsb_client* client)
            : _fd(std::move(fd))
            , _read_buf(_fd.input())
            , _write_buf(_fd.output())
            , _ycsb_client(client)
            //, _client_id(id)
        {
            //setup().get();
        }

        uint64_t nr_done() {
            return _nr_done;
        }

        future<> setup() {
            std::string command = build_redis_command({"JS", "setup", to_string(_client_id)});
            return _write_buf.write(command).then([this] {
                return _write_buf.flush();
            }).then([this] {
                return _read_buf.read().then([this] (temporary_buffer<char> buf) {
                    return make_ready_future();
                });
            });
        }

        future<> do_req(int k) {
            //auto size = _ycsb_client->recordSizeB;
            const uint16_t keyLen = 8;
            char key[keyLen];
            //char value[size];
         
            uint64_t readThreshold = (~0UL / 100) * _ycsb_client->readPercent;
            memset(key, 0, keyLen);
            //string("workload").copy(key, 8);
            //to_string(engine().cpu_id()).copy(key + 8, 2);
            //to_string(_client_id).copy(key + 10, 4);
            //*reinterpret_cast<uint64_t*>(key) = _ycsb_client->generator->nextNumber();
            //*reinterpret_cast<uint64_t*>(key) = _ycsb_client->generator->nextNumber();
//            if (_nr_count == 0) {
//            } else
//                to_string(k).copy(key, 8);
            std::string command;
            //printf("%s\n", key);
 //           printf("before %u %lu\n", engine().cpu_id(), _client_id);
            if (_ycsb_client->workload == "YCSB-SCAN") {
                //command = build_redis_command({"GET", "1"});
                command = build_redis_command({"JS", "q2"});
            } else if (_ycsb_client->workload == "SETUP") {
                command = build_redis_command({"JS", "setup"});
                return _write_buf.write(command).then([this] {
                    return _write_buf.flush().then([this] {
                        return _read_buf.read().then([this] (temporary_buffer<char> buf) {
                           return make_ready_future();
                        });
                    });
                });
            } else if (generateRandom() <= readThreshold) {
                //command = build_redis_command({"GET", key, to_string(_client_id)});
                for (int i = 0; i < 8; i++) {
                    memset(key, 0, keyLen);
                    //to_string(_ycsb_client->generator->nextNumber()%4031).copy(key, 8);
                    //to_string(10).copy(key, 8);
                    //to_string(generateRandom()%4031).copy(key, 8);
                    //to_string(keys[generateRandom()%keys.size()]).copy(key, 8);
                    to_string(_ycsb_client->generator->nextNumber()).copy(key, 8);
                    command = command + build_redis_command({"GET", key});
                    //command = command + build_redis_command({"JS", "get", key});
                    //command = command + build_redis_command({"JS", "get_friend_list", key, "2"});
                    //command = command + build_redis_command({"JS", "predict"});
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    memset(key, 0, keyLen);
                    to_string(keys[generateRandom()%keys.size()]).copy(key, 8);
                    //to_string(_ycsb_client->generator->nextNumber()).copy(key, 8);
                    //command = command + build_redis_command({"GET", key});
                    command = command + build_redis_command({"JS", "get", key});
                    //command = command + build_redis_command({"JS", "get_friend_list", key, "2"});
                }

                //genRandomString(value, size);
                //command = build_redis_command({"SET", key, value, to_string(_client_id)});
            }
  
            std::chrono::steady_clock::time_point* s = new std::chrono::steady_clock::time_point();
            *s = steady_clock_type::now();

            return _write_buf.write(command).then([this, s, command] {
            return _write_buf.flush().then([this, s] {
                //return _read_buf.read_exactly(128*8).then([this, s] (temporary_buffer<char> buf) {
                return _read_buf.read().then([this, s] (temporary_buffer<char> buf) {
//                    printf("%s\n", buf.get());
                    std::string str = buf.get();
 //                   _nr_count++;
//                    if (_nr_count == 32) {
//                        _nr_count = 0;
                        _nr_done+=8;
/*                        auto f = steady_clock_type::now();
                        auto e = f - *s;
                        auto gap = static_cast<double>(e.count() / 1000.0);
                        print("%f\n", gap);
*/
//                    }
//            printf("after %u %lu\n", engine().cpu_id(), _client_id);

//                    std::string delimiter = "/r/n"; 
//                    size_t pos = str.find(delimiter);
//                    str.erase(0, pos + delimiter.length());
                    //cout << str;
                    if (_ycsb_client->done(_nr_done))
                        return make_ready_future();

                    // Busy wait to control offered load.
                    /*std::chrono::steady_clock::time_point* begin = new std::chrono::steady_clock::time_point();
                    *begin = steady_clock_type::now();
                    std::chrono::steady_clock::time_point* end = new std::chrono::steady_clock::time_point();
                    *end = steady_clock_type::now();
                    auto timegap = std::chrono::nanoseconds(*end - *begin).count();
                    while (timegap < 10000)
                    {
                        *end = steady_clock_type::now();
                        timegap = std::chrono::nanoseconds(*end - *begin).count();
                    }*/
                    
/*                    auto f = steady_clock_type::now();
                    auto e = f - *s;
                    auto gap = static_cast<double>(e.count() / 1000.0);
                    print("%f\n", gap);
*/
                    //usleep(220);
                    return do_req(0);
                    //return do_req(atoi(str.c_str()));
                });
            });
            });
        }
    };

    future<uint64_t> total_reqs() {
        print("Requests on cpu %2d: %ld\n", engine().cpu_id(), _total_reqs);
        return make_ready_future<uint64_t>(_total_reqs);
    }

    bool done(uint64_t nr_done) {
        return nr_done >= _reqs_per_conn;
    }

    future<> connect(ipv4_addr server_addr) {
        // Establish all the TCP connections first
        for (unsigned i = 0; i < _conn_per_core; i++) {
            engine().net().connect(make_ipv4_address(server_addr)).then([this] (connected_socket fd) {
                _sockets.push_back(std::move(fd));
                http_debug("Established connection %6d on cpu %3d\n", _conn_connected.current(), engine().cpu_id());
                auto conn = new connection(std::move(_sockets.back()), this);
                _connections.push_back(std::move(conn));
                _conn_connected.signal();
            }).or_terminate();
        }
        return _conn_connected.wait(_conn_per_core);
    }

    future<> setup_all()
    {
        unsigned i = 0;
        for (auto&& conn : _connections) {
            conn->_client_id = i + engine().cpu_id()*100;
            i++;
            conn->setup().then([this, conn] {
                _conn_setup.signal();
            });
        }
        // All finished
        return _conn_setup.wait(_conn_per_core);
    }

    /**
     * Run the workload and try to maintain a fix throughput.
     *
     * \param targetOps
     *      Throughput the workload should attempt to maintain; 0 means run at
     *      full throttle.
     */
    future<> run()
    {
        for (auto&& conn : _connections) {
            conn->do_req(0).then_wrapped([this, conn] (auto&& f) {
                _total_reqs += conn->nr_done();
                _conn_finished.signal();

                try {
                    f.get();
                } catch (std::exception& ex) {
                    print("request error: %s\n", ex.what());
                }
            });
        }
        // All finished
        return _conn_finished.wait(_conn_per_core);
    }

    future<> stop() {
        return make_ready_future();
    }

//private:
    std::string workload;
    unsigned recordCount;
    int recordSizeB;
    int readPercent;
    Tub<ZipfianGenerator> generator;
    unsigned _duration;
    unsigned _conn_per_core;
    unsigned _reqs_per_conn;
    std::vector<connected_socket> _sockets;
    std::vector<connection*> _connections;
    semaphore _conn_connected{0};
    semaphore _conn_finished{0};
    semaphore _conn_setup{0};
    uint64_t _total_reqs{0};
};

void load_fb_graph(void) {
    string line;
    ifstream fb_file("../facebook_combined.txt");
    if (fb_file) {
        uint32_t prev_key = 0;
        while (getline(fb_file, line))
        {
            string delimiter = " ";
            auto pos = line.find(delimiter);
            string k = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            uint32_t key = atoi(k.c_str());
            if (key == prev_key) {
                continue;
            }

            keys.push_back(prev_key);
            prev_key = key;
        }
        keys.push_back(prev_key);

        fb_file.close();
    } else
        cout << "Open file error.\n";
}

namespace bpo = boost::program_options;

int main(int ac, char** av) {
    load_fb_graph();
    app_template app;
    app.add_options()
        ("server,s", bpo::value<std::string>()->default_value("10.0.1.10:11211"), "Server address")
        ("conn,n", bpo::value<unsigned>()->default_value(100), "total connections")
        ("reqs,r", bpo::value<unsigned>()->default_value(1000), "reqs per connection")
        ("duration,d", bpo::value<unsigned>()->default_value(10), "duration of the test in seconds)")
        ("workload,w", bpo::value<std::string>()->default_value("YCSB-C"), "Type of YCSB workload")
        ("object_size,o", bpo::value<unsigned>()->default_value(100), "object size");

    return app.run(ac, av, [&app] () -> future<int> {
        auto& config = app.configuration();
        auto server = config["server"].as<std::string>();
        auto reqs_per_conn = config["reqs"].as<unsigned>();
        auto total_conn= config["conn"].as<unsigned>();
        auto duration = config["duration"].as<unsigned>();
        auto workload = config["workload"].as<std::string>();
        auto object_size = config["object_size"].as<unsigned>();

        if (total_conn % smp::count != 0) {
            print("Error: conn needs to be n * cpu_nr\n");
            return make_ready_future<int>(-1);
        }

        auto ycsb_clients = new distributed<ycsb_client>;

        std::chrono::steady_clock::time_point* started = new std::chrono::steady_clock::time_point();
        print("========== ycsb_client ============\n");
        print("Server: %s\n", server);
        print("Connections: %u\n", total_conn);
        print("Requests/connection: %s\n", reqs_per_conn == 0 ? "dynamic (timer based)" : std::to_string(reqs_per_conn));

        return ycsb_clients->start(std::move(workload), std::move(duration), std::move(total_conn), std::move(reqs_per_conn), std::move(object_size)).then([ycsb_clients, server] {
            return ycsb_clients->invoke_on_all(&ycsb_client::connect, ipv4_addr{server});
        }).then([ycsb_clients] {
            return ycsb_clients->invoke_on_all(&ycsb_client::setup_all);
        }).then([ycsb_clients, started] {
            *started = steady_clock_type::now();
            return ycsb_clients->invoke_on_all(&ycsb_client::run);
        }).then([ycsb_clients] {
            return ycsb_clients->map_reduce(adder<uint64_t>(), &ycsb_client::total_reqs);
        }).then([ycsb_clients, started] (auto total_reqs) {
           auto finished = steady_clock_type::now();
           auto elapsed = finished - *started;
           auto secs = static_cast<double>(elapsed.count() / 1000000000.0);
           print("Total cpus: %u\n", smp::count);
           print("Total requests: %u\n", total_reqs);
           print("Total time: %f\n", secs);
           print("Requests/sec: %f\n", static_cast<double>(total_reqs) / secs);
           print("==========     done     ============\n");
           return ycsb_clients->stop().then([ycsb_clients] {
               // FIXME: If we call engine().exit(0) here to exit when
               // requests are done. The tcp connection will not be closed
               // properly, becasue we exit too earily and the FIN packets are
               // not exchanged.
                delete ycsb_clients;
                return make_ready_future<int>(0);
           });
        });

            return seastar::make_ready_future<int>(0);
    });
}
