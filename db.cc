#include <iostream>
#include "include/seastarkv.hh"
#include "include/db.hh"
#include "include/reply_builder.hh"

using namespace std;

distributed<database> db;

// TODO(stutsman): This is gross, but the dumps synchronize badly enough to
// screwup output to the log file. We should do something simple that doesn't
// suffer from contention like this.
// Also: seastar seems to have a spinlock in the upstream documentation, but
// I couldn't find it in our current source tree.
typedef std::mutex Mutex;
typedef std::lock_guard<mutex> Lock;
Mutex dump_mutex{};

void
database::dump_stats()
{
    ts now = std::chrono::high_resolution_clock::now();
    ns interval_ns = now - last_dump;
    if (interval_ns.count() < 1e9)
        return;

    ns total_ns = now - first_dump;

    // Update all once-per-interval stats.
    stats.time = total_ns;
    stats.map_size = obj_map[0].size();

    shard_id id{engine().cpu_id()};

    auto diff = stats - prev_stats;

    {
      Lock _{dump_mutex};
      stats.dump(id, ">");
      diff.dump(id, "-");
    }

    prev_stats = stats;
    last_dump = now;
}

future<> database::start() {
    for (int i = 0; i < NUM_CONTEXTS; i++)
        ht[i].table = NULL;
    return make_ready_future<>();
}

future<> database::stop() {
    return make_ready_future<>();
}

// Set value on all cores
future<> database::set_all(redis_key rk, db_val val) {
//    obj_map[0].insert(std::make_pair(rk.key(), val));
    return make_ready_future<>();
}

// C++ version of set()
// TO DO: currently it just set all fields to 1, need to fix this 
future<scattered_message_ptr> database::set(const redis_key& rk, sstring& val) {
    db_val* v = ht_get(&ht[0], atoi(rk.key().c_str()));
    v->data = malloc(128);
    uint32_t* data = (uint32_t*)(v->data);
    for (int i = 0; i < 32; i++)
        data[i] = 1;

    return reply_builder::build(msg_ok);
}

// C++ version of get()
// TO DO: currently just read the first field, need to be able to specify which field to read.
future<scattered_message_ptr> database::get(const redis_key& key, int tid) {
    uint32_t* data;

    auto k = atoi(key.key().c_str());
//    for (int i = 0; i < 2048; i++) {
    db_val* v = ht_get(&ht[tid], k);
    if (!v) {
        sstring val = to_sstring(-1);
        return reply_builder::build(val, val.size());
    }
    data = (uint32_t*)(v->data);
    sstring val;
/*    for (unsigned i = 0; i < v->length; i++) {
        auto tmp = to_sstring(*data);
        val.append(tmp.c_str(), tmp.size());
        data++;
    }*/
//    k = (k + 1)%(671000-1);
//    }
    val = to_sstring(*data);

    return reply_builder::build(val, val.size());
}

// TO DO: not implemented for hash table delete
bool database::del(const redis_key& rk)
{
    obj_map[0].erase(rk.key());
    return 0;
}

// C++ binding for getting value from database
future<foreign_ptr<lw_shared_ptr<db_val>>>
database::get_direct(uint32_t key, int tid)
{
    stats.gets++;
//    dump_stats();
    using return_type = foreign_ptr<lw_shared_ptr<db_val>>;
    db_val* val = ht_get(&ht[tid], key);
    if (!val) {
        val = (db_val*)malloc(sizeof(db_val));
        val->length = 0;
    }
    return make_ready_future<return_type>(
        foreign_ptr<lw_shared_ptr<db_val>>(make_lw_shared<db_val>(*val)));
}

// C++ binding for setting key value
future<foreign_ptr<lw_shared_ptr<sstring>>>
database::set_direct(uint32_t key, db_val* val, int tid)
{
    using return_type = foreign_ptr<lw_shared_ptr<sstring>>;
    if (ht[tid].table == NULL)
            hashtable_init(&ht[tid], 1000*1000);
        ht_set(&ht[tid], val);

    const sstring v = msg_ok;
    return make_ready_future<return_type>(
        foreign_ptr<lw_shared_ptr<sstring>>(make_lw_shared<sstring>(v)));
}

// TO DO: not implemented for hash table 
future<foreign_ptr<lw_shared_ptr<sstring>>>
database::del_direct(const redis_key& rk, int tid)
{
    using return_type = foreign_ptr<lw_shared_ptr<sstring>>;
    obj_map[tid].erase(rk.key());
    const sstring v = "ok\n";
    return make_ready_future<return_type>(
        foreign_ptr<lw_shared_ptr<sstring>>(make_lw_shared<sstring>(v)));
}

// Get pointer to hash table
future<foreign_ptr<lw_shared_ptr<db_val**>>>
database::get_table(int tid)
{
    using return_type = foreign_ptr<lw_shared_ptr<db_val**>>;
    return make_ready_future<return_type>(
        foreign_ptr<lw_shared_ptr<db_val**>>(make_lw_shared<db_val**>(ht[tid].table)));
}

db_val** database::get_table_direct(int tid)
{
    return ht[tid].table;
}
// Obsolete code for btree version, not needed for hash table version
future<foreign_ptr<lw_shared_ptr<db_val>>>
database::get_iterator(const redis_key& rk, int tid)
{
    using return_type = foreign_ptr<lw_shared_ptr<db_val>>;
    it[tid] = obj_map[tid].find(rk.key());
    db_val val;
    if (it[tid] != obj_map[tid].end()) val = it[tid]->second;
    return make_ready_future<return_type>(
        foreign_ptr<lw_shared_ptr<db_val>>(make_lw_shared<db_val>(val)));
}

// Obsolete code for btree version, not needed for hash table version
future<foreign_ptr<lw_shared_ptr<db_val>>>
database::get_next(int tid)
{
    using return_type = foreign_ptr<lw_shared_ptr<db_val>>;
    db_val val;
    if (it[tid] != obj_map[tid].end()) val = it[tid]->second;
    ++(it[tid]);
    return make_ready_future<return_type>(
        foreign_ptr<lw_shared_ptr<db_val>>(make_lw_shared<db_val>(val)));
}
