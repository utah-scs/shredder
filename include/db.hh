#pragma once
#include "include/seastarkv.hh"
#include "include/reply_builder.hh"
#include <cstdio>
#include <fstream>
#include <chrono>

using namespace redis;
using namespace std;

class database;
extern distributed<database> db;
inline distributed<database>& get_database() {
    return db;
}
inline database* get_local_database() {
    return &db.local();
}

struct db_val {
    uint32_t key;
    struct db_val *next;
    void* data;
    uint32_t length;
}__attribute__((__packed__));

struct node
{
    void* data;
    node *next;
};

class database {
public:
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> ts;
    typedef std::chrono::duration<size_t, std::nano> ns;

    struct hashtable {
        uint32_t size;
        struct db_val **table;
    };

    typedef struct hashtable hashtable_t;
    typedef struct db_val db_val_t;

    void hashtable_init(hashtable_t* ht, uint32_t size) {
        ht->table = (db_val**)calloc(size, sizeof(void*));
        assert(ht->table != NULL);
        ht->size = size;
        return;
    }

    // Thomas Wang, Integer Hash Functions.
    // http://www.concentric.net/~Ttwang/tech/inthash.htm
    inline uint32_t get_hash(uint32_t key, uint32_t seed) {
        uint32_t hash = key;
        hash = hash ^ seed;
        hash = ~hash + (hash << 15);  // hash = (hash << 15) - hash - 1;
        hash = hash ^ (hash >> 12);
        hash = hash + (hash << 2);
        hash = hash ^ (hash >> 4);
        hash = hash * 2057;  // hash = (hash + (hash << 3)) + (hash << 11);
        hash = hash ^ (hash >> 16);
        return hash & 0x3fffffff;
    }

    void ht_set(hashtable_t* ht, db_val_t* val) {
        val->next = NULL;
        uint32_t hash = get_hash(val->key, 0) % ht->size;
        db_val_t* next = ht->table[hash];
        db_val_t* before = NULL;
        while (next != NULL && next->key != val->key) {
            before = next;
            next = before->next;
        }

        if (next != NULL) {
            free(next->data);
            next->data = val->data;
            next->length = val->length;
            free(val);
        } else if (before != NULL){
            before->next = val;
        } else
            ht->table[hash] = val;
    }

    db_val_t* ht_get(hashtable_t* ht, uint32_t key) {
        uint32_t hash = get_hash(key, 0) % ht->size;
        db_val_t* p = ht->table[hash];
        while (p && p->key != key)
            p = p->next;
        return p;
    }

    database()
    {
    }

    ~database() {
    }; 

    future<> set_all(redis_key rk, db_val val);
    future<scattered_message_ptr> set(const redis_key& rk, sstring& val);
    future<scattered_message_ptr> get(const redis_key& key, int tid);
    bool del(const redis_key& key);
    future<foreign_ptr<lw_shared_ptr<db_val>>> get_direct(uint32_t key, int tid);
    future<foreign_ptr<lw_shared_ptr<sstring>>> set_direct(uint32_t key, db_val* val, int tid);
    future<foreign_ptr<lw_shared_ptr<sstring>>> del_direct(const redis_key& rk, int tid);
    future<foreign_ptr<lw_shared_ptr<db_val>>> get_iterator(const redis_key& rk, int tid);
    future<foreign_ptr<lw_shared_ptr<db_val>>> get_next(int tid);
    future<foreign_ptr<lw_shared_ptr<db_val**>>> get_table(int tid);
    db_val** get_table_direct(int tid);

    future<> start();
    future<> stop();
    // One hashtable for each V8 context
    hashtable_t ht[NUM_CONTEXTS];
};
