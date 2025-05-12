// FineRegistry.cpp
#include "FineRegistry.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cctype>
#include <set>

using namespace std;

FineRegistry::FineRegistry() : head(new FineRecord{ 0, 0, 0, 0, false, nullptr }), idToRecordMap() {
    load();
}

FineRegistry::~FineRegistry() {
    clear();
}

void FineRegistry::clear() {
    FineRecord* current = head;
    while (current) {
        FineRecord* temp = current;
        current = current->next;
        delete temp;
    }
    head = new FineRecord{ 0, 0, 0, 0, false, nullptr };
    idToRecordMap.clear();
}

int FineRegistry::getNextId() {
    set<int> usedIds;
    FineRecord* current = head->next;
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

void FineRegistry::parseLine(const string& line) {
    if (line.empty()) return;

    string id_str = line.substr(0, ID_LENGTH);
    id_str.erase(id_str.find_last_not_of(' ') + 1);
    int id = stoi(id_str);

    string data = line.substr(ID_LENGTH);
    istringstream iss(data);
    int driverId, cityId, fineId;
    bool isPaid;
    iss >> driverId >> cityId >> fineId >> isPaid;

    FineRecord* newRecord = new FineRecord{ id, driverId, cityId, fineId, isPaid, head->next };
    head->next = newRecord;
    idToRecordMap.insert(id, newRecord);
}

void FineRegistry::load() {
    ifstream file(filename);
    string line;
    clear();
    while (getline(file, line)) {
        parseLine(line);
    }
}

void FineRegistry::save() {
    ofstream file(filename);
    FineRecord* current = head->next;
    while (current) {
        file << setw(ID_LENGTH) << left << current->id
            << current->driverId << " "
            << current->cityId << " "
            << current->fineId << " "
            << current->isPaid << endl;
        current = current->next;
    }
}

void FineRegistry::addRecord(int driverId, int cityId, int fineId, bool isPaid) {
    int newId = getNextId();
    FineRecord* newRecord = new FineRecord{ newId, driverId, cityId, fineId, isPaid, head->next };
    head->next = newRecord;
    idToRecordMap.insert(newId, newRecord);
    save();
}

FineRegistry::FineRecord* FineRegistry::getRecordsByDriver(int driverId) {
    FineRecord* result = nullptr;
    FineRecord* current = head->next;
    while (current) {
        if (driverId == 0 || current->driverId == driverId) {
            FineRecord* newNode = new FineRecord(*current);
            newNode->next = result;
            result = newNode;
        }
        current = current->next;
    }
    return result;
}

FineRegistry::FineRecord* FineRegistry::getRecordsByCity(int cityId) {
    FineRecord* result = nullptr;
    FineRecord* current = head->next;
    while (current) {
        if (current->cityId == cityId) {
            FineRecord* newNode = new FineRecord(*current);
            newNode->next = result;
            result = newNode;
        }
        current = current->next;
    }
    return result;
}

void FineRegistry::markAsPaid(int recordId) {
    void* recordPtr;
    if (idToRecordMap.get(recordId, recordPtr)) {  // <- Заменить поиск
        static_cast<FineRecord*>(recordPtr)->isPaid = true;
        save();
    }
}

void FineRegistry::deleteRecord(int recordId) {
    FineRecord* prev = head;
    FineRecord* current = head->next;
    while (current) {
        if (current->id == recordId) {
            prev->next = current->next;
            idToRecordMap.remove(recordId);
            delete current;
            save();
            return;
        }
        prev = current;
        current = current->next;
    }
}

void FineRegistry::updateDriverReferences(int oldDriverId) {
    FineRecord* current = head->next;
    bool updated = false;
    while (current) {
        if (current->driverId == oldDriverId) {
            current->driverId = 0;
            updated = true;
        }
        current = current->next;
    }
    if (updated) save();
}

void FineRegistry::updateCityReferences(int oldCityId) {
    FineRecord* current = head->next;
    bool updated = false;
    while (current) {
        if (current->cityId == oldCityId) {
            current->cityId = 0;
            updated = true;
        }
        current = current->next;
    }
    if (updated) save();
}