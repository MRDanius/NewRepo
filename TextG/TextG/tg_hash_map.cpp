#include "tg_hash_map.h"
#include <cstring>

WordHashMap::WordHashMap(int initial_cap) : capacity(initial_cap), size(0) {
    buckets = new Node * [capacity]();
}

WordHashMap::~WordHashMap() {
    for (int i = 0; i < capacity; ++i) {
        Node* node = buckets[i];
        while (node) {
            Node* prev = node;
            node = node->next;
            delete prev;
        }
    }
    delete[] buckets;
}

void WordHashMap::insert(const char* word, int id) {
    unsigned h = 0;
    for (int i = 0; word[i]; ++i) h = h * 31 + word[i];
    int idx = h % capacity;

    Node* node = buckets[idx];
    while (node) {
        if (strcmp(node->entry.word, word) == 0) return;
        node = node->next;
    }

    Node* new_node = new Node{};
    strcpy_s(new_node->entry.word, word);
    new_node->entry.id = id;
    new_node->next = buckets[idx];
    buckets[idx] = new_node;
    size++;
}

int WordHashMap::get(const char* word) const {
    unsigned h = 0;
    for (int i = 0; word[i]; ++i) h = h * 31 + word[i];
    int idx = h % capacity;

    Node* node = buckets[idx];
    while (node) {
        if (strcmp(node->entry.word, word) == 0)
            return node->entry.id;
        node = node->next;
    }
    return -1;
}

BigramHashMap::BigramHashMap(int initial_cap) : capacity(initial_cap) {
    buckets = new Node * [capacity]();
}

BigramHashMap::~BigramHashMap() {
    for (int i = 0; i < capacity; ++i) {
        Node* node = buckets[i];
        while (node) {
            Node* prev = node;
            node = node->next;
            delete prev;
        }
    }
    delete[] buckets;
}

void BigramHashMap::insert_or_update(int from, int to) {
    BigramKey key{ from, to };
    int idx = (from * 31 + to) % capacity;

    Node* node = buckets[idx];
    while (node) {
        if (node->entry.key.from_id == from && node->entry.key.to_id == to) {
            node->entry.count++;
            return;
        }
        node = node->next;
    }

    Node* new_node = new Node{};
    new_node->entry.key = key;
    new_node->entry.count = 1;
    new_node->next = buckets[idx];
    buckets[idx] = new_node;
}
