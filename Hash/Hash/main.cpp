#include "hashtable.h"
#include "generator.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    const int N = 10000;
    string* uniqueStrings = generateUniqueStrings(N);

    HashTable tables[] = {
        HashTable(3, 100),
        HashTable(5, 200),
        HashTable(7, 300),
        HashTable(11, 400)
    };

    // ��������� ������ �� ��� �������
    for (int i = 0; i < N; ++i) {
        for (size_t j = 0; j < sizeof(tables) / sizeof(tables[0]); ++j) {
            tables[j].addWordIfUnique(uniqueStrings[i].c_str());
        }
    }

    // ������ ������ CSV-����
    ofstream file("all_buckets.csv");
    if (!file.is_open()) {
        cerr << "Failed to create CSV file!" << endl;
        return 1;
    }

    file << "HashTableSize;Bucket;Count\n"; // ���������

    for (const auto& table : tables) {
        table.exportToCSV(file); // ���������� ������ ������ �������
    }

    file.close();
    delete[] uniqueStrings;

    cout << "All data is saved in all_buckets.csv" << endl;
    return 0;
}
//C:\Users\�������\source\repos\Hash\Hash