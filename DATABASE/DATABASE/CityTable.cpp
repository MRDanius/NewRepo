// CityTable.cpp
#include "CityTable.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cctype>
#include <set>

using namespace std;

CityTable::CityTable() : head(new City{ 0, "Служебная_запись", nullptr }), idToCityMap() {
    load();
}

CityTable::~CityTable() {
    clear();
}

void CityTable::clear() {
    City* current = head;
    while (current) {
        City* temp = current;
        current = current->next;
        delete temp;
    }
    head = new City{ 0, "Служебная_запись", nullptr };
    idToCityMap.clear();
}

int CityTable::getNextId() {
    set<int> usedIds;
    City* current = head->next;
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

void CityTable::parseLine(const string& line) {
    if (line.empty()) return;

    string id_str = line.substr(0, ID_LENGTH);
    id_str.erase(id_str.find_last_not_of(' ') + 1);
    int id = stoi(id_str);

    string name = line.substr(ID_LENGTH);
    while (!name.empty() && isspace(name.front())) {
        name.erase(0, 1);
    }

    City* newCity = new City{ id, name, head->next };
    head->next = newCity;
    idToCityMap.insert(id, newCity);  // <- Добавить эту строку
}

void CityTable::load() {
    ifstream file(filename);
    string line;
    clear();
    while (getline(file, line)) {
        parseLine(line);
    }
}

void CityTable::save() {
    ofstream file(filename);
    City* current = head->next;
    while (current) {
        file << setw(ID_LENGTH) << left << current->id
            << current->name << endl;
        current = current->next;
    }
}

void CityTable::addCity(const string& name) {
    int newId = getNextId();
    City* newCity = new City{ newId, name, head->next };
    head->next = newCity;
    idToCityMap.insert(newId, newCity);  // <- Добавить эту строку
    save();
}

string CityTable::getCityName(int cityId) {
    void* cityPtr;
    if (idToCityMap.get(cityId, cityPtr)) {  // <- Заменить старый поиск
        City* city = static_cast<City*>(cityPtr);
        return city->name;
    }
    return "Неизвестный_город";
}

CityTable::City* CityTable::getAllCities() {
    return head->next;
}

void CityTable::deleteRecord(int cityId) {
    City* prev = head;
    City* current = head->next;
    while (current) {
        if (current->id == cityId) {
            prev->next = current->next;
            idToCityMap.remove(cityId);  // <- Добавить эту строку
            delete current;
            save();
            return;
        }
        prev = current;
        current = current->next;
    }
}
void CityTable::updateReferences(int oldId, int newId) {}