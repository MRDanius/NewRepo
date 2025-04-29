#include "generator.h"
#include "hashtable.h"
#include <random>

std::string* generateUniqueStrings(int count) {
    std::string* strings = new std::string[count];
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist('a', 'z');

    HashTable uniqueCheck(3, 10000);

    int generated = 0;
    while (generated < count) {
        std::string s(4, ' ');
        for (int i = 0; i < 4; ++i) {
            s[i] = static_cast<char>(dist(gen));
        }

        if (uniqueCheck.addWordIfUnique(s.c_str())) {
            strings[generated++] = s;
        }
    }
    return strings;
}