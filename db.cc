#include <iostream>
#include "include/seastarkv.hh"
#include "include/db.hh"
#include "include/reply_builder.hh"

using namespace std;

distributed<database> db;

future<> database::start() {
    for (int i = 0; i < NUM_CONTEXTS; i++)
        ht[i].table = NULL;
    return make_ready_future<>();
}

future<> database::stop() {
    return make_ready_future<>();
}

// C++ binding for getting value from database
future<foreign_ptr<lw_shared_ptr<db_val>>>
database::get_direct(uint32_t key, int tid)
{
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
