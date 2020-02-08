#include "include/seastarkv.hh"
#include "include/net_server.hh"
#include "include/req_server.hh"
#include "include/db.hh"
#include <sys/resource.h>

#define PLATFORM "seastar"
#define VERSION "v1.0"
#define VERSION_STRING PLATFORM " " VERSION

using namespace seastar;

int main(int argc, char** argv) {
    using namespace v8;
    char* tmp[3];
    const char* a1 = "seastarkv";
    const char* a2 = "--max-old-space-size=100000";
    tmp[0] = (char*)a1;
    tmp[1] = (char*)a2;
    char** opt = (char**)&tmp;

    V8::InitializeICUDefaultLocation(argv[0]);
    V8::InitializeExternalStartupData(argv[0]);
    std::unique_ptr<Platform> platform = platform::NewDefaultPlatform();
    V8::InitializePlatform(platform.get());
    V8::Initialize();

    int c = 2;
    V8::SetFlagsFromCommandLine(&c, opt, true);
    v8::internal::FLAG_expose_gc = true;
    v8::internal::FLAG_allow_natives_syntax = true;
    v8::internal::FLAG_max_old_space_size = 100000;

    seastar::app_template app;
    return app.run_deprecated(argc, argv, [&] {
        return async([argc, argv] () {
            auto& net_server = get_net_server();
            auto& req_server = get_req_server();
            auto& db = get_database();

            engine().at_exit([&] { return net_server.stop(); });
            engine().at_exit([&] { return req_server.stop(); });
            engine().at_exit([&] { return db.stop(); });

            db.start().then([&] {
                return db.invoke_on_all(&database::start);
            }).get();

            net_server.start().then([&] {
                return net_server.invoke_on_all(&network_server::start);
            }).get();

            req_server.start(argv).then([&req_server] {
                // Start JS thread on all cores
                return req_server.invoke_on_all(&req_service::js);
            }).get();
       });
    });
    V8::Dispose();
    V8::ShutdownPlatform();
    delete platform.get();
}
