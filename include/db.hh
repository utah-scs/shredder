#pragma once
#include "include/seastarkv.hh"
#include "include/reply_builder.hh"
#include "btree/btree.h"
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
    void* list;
    uint32_t length;
}__attribute__((__packed__));

typedef btree::btree_map<sstring, db_val> MyMap;

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

    class stats {
       public:
        ns time;
        ssize_t gets;
        ssize_t sets;
        ssize_t map_size;

        stats()
          : time{}
          , gets{}
          , sets{}
          , map_size{}
        {
        }

        stats operator-(const stats& other) const {
            stats out = *this;
            out.time -= other.time;
            out.gets -= other.gets;
            out.sets -= other.sets;
            out.map_size -= other.map_size;
            return out;
        }

        void dump(shard_id id, const std::string& prefix) const {
            //static std::atomic<shard_id> next{0};
            //while (next != id);
            std::cerr
              << prefix << " " << id
                << " time " << time.count()/1e9 << std::endl
              << prefix << " " << id
                << " gets " << gets << std::endl
              << prefix << " " << id
                 << " sets " << sets << std::endl
              << prefix << " " << id
                 << " map_size " << map_size << std::endl
             ;
            //next++;
        }
    };

    database()
      : first_dump{}
      , last_dump{}
    {
      ts now = std::chrono::high_resolution_clock::now();
      last_dump = first_dump = now;
    }

    ~database() {
    }; 

    void dump_stats();

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
    hashtable_t ht[NUM_CONTEXTS];
private:
    //Btree map, currently not used.
    MyMap obj_map[NUM_CONTEXTS];
    MyMap::const_iterator it[NUM_CONTEXTS];
    node *head[NUM_CONTEXTS];

    ts first_dump;
    ts last_dump;

    stats prev_stats;
    stats stats;
};
