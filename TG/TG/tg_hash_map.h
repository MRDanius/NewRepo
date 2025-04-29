#pragma once
#include "tg_data_structures.h"
#include "tg_utils.h"

class WordHashMap {
private:
    struct Node {
        WordEntry entry;
        Node* next = nullptr;
    };

    Node** buckets;
    int capacity;
    int size;

    int hash(const char* word) const {
        unsigned h = 0;
        for (int i = 0; word[i]; ++i)
            h = h * 31 + word[i];
        return h % capacity;
    }

public:
    WordHashMap(int initial_cap = 100);
    ~WordHashMap();
    void insert(const char* word, int id);
    int get(const char* word) const;
    void for_each(void (*func)(const WordEntry&)) const;
    int get_unique_count() const { return size; }
};

class BigramHashMap {
private:
    struct Node {
        BigramEntry entry;
        Node* next = nullptr;
    };

    Node** buckets;
    int capacity;

    int hash(const BigramKey& key) const {
        return (key.from_id * 31 + key.to_id) % capacity;
    }

public:
    BigramHashMap(int initial_cap = 1000);
    ~BigramHashMap();
    void insert_or_update(int from, int to);
    void for_each(void (*func)(const BigramEntry&)) const;
};