// IntHashMap.h
#pragma once

class IntHashMap {
private:
    struct Node {
        int key;
        void* value;
        bool isDeleted;
        Node() : key(0), value(nullptr), isDeleted(false) {}
    };

    static const int INITIAL_CAPACITY = 16;
    Node* table;
    int capacity;
    int count;
    float loadFactor;

    int hash1(int key) const;
    int hash2(int key) const;
    void rehash();
    bool isPrime(int num) const;
    int nextPrime(int num) const;

public:
    IntHashMap(int initialCapacity = INITIAL_CAPACITY, float lf = 0.75f);
    ~IntHashMap();

    void insert(int key, void* value);
    bool get(int key, void*& value) const;
    bool remove(int key);
    void clear();
    bool contains(int key) const;
    int size() const;
};