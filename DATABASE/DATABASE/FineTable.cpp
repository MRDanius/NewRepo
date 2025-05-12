// FineTable.cpp
#include "FineTable.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cctype>
#include <set>

using namespace std;

FineTable::FineTable() : head(new Fine{ 0, 0.0, "", nullptr }), idToFineMap() {
    load();
}

FineTable::~FineTable() {
    clear();
}

void FineTable::clear() {
    Fine* current = head;
    while (current) {
        Fine* temp = current;
        current = current->next;
        delete temp;
    }
    head = new Fine{ 0, 0.0, "", nullptr };
    idToFineMap.clear();
}

int FineTable::getNextId() {
    set<int> usedIds;
    Fine* current = head->next;
    while (current) {
        usedIds.insert(current->id);
        current = current->next;
    }
    for (int i = 1;; i++) {
        if (usedIds.find(i) == usedIds.end()) {
            return i;
        }
    }
}

void FineTable::parseLine(const string& line) {
    if (line.empty()) return;

    string id_str = line.substr(0, ID_LENGTH);
    id_str.erase(id_str.find_last_not_of(' ') + 1);
    int id = stoi(id_str);

    string data = line.substr(ID_LENGTH);
    istringstream iss(data);
    double amount;
    string type;
    iss >> amount >> type;

    Fine* newFine = new Fine{ id, amount, type, head->next };
    head->next = newFine;
    idToFineMap.insert(id, newFine);
}

void FineTable::load() {
    ifstream file(filename);
    string line;
    clear();
    while (getline(file, line)) {
        parseLine(line);
    }
}

void FineTable::save() {
    ofstream file(filename);
    Fine* current = head->next;
    while (current) {
        file << setw(ID_LENGTH) << left << current->id
            << current->amount << " "
            << current->type << endl;
        current = current->next;
    }
}

void FineTable::addFine(double amount, const string& type) {
    int newId = getNextId();
    Fine* newFine = new Fine{ newId, amount, type, head->next };
    head->next = newFine;
    idToFineMap.insert(newId, newFine);
    save();
}

FineTable::Fine* FineTable::getFineById(int fineId) {
    void* finePtr;
    if (idToFineMap.get(fineId, finePtr)) {  // <- Заменить поиск
        return static_cast<Fine*>(finePtr);
    }
    return nullptr;
}

FineTable::Fine* FineTable::getAllFines() {
    return head->next;
}

void FineTable::deleteRecord(int fineId) {
    Fine* prev = head;
    Fine* current = head->next;
    while (current) {
        if (current->id == fineId) {
            prev->next = current->next;
            idToFineMap.remove(fineId);
            delete current;
            save();
            return;
        }
        prev = current;
        current = current->next;
    }
}

void FineTable::updateReferences(int oldId, int newId) {}