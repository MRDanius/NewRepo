// IntHashMap.cpp
#include "IntHashMap.h"
#include <cmath>

IntHashMap::IntHashMap(int initialCapacity, float lf)
    : capacity(nextPrime(initialCapacity)), loadFactor(lf), count(0) {
    table = new Node[capacity];
}

IntHashMap::~IntHashMap() {
    delete[] table;
}

bool IntHashMap::isPrime(int num) const {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;

    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

int IntHashMap::nextPrime(int num) const {
    while (!isPrime(num)) {
        num++;
    }
    return num;
}

int IntHashMap::hash1(int key) const {
    return abs(key) % capacity;
}

int IntHashMap::hash2(int key) const {
    return 1 + (abs(key) % (capacity - 1));
}

void IntHashMap::rehash() {
    int oldCapacity = capacity;
    capacity = nextPrime(capacity * 2);

    Node* oldTable = table;
    table = new Node[capacity];
    count = 0;

    for (int i = 0; i < oldCapacity; ++i) {
        if (oldTable[i].value != nullptr && !oldTable[i].isDeleted) {
            insert(oldTable[i].key, oldTable[i].value);
        }
    }

    delete[] oldTable;
}

void IntHashMap::insert(int key, void* value) {
    if (count >= capacity * loadFactor) {
        rehash();
    }

    int index = hash1(key);
    int step = hash2(key);

    for (int i = 0; i < capacity; ++i) {
        if (table[index].value == nullptr || table[index].isDeleted) {
            table[index].key = key;
            table[index].value = value;
            table[index].isDeleted = false;
            count++;
            return;
        }

        if (table[index].key == key && !table[index].isDeleted) {
            table[index].value = value;
            return;
        }

        index = (index + step) % capacity;
    }

    rehash();
    insert(key, value);
}

bool IntHashMap::get(int key, void*& value) const {
    int index = hash1(key);
    int step = hash2(key);

    for (int i = 0; i < capacity; ++i) {
        if (table[index].value == nullptr && !table[index].isDeleted) {
            return false;
        }

        if (table[index].key == key && !table[index].isDeleted) {
            value = table[index].value;
            return true;
        }

        index = (index + step) % capacity;
    }

    return false;
}

bool IntHashMap::remove(int key) {
    int index = hash1(key);
    int step = hash2(key);

    for (int i = 0; i < capacity; ++i) {
        if (table[index].value == nullptr && !table[index].isDeleted) {
            return false;
        }

        if (table[index].key == key && !table[index].isDeleted) {
            table[index].isDeleted = true;
            count--;
            return true;
        }

        index = (index + step) % capacity;
    }

    return false;
}

void IntHashMap::clear() {
    for (int i = 0; i < capacity; ++i) {
        table[i].value = nullptr;
        table[i].isDeleted = false;
    }
    count = 0;
}

bool IntHashMap::contains(int key) const {
    void* dummy;
    return get(key, dummy);
}

int IntHashMap::size() const {
    return count;
}