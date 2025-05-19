//// FineRegistry.cpp
//#include "FineRegistry.h"
//#include <fstream>
//#include <sstream>
//#include <iomanip>
//#include <iostream>
//#include <cctype>
//#include <set>
//
//using namespace std;
//
//FineRegistry::FineRegistry() : head(new FineRecord{ 0, 0, 0, 0, " ", false, nullptr }), idToRecordMap() {
//    load();
//}
//
//FineRegistry::~FineRegistry() {
//    clear();
//}
//
//void FineRegistry::clear() {
//    FineRecord* current = head;
//    while (current) {
//        FineRecord* temp = current;
//        current = current->next;
//        delete temp;
//    }0,
//        head = new FineRecord{ 0, 0, 0, 0, " ", false, nullptr };
//    idToRecordMap.clear();
//}
//
//int FineRegistry::getNextId() {
//    set<int> usedIds;
//    FineRecord* current = head->next;
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
//void FineRegistry::parseLine(const string& line) {
//    if (line.empty()) return;
//
//    // Парсим ID (первые 5 символов)
//    string id_str = line.substr(0, ID_LENGTH);
//    id_str.erase(id_str.find_last_not_of(' ') + 1);
//    int id = stoi(id_str);
//
//    // Остальные данные
//    string data = line.substr(ID_LENGTH);
//    istringstream iss(data);
//    int driverId, cityId, fineId;
//    string violationDate;
//    bool isPaid;
//
//    if (!(iss >> driverId >> cityId >> fineId >> violationDate >> isPaid)) {
//        cerr << "Ошибка парсинга строки: " << line << endl;
//        return;
//    }
//
//    // Создаем запись
//    FineRecord* newRecord = new FineRecord{
//        id, driverId, cityId, fineId,
//        violationDate, isPaid, head->next
//    };
//    head->next = newRecord;
//    idToRecordMap.insert(id, newRecord);
//}
//
//void FineRegistry::load() {
//    ifstream file(filename);
//    string line;
//    clear();
//    while (getline(file, line)) {
//        parseLine(line);
//    }
//}
//
//void FineRegistry::save() {
//    ofstream file(filename);
//    FineRecord* current = head->next;
//    while (current) {
//        file << setw(ID_LENGTH) << left << current->id
//            << current->driverId << " "
//            << current->cityId << " "
//            << current->fineId << " "
//            << current->violationDate << " "
//            << current->isPaid << endl;
//        current = current->next;
//    }
//}
//
//void FineRegistry::addRecord(int driverId, int cityId, int fineId, const std::string& violationDate, bool isPaid) {
//    int newId = getNextId();
//    FineRecord* newRecord = new FineRecord{ newId, driverId, cityId, fineId, violationDate, isPaid, head->next };
//    head->next = newRecord;
//    idToRecordMap.insert(newId, newRecord);
//    save();
//}
//
//FineRegistry::FineRecord* FineRegistry::getRecordsByDriver(int driverId) {
//    FineRecord* result = nullptr;
//    FineRecord* current = head->next;
//    while (current) {
//        if (driverId == 0 || current->driverId == driverId) {
//            FineRecord* newNode = new FineRecord(*current);
//            newNode->next = result;
//            result = newNode;
//        }
//        current = current->next;
//    }
//    return result;
//}
//
//FineRegistry::FineRecord* FineRegistry::getRecordsByCity(int cityId) {
//    FineRecord* result = nullptr;
//    FineRecord* current = head->next;
//    while (current) {
//        if (current->cityId == cityId) {
//            FineRecord* newNode = new FineRecord(*current);
//            newNode->next = result;
//            result = newNode;
//        }
//        current = current->next;
//    }
//    return result;
//}
//
//void FineRegistry::markAsPaid(int recordId) {
//    void* recordPtr;
//    if (idToRecordMap.get(recordId, recordPtr)) {  // <- Заменить поиск
//        static_cast<FineRecord*>(recordPtr)->isPaid = true;
//        save();
//    }
//}
//
//void FineRegistry::deleteRecord(int recordId) {
//    FineRecord* prev = head;
//    FineRecord* current = head->next;
//    while (current) {
//        if (current->id == recordId) {
//            prev->next = current->next;
//            idToRecordMap.remove(recordId);
//            delete current;
//            save();
//            return;
//        }
//        prev = current;
//        current = current->next;
//    }
//}
//
//void FineRegistry::updateDriverReferences(int oldDriverId) {
//    FineRecord* current = head->next;
//    bool updated = false;
//    while (current) {
//        if (current->driverId == oldDriverId) {
//            current->driverId = 0;
//            updated = true;
//        }
//        current = current->next;
//    }
//    if (updated) save();
//}
//
//void FineRegistry::updateCityReferences(int oldCityId) {
//    FineRecord* current = head->next;
//    bool updated = false;
//    while (current) {
//        if (current->cityId == oldCityId) {
//            current->cityId = 0;
//            updated = true;
//        }
//        current = current->next;
//    }
//    if (updated) save();
//}

//#include "FineRegistry.h"
//#include <fstream>
//#include <sstream>
//#include <iomanip>
//#include <set>
//
//FineRegistry::FineRegistry()
//    : head(new ViolationNode(-1, -1, -1, -1, "", false, nullptr)),
//    currentIterator(nullptr) {
//    loadFromFile();
//}
//
//FineRegistry::~FineRegistry() {
//    clearList();
//    delete head;
//}
//
//const int& FineRegistry::generateNextId() {
//    static int nextId = 1;
//    std::set<int> usedIds;
//    for (ViolationNode* curr = head->next; curr; curr = curr->next)
//        usedIds.insert(curr->id);
//    while (usedIds.count(nextId))
//        nextId++;
//    return nextId;
//}
//
//void FineRegistry::parseLine(const std::string& line) {
//    if (line.empty()) return;
//
//    std::string idStr = line.substr(0, ID_LENGTH);
//    int id = std::stoi(idStr);
//
//    std::istringstream iss(line.substr(ID_LENGTH));
//    int driverId, cityId, fineId;
//    std::string date;
//    bool paid;
//    iss >> driverId >> cityId >> fineId >> date >> paid;
//
//    ViolationNode* newNode = new ViolationNode(
//        id, driverId, cityId, fineId, date, paid, head->next
//    );
//    head->next = newNode;
//    idToViolationMap.insert(id, newNode);
//}
//
//void FineRegistry::clearList() {
//    ViolationNode* current = head->next;
//    while (current) {
//        ViolationNode* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    head->next = nullptr;
//}
//
//void FineRegistry::loadFromFile() {
//    std::ifstream file(filename);
//    if (!file.is_open()) return;
//
//    clearList();
//    std::string line;
//    while (std::getline(file, line))
//        parseLine(line);
//}
//
//void FineRegistry::saveToFile() {
//    std::ofstream file(filename);
//    for (ViolationNode* curr = head->next; curr; curr = curr->next)
//        file << std::setw(ID_LENGTH) << std::left << curr->id
//        << curr->driverId << " " << curr->cityId << " "
//        << curr->fineId << " " << curr->date << " "
//        << curr->paid << std::endl;
//}
//
//void FineRegistry::addViolation(const int& driverId, const int& cityId,
//    const int& fineId, const std::string& date) {
//    const int& newId = generateNextId();
//    ViolationNode* newNode = new ViolationNode(
//        newId, driverId, cityId, fineId, date, false, head->next
//    );
//    head->next = newNode;
//    idToViolationMap.insert(newId, newNode);
//    saveToFile();
//}
//
//void FineRegistry::markAsPaid(const int& recordId) {
//    void* data;
//    if (idToViolationMap.get(recordId, data)) {
//        ViolationNode* violation = static_cast<ViolationNode*>(data);
//        violation->paid = true;
//        saveToFile();
//    }
//}
//
//void FineRegistry::updateDriverReferences(const int& driverId) {
//    for (ViolationNode* curr = head->next; curr; curr = curr->next) {
//        if (curr->driverId == driverId)
//            curr->driverId = -1;
//    }
//    saveToFile();
//}
//
//void FineRegistry::updateCityReferences(const int& cityId) {
//    for (ViolationNode* curr = head->next; curr; curr = curr->next) {
//        if (curr->cityId == cityId)
//            curr->cityId = -1;
//    }
//    saveToFile();
//}
//
//void FineRegistry::violationIteratorReset() const {
//    currentIterator = head->next;
//}
//
//bool FineRegistry::violationIteratorHasNext() const {
//    return currentIterator != nullptr;
//}
//
//FineRegistry::ViolationInfo FineRegistry::violationIteratorNext(
//    const DriverTable& drivers,
//    const CityTable& cities,
//    const FineTable& fines) const
//{
//    ViolationInfo info;
//    if (!currentIterator) return info;
//
//    info.recordId = currentIterator->id;
//    info.driverName = drivers.getDriverInfoById(currentIterator->driverId).fullName;
//    info.cityName = cities.getCityNameById(currentIterator->cityId);
//    info.fineType = fines.getFineInfoById(currentIterator->fineId).type;
//    info.date = currentIterator->date;
//    info.paid = currentIterator->paid;
//
//    currentIterator = currentIterator->next;
//    return info;
//}


//#include "FineRegistry.h"
//#include <fstream>
//#include <sstream>
//#include <iomanip>
//#include <set>
//
//FineRegistry::FineRegistry()
//    : head(new ViolationNode(-1, -1, -1, -1, "", false, nullptr)),
//    currentIterator(nullptr) {
//    loadFromFile();
//}
//
//FineRegistry::~FineRegistry() {
//    clearList();
//    delete head;
//}
//
//const int& FineRegistry::generateNextId() {
//    static int nextId = 1;
//    std::set<int> usedIds;
//    for (ViolationNode* curr = head->next; curr; curr = curr->next)
//        usedIds.insert(curr->id);
//    while (usedIds.count(nextId)) nextId++;
//    return nextId;
//}
//
//void FineRegistry::parseLine(const std::string& line) {
//    if (line.empty()) return;
//
//    std::istringstream iss(line);
//    int id, driverId, cityId, fineId;
//    std::string date;
//    bool paid;
//
//    iss >> id >> driverId >> cityId >> fineId >> date >> paid;
//
//    ViolationNode* newNode = new ViolationNode(
//        id, driverId, cityId, fineId, date, paid, head->next
//    );
//    head->next = newNode;
//    idToViolationMap.insert(id, newNode);
//}
//
//void FineRegistry::clearList() {
//    ViolationNode* current = head->next;
//    while (current) {
//        ViolationNode* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    head->next = nullptr;
//    idToViolationMap.clear();
//}
//
//void FineRegistry::loadFromFile() {
//    std::ifstream file(filename);
//    if (!file.is_open()) return;
//
//    clearList();
//    std::string line;
//    while (std::getline(file, line))
//        parseLine(line);
//}
//
//void FineRegistry::saveToFile() {
//    std::ofstream file(filename);
//    for (ViolationNode* curr = head->next; curr; curr = curr->next) {
//        file << std::setw(5) << std::left << curr->id
//            << curr->driverId << " "
//            << curr->cityId << " "
//            << curr->fineId << " "
//            << curr->date << " "
//            << curr->paid << "\n";
//    }
//}
//
//void FineRegistry::addViolation(int driverId, int cityId,
//    int fineId, const std::string& date) {
//    const int& newId = generateNextId();
//    ViolationNode* newNode = new ViolationNode(
//        newId, driverId, cityId, fineId, date, false, head->next
//    );
//    head->next = newNode;
//    idToViolationMap.insert(newId, newNode);
//    saveToFile();
//}
//
//void FineRegistry::markAsPaid(int recordId) {
//    void* data;
//    if (idToViolationMap.get(recordId, data)) {
//        ViolationNode* violation = static_cast<ViolationNode*>(data);
//        violation->paid = true;
//        saveToFile();
//    }
//}
//
//void FineRegistry::updateDriverReferences(int driverId) {
//    ViolationNode* current = head->next;
//    while (current) {
//        if (current->driverId == driverId) {
//            current->driverId = -1;
//        }
//        current = current->next;
//    }
//    saveToFile();
//}
//
//void FineRegistry::updateCityReferences(int cityId) {
//    ViolationNode* current = head->next;
//    while (current) {
//        if (current->cityId == cityId) {
//            current->cityId = -1;
//        }
//        current = current->next;
//    }
//    saveToFile();
//}
//
//void FineRegistry::violationIteratorReset() const {
//    currentIterator = head->next;
//}
//
//bool FineRegistry::violationIteratorHasNext() const {
//    return currentIterator != nullptr;
//}
//
//FineRegistry::ViolationInfo FineRegistry::violationIteratorNext(
//    const DriverTable& drivers,
//    const CityTable& cities,
//    const FineTable& fines) const
//{
//    ViolationInfo info;
//    if (!currentIterator) return info;
//
//    info.id = currentIterator->id;
//    info.driverName = drivers.getDriverInfoById(currentIterator->driverId).fullName;
//    info.cityName = cities.getCityNameById(currentIterator->cityId);
//
//    FineTable::FineInfo fineInfo = fines.getFineInfoById(currentIterator->fineId);
//    info.fineType = fineInfo.type;
//    info.amount = fineInfo.amount;
//    info.severity = fineInfo.severity;
//
//    info.date = currentIterator->date;
//    info.paid = currentIterator->paid;
//
//    currentIterator = currentIterator->next;
//    return info;
//}


#include "FineRegistry.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <set>

// Конструктор: инициализация и загрузка данных
FineRegistry::FineRegistry()
    : head(new ViolationNode(-1, -1, -1, -1, "", false, nullptr)),
    currentIterator(nullptr) {
    loadFromFile();
}

// Деструктор: очистка списка
FineRegistry::~FineRegistry() {
    clearList();
    delete head;
}

// Генерация уникального ID для нового нарушения
const int& FineRegistry::generateNextId() {
    static int nextId = 1;
    std::set<int> usedIds;
    for (ViolationNode* curr = head->next; curr; curr = curr->next)
        usedIds.insert(curr->id);
    while (usedIds.count(nextId)) nextId++;
    return nextId;
}

// Парсинг строки из файла в ViolationNode
void FineRegistry::parseLine(const std::string& line) {
    if (line.empty()) return;

    std::istringstream iss(line);
    int id, driverId, cityId, fineId;
    std::string date;
    bool paid;

    iss >> id >> driverId >> cityId >> fineId >> date >> paid;

    ViolationNode* newNode = new ViolationNode(
        id, driverId, cityId, fineId, date, paid, head->next
    );
    head->next = newNode;
    idToViolationMap.insert(id, newNode);
}

// Очистка списка нарушений
void FineRegistry::clearList() {
    ViolationNode* current = head->next;
    while (current) {
        ViolationNode* temp = current;
        current = current->next;
        delete temp;
    }
    head->next = nullptr;
    idToViolationMap.clear();
}

// Загрузка данных из файла registry.txt
void FineRegistry::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    clearList();
    std::string line;
    while (std::getline(file, line)) {
        parseLine(line);
    }
}

// Сохранение данных в файл registry.txt
void FineRegistry::saveToFile() {
    std::ofstream file(filename);
    for (ViolationNode* curr = head->next; curr; curr = curr->next) {
        file << std::setw(5) << std::left << curr->id
            << curr->driverId << " "
            << curr->cityId << " "
            << curr->fineId << " "
            << curr->date << " "
            << curr->paid << "\n";
    }
}

// Добавление нового нарушения
void FineRegistry::addViolation(int driverId, int cityId, int fineId, const std::string& date) {
    const int& newId = generateNextId();
    ViolationNode* newNode = new ViolationNode(
        newId, driverId, cityId, fineId, date, false, head->next
    );
    head->next = newNode;
    idToViolationMap.insert(newId, newNode);
    saveToFile();
}

// Отметка нарушения как оплаченного
void FineRegistry::markAsPaid(int recordId) {
    void* data;
    if (idToViolationMap.get(recordId, data)) {
        ViolationNode* violation = static_cast<ViolationNode*>(data);
        violation->paid = true;
        saveToFile();
    }
}

// Обновление ссылок на водителя при его удалении
void FineRegistry::updateDriverReferences(int driverId) {
    for (ViolationNode* curr = head->next; curr; curr = curr->next) {
        if (curr->driverId == driverId) {
            curr->driverId = -1;
        }
    }
    saveToFile();
}

// Обновление ссылок на город при его удалении
void FineRegistry::updateCityReferences(int cityId) {
    for (ViolationNode* curr = head->next; curr; curr = curr->next) {
        if (curr->cityId == cityId) {
            curr->cityId = -1;
        }
    }
    saveToFile();
}

// Итератор: сброс указателя на начало списка
void FineRegistry::violationIteratorReset() const {
    currentIterator = head->next;
}

// Проверка наличия следующего нарушения
bool FineRegistry::violationIteratorHasNext() const {
    return currentIterator != nullptr;
}

// Получение информации о нарушении с преобразованием ID в текстовые данные
FineRegistry::ViolationInfo FineRegistry::violationIteratorNext(
    const DriverTable& drivers,
    const CityTable& cities,
    const FineTable& fines
) const {
    ViolationInfo info;
    if (!currentIterator) return info;

    info.id = currentIterator->id;
    info.driverName = drivers.getDriverInfoById(currentIterator->driverId).fullName;
    info.cityName = cities.getCityNameById(currentIterator->cityId);
    info.fineType = fines.getFineInfoById(currentIterator->fineId).type;
    info.date = currentIterator->date;
    info.amount = fines.getFineInfoById(currentIterator->fineId).amount;
    info.paid = currentIterator->paid;
    info.severity = fines.getFineInfoById(currentIterator->fineId).severity;

    currentIterator = currentIterator->next;
    return info;
}