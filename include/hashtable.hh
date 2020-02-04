#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

struct db_val {
    uint32_t key;
    struct db_val *next;
    void* data;
    void* list;
    size_t length;
};

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
    uint32_t hash = get_hash(val->key, 0) % ht->size;
    db_val_t* next = ht->table[hash];
    db_val_t* before = NULL;
    while (next != NULL && next->key != val->key) {
        cout << next->key << " " << val->key << "\n";
        before = next;
        next = next->next;
    }

    if (next != NULL) {
        free(next->data);
        next->data = val->data;
        next->length = val->length;
        free(val);
    } else {
        before->next = val;
    }
}                                         

db_val_t* ht_get(hashtable_t* ht, uint32_t key) {
    uint32_t hash = get_hash(key, 0) % ht->size;
    db_val_t* p = ht->table[hash];
    while (p && p->key != key)
        p = p->next;
    return p;
}
                                          
