// DriverTable.cpp
#include "DriverTable.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cctype>
#include <set>

using namespace std;

DriverTable::DriverTable() : head(new Driver{ 0, "", "", 0, nullptr }), idToDriverMap() {
    load();
}

DriverTable::~DriverTable() {
    clear();
}

void DriverTable::clear() {
    Driver* current = head;
    while (current) {
        Driver* temp = current;
        current = current->next;
        delete temp;
    }
    head = new Driver{ 0, "", "", 0, nullptr };
    idToDriverMap.clear();
}

int DriverTable::getNextId() {
    set<int> usedIds;
    Driver* current = head->next;
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

void DriverTable::parseLine(const string& line) {
    if (line.empty()) return;

    string id_str = line.substr(0, ID_LENGTH);
    id_str.erase(id_str.find_last_not_of(' ') + 1);
    int id = stoi(id_str);

    string data = line.substr(ID_LENGTH);
    size_t last_space = data.rfind(' '); // Последний пробел (перед cityId)
    size_t prev_space = data.rfind(' ', last_space - 1); // Предпоследний пробел (перед birthDate)

    if (last_space == string::npos || prev_space == string::npos) return;

    string fullName = data.substr(0, prev_space);
    string birthDate = data.substr(prev_space + 1, last_space - prev_space - 1);
    int cityId = stoi(data.substr(last_space + 1));

    // Удаляем лишние пробелы
    fullName.erase(0, fullName.find_first_not_of(' '));
    fullName.erase(fullName.find_last_not_of(' ') + 1);
    birthDate.erase(0, birthDate.find_first_not_of(' '));
    birthDate.erase(birthDate.find_last_not_of(' ') + 1);

    Driver* newDriver = new Driver{ id, fullName, birthDate, cityId, head->next };
    head->next = newDriver;
    idToDriverMap.insert(id, newDriver);
}


void DriverTable::load() {
    ifstream file(filename);
    string line;
    clear();
    while (getline(file, line)) {
        parseLine(line);
    }
}

void DriverTable::save() {
    ofstream file(filename);
    Driver* current = head->next;
    while (current) {
        file << setw(ID_LENGTH) << left << current->id
            << current->fullName << " "
            << current->birthDate << " "
            << current->cityId << endl;
        current = current->next;
    }
}


void DriverTable::addDriver(const string& fullName, const string& birthDate, int cityId) {
    int newId = getNextId();
    Driver* newDriver = new Driver{ newId, fullName, birthDate, cityId, head->next };
    head->next = newDriver;
    idToDriverMap.insert(newId, newDriver);  // <- Добавить
}

string DriverTable::getDriverInfo(int driverId) {
    void* driverPtr;
    if (idToDriverMap.get(driverId, driverPtr)) {  // <- Заменить поиск
        Driver* driver = static_cast<Driver*>(driverPtr);
        return "ID: " + to_string(driver->id) +
            ", ФИО: " + driver->fullName +
            ", Дата рождения: " + driver->birthDate +
            ", Город ID: " + to_string(driver->cityId);
    }
    return "Водитель не найден";
}

DriverTable::Driver* DriverTable::getAllDrivers() {
    return head->next;
}

void DriverTable::deleteRecord(int driverId) {
    Driver* prev = head;
    Driver* current = head->next;
    while (current) {
        if (current->id == driverId) {
            prev->next = current->next;
            idToDriverMap.remove(driverId);
            delete current;
            save();
            return;
        }
        prev = current;
        current = current->next;
    }
}

void DriverTable::updateReferences(int oldId, int newId) {}

void DriverTable::updateCityReferences(int oldCityId) {
    Driver* current = head->next;
    while (current) {
        if (current->cityId == oldCityId) {
            current->cityId = 0;
        }
        current = current->next;
    }
    save();
}