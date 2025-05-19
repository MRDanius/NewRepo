//// DriverTable.cpp
//#include "DriverTable.h"
//#include <fstream>
//#include <sstream>
//#include <iomanip>
//#include <iostream>
//#include <cctype>
//#include <set>
//
//using namespace std;
//
//DriverTable::DriverTable() : head(new Driver{ 0, "", "", 0, nullptr }), idToDriverMap() {
//    load();
//}
//
//DriverTable::~DriverTable() {
//    clear();
//}
//
//void DriverTable::clear() {
//    Driver* current = head;
//    while (current) {
//        Driver* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    head = new Driver{ 0, "", "", 0, nullptr };
//    idToDriverMap.clear();
//}
//
//int DriverTable::getNextId() {
//    set<int> usedIds;
//    Driver* current = head->next;
//    while (current) {
//        usedIds.insert(current->id);
//        current = current->next;
//    }
//    for (int i = 1;; i++) {
//        if (usedIds.find(i) == usedIds.end()) {
//            return i;
//        }
//    }
//}
//
//void DriverTable::parseLine(const string& line) {
//    if (line.empty()) return;
//
//    string id_str = line.substr(0, ID_LENGTH);
//    id_str.erase(id_str.find_last_not_of(' ') + 1);
//    int id = stoi(id_str);
//
//    string data = line.substr(ID_LENGTH);
//    size_t last_space = data.rfind(' '); // Последний пробел (перед cityId)
//    size_t prev_space = data.rfind(' ', last_space - 1); // Предпоследний пробел (перед birthDate)
//
//    if (last_space == string::npos || prev_space == string::npos) return;
//
//    string fullName = data.substr(0, prev_space);
//    string birthDate = data.substr(prev_space + 1, last_space - prev_space - 1);
//    int cityId = stoi(data.substr(last_space + 1));
//
//    // Удаляем лишние пробелы
//    fullName.erase(0, fullName.find_first_not_of(' '));
//    fullName.erase(fullName.find_last_not_of(' ') + 1);
//    birthDate.erase(0, birthDate.find_first_not_of(' '));
//    birthDate.erase(birthDate.find_last_not_of(' ') + 1);
//
//    Driver* newDriver = new Driver{ id, fullName, birthDate, cityId, head->next };
//    head->next = newDriver;
//    idToDriverMap.insert(id, newDriver);
//}
//
//void DriverTable::load() {
//    ifstream file(filename);
//    if (!file.is_open()) {
//        cerr << "Файл не найден, будет создан новый." << endl;
//        return;
//    }
//
//    clear(); // Очищаем текущие данные перед загрузкой
//
//    string line;
//    while (getline(file, line)) {
//        parseLine(line);
//    }
//    file.close();
//}
//
//void DriverTable::save() {
//    ofstream file(filename);
//    if (!file.is_open()) {
//        cerr << "Ошибка открытия файла для сохранения!" << endl;
//        return;
//    }
//
//    Driver* current = head->next;
//    while (current) {
//        file << setw(ID_LENGTH) << left << current->id
//            << current->fullName << " "
//            << current->birthDate << " "
//            << current->cityId << endl;
//        current = current->next;
//    }
//    file.close();
//}
//
//
//void DriverTable::addDriver(const string& fullName, const string& birthDate, int cityId) {
//    int newId = getNextId();
//    Driver* newDriver = new Driver{ newId, fullName, birthDate, cityId, head->next };
//    head->next = newDriver;
//    idToDriverMap.insert(newId, newDriver);  // <- Добавить
//}
//
//string DriverTable::getDriverInfo(int driverId) {
//    void* driverPtr;
//    if (idToDriverMap.get(driverId, driverPtr)) {  // <- Заменить поиск
//        Driver* driver = static_cast<Driver*>(driverPtr);
//        return "ID: " + to_string(driver->id) +
//            ", ФИО: " + driver->fullName +
//            ", Дата рождения: " + driver->birthDate +
//            ", Город ID: " + to_string(driver->cityId);
//    }
//    return "Водитель не найден";
//}
//
//DriverTable::Driver* DriverTable::getAllDrivers() {
//    return head->next;
//}
//
//void DriverTable::deleteRecord(int driverId) {
//    Driver* prev = head;
//    Driver* current = head->next;
//    while (current) {
//        if (current->id == driverId) {
//            prev->next = current->next;
//            idToDriverMap.remove(driverId);
//            delete current;
//            save();
//            return;
//        }
//        prev = current;
//        current = current->next;
//    }
//}
//
//void DriverTable::updateReferences(int oldId, int newId) {}
//
//void DriverTable::updateCityReferences(int oldCityId) {
//    Driver* current = head->next;
//    while (current) {
//        if (current->cityId == oldCityId) {
//            current->cityId = 0;
//        }
//        current = current->next;
//    }
//    save();
//}

//#include "DriverTable.h"
//#include <fstream>
//#include <sstream>
//#include <iomanip>
//#include <set>
//
//DriverTable::DriverTable()
//    : head(new DriverNode(-1, "", "", -1, nullptr)), currentIterator(nullptr) {
//    loadFromFile();
//}
//
//DriverTable::~DriverTable() {
//    clearList();
//    delete head;
//}
//
//const int& DriverTable::generateNextId() {
//    static int nextId = 1;
//    std::set<int> usedIds;
//    for (DriverNode* curr = head->next; curr; curr = curr->next)
//        usedIds.insert(curr->id);
//    while (usedIds.count(nextId))
//        nextId++;
//    return nextId;
//}
//
//void DriverTable::parseLine(const std::string& line) {
//    if (line.empty()) return;
//
//    std::string idStr = line.substr(0, ID_LENGTH);
//    int id = std::stoi(idStr);
//
//    std::istringstream iss(line.substr(ID_LENGTH));
//    std::string fullName, birthDate;
//    int cityId;
//    std::getline(iss, fullName, ';');
//    std::getline(iss, birthDate, ';');
//    iss >> cityId;
//
//    DriverNode* newNode = new DriverNode(id, fullName, birthDate, cityId, head->next);
//    head->next = newNode;
//    idToDriverMap.insert(id, newNode);
//    nameToIdMap[fullName] = id;
//}
//
//void DriverTable::clearList() {
//    DriverNode* current = head->next;
//    while (current) {
//        DriverNode* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    head->next = nullptr;
//}
//
//void DriverTable::loadFromFile() {
//    std::ifstream file(filename);
//    if (!file.is_open()) return;
//
//    clearList();
//    std::string line;
//    while (std::getline(file, line))
//        parseLine(line);
//}
//
//void DriverTable::saveToFile() {
//    std::ofstream file(filename);
//    for (DriverNode* curr = head->next; curr; curr = curr->next)
//        file << std::setw(ID_LENGTH) << std::left << curr->id
//        << curr->fullName << ";" << curr->birthDate << ";"
//        << curr->cityId << std::endl;
//}
//
//void DriverTable::addDriver(const std::string& fullName,
//    const std::string& birthDate,
//    const int& cityId) {
//    const int& newId = generateNextId();
//    DriverNode* newNode = new DriverNode(newId, fullName, birthDate, cityId, head->next);
//    head->next = newNode;
//    idToDriverMap.insert(newId, newNode);
//    nameToIdMap[fullName] = newId;
//    saveToFile();
//}
//
//void DriverTable::deleteDriver(const std::string& name) {
//    auto it = nameToIdMap.find(name);
//    if (it == nameToIdMap.end()) return;
//
//    const int& targetId = it->second;
//    DriverNode* prev = head;
//    DriverNode* current = head->next;
//    while (current) {
//        if (current->id == targetId) {
//            prev->next = current->next;
//            idToDriverMap.remove(targetId);
//            nameToIdMap.erase(current->fullName);
//            delete current;
//            saveToFile();
//            return;
//        }
//        prev = current;
//        current = current->next;
//    }
//}
//
//DriverTable::DriverInfo DriverTable::getDriverInfo(const std::string& name) const {
//    DriverInfo info;
//    const int& id = getDriverId(name);
//    if (id == -1) return info;
//
//    void* data;
//    if (idToDriverMap.get(id, data)) {
//        DriverNode* driver = static_cast<DriverNode*>(data);
//        info.fullName = driver->fullName;
//        info.birthDate = driver->birthDate;
//    }
//    return info;
//}
//
//const int& DriverTable::getDriverId(const std::string& name) const {
//    static const int invalidId = -1;
//    auto it = nameToIdMap.find(name);
//    return (it != nameToIdMap.end()) ? it->second : invalidId;
//}
//
//int DriverTable::getCityIdForDriver(const std::string& name) const {
//    const int& driverId = getDriverId(name);
//    if (driverId == -1) return -1;
//
//    void* data;
//    if (idToDriverMap.get(driverId, data)) {
//        DriverNode* driver = static_cast<DriverNode*>(data);
//        return driver->cityId;
//    }
//    return -1;
//}
//
//void DriverTable::driverIteratorReset() const {
//    currentIterator = head->next;
//}
//
//bool DriverTable::driverIteratorHasNext() const {
//    return currentIterator != nullptr;
//}
//
//DriverTable::DriverInfo DriverTable::driverIteratorNext(const CityTable& cityTable) const {
//    DriverInfo info;
//    if (!currentIterator) return info;
//
//    info.fullName = currentIterator->fullName;
//    info.birthDate = currentIterator->birthDate;
//    info.cityName = cityTable.getCityNameById(currentIterator->cityId);
//
//    currentIterator = currentIterator->next;
//    return info;
//}
//
//DriverTable::DriverInfo DriverTable::getDriverInfoById(const int& driverId) const {
//    DriverInfo info;
//    void* data;
//
//    if (idToDriverMap.get(driverId, data)) {
//        DriverNode* driver = static_cast<DriverNode*>(data);
//        info.fullName = driver->fullName;
//        info.birthDate = driver->birthDate;
//    }
//    return info;
//}

#include "DriverTable.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <set>

DriverTable::DriverTable()
    : head(new DriverNode(-1, "", "", -1, nullptr)),
    currentIterator(nullptr) {
    loadFromFile();
}

DriverTable::~DriverTable() {
    clearList();
    delete head;
}

const int& DriverTable::generateNextId() {
    static int nextId = 1;
    std::set<int> usedIds;
    for (DriverNode* curr = head->next; curr; curr = curr->next)
        usedIds.insert(curr->id);
    while (usedIds.count(nextId)) nextId++;
    return nextId;
}

void DriverTable::parseLine(const std::string& line) {
    if (line.empty()) return;

    std::istringstream iss(line);
    int id, cityId;
    std::string fullName, birthDate;

    iss >> id >> std::quoted(fullName) >> std::quoted(birthDate) >> cityId;

    DriverNode* newNode = new DriverNode(id, fullName, birthDate, cityId, head->next);
    head->next = newNode;
    idToDriverMap.insert(id, newNode);
    nameToIdMap[fullName] = id;
}

void DriverTable::clearList() {
    DriverNode* current = head->next;
    while (current) {
        DriverNode* temp = current;
        current = current->next;
        delete temp;
    }
    head->next = nullptr;
    idToDriverMap.clear();
    nameToIdMap.clear();
}

void DriverTable::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    clearList();
    std::string line;
    while (std::getline(file, line))
        parseLine(line);
}

void DriverTable::saveToFile() {
    std::ofstream file(filename);
    for (DriverNode* curr = head->next; curr; curr = curr->next) {
        file << std::setw(5) << std::left << curr->id
            << std::quoted(curr->fullName) << " "
            << std::quoted(curr->birthDate) << " "
            << curr->cityId << "\n";
    }
}

void DriverTable::addDriver(const std::string& fullName,
    const std::string& birthDate,
    int cityId) {
    const int& newId = generateNextId();
    DriverNode* newNode = new DriverNode(newId, fullName, birthDate, cityId, head->next);
    head->next = newNode;
    idToDriverMap.insert(newId, newNode);
    nameToIdMap[fullName] = newId;
    saveToFile();
}

void DriverTable::deleteDriver(const std::string& name) {
    auto it = nameToIdMap.find(name);
    if (it == nameToIdMap.end()) return;

    const int& targetId = it->second;
    DriverNode* prev = head;
    DriverNode* current = head->next;
    while (current) {
        if (current->id == targetId) {
            prev->next = current->next;
            idToDriverMap.remove(targetId);
            nameToIdMap.erase(current->fullName);
            delete current;
            saveToFile();
            return;
        }
        prev = current;
        current = current->next;
    }
}

DriverTable::DriverInfo DriverTable::getDriverInfo(const std::string& name) const {
    DriverInfo info;
    const int& id = getDriverId(name);
    if (id == -1) return info;

    void* data;
    if (idToDriverMap.get(id, data)) {
        DriverNode* driver = static_cast<DriverNode*>(data);
        info.fullName = driver->fullName;
        info.birthDate = driver->birthDate;
        info.cityId = driver->cityId;
    }
    return info;
}

DriverTable::DriverInfo DriverTable::getDriverInfoById(int driverId) const {
    DriverInfo info;
    void* data;
    if (idToDriverMap.get(driverId, data)) {
        DriverNode* driver = static_cast<DriverNode*>(data);
        info.fullName = driver->fullName;
        info.birthDate = driver->birthDate;
        info.cityId = driver->cityId;
    }
    return info;
}

int DriverTable::getCityIdForDriver(const std::string& name) const {
    const int& driverId = getDriverId(name);
    if (driverId == -1) return -1;

    void* data;
    if (idToDriverMap.get(driverId, data)) {
        DriverNode* driver = static_cast<DriverNode*>(data);
        return driver->cityId;
    }
    return -1;
}

void DriverTable::updateCityReferences(int oldCityId) {
    DriverNode* current = head->next;
    while (current) {
        if (current->cityId == oldCityId) {
            current->cityId = -1;
        }
        current = current->next;
    }
    saveToFile();
}

void DriverTable::driverIteratorReset() const {
    currentIterator = head->next;
}

bool DriverTable::driverIteratorHasNext() const {
    return currentIterator != nullptr;
}

DriverTable::DriverInfo DriverTable::driverIteratorNext() const {
    DriverInfo info;
    if (!currentIterator) return info;

    info.id = currentIterator->id;
    info.fullName = currentIterator->fullName;
    info.birthDate = currentIterator->birthDate;
    info.cityId = currentIterator->cityId;

    currentIterator = currentIterator->next;
    return info;
}

const int& DriverTable::getDriverId(const std::string& name) const {
    static const int invalidId = -1;
    auto it = nameToIdMap.find(name);
    return (it != nameToIdMap.end()) ? it->second : invalidId;
}