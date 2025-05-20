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


//#include "FineRegistry.h"
//#include <fstream>
//#include <sstream>
//#include <iomanip>
//#include <set>
//
//// Конструктор: инициализация и загрузка данных
//FineRegistry::FineRegistry()
//    : head(new ViolationNode(-1, -1, -1, -1, "", false, nullptr)),
//    currentIterator(nullptr) {
//    loadFromFile();
//}
//
//// Деструктор: очистка списка
//FineRegistry::~FineRegistry() {
//    clearList();
//    delete head;
//}
//
//// Генерация уникального ID для нового нарушения
//const int& FineRegistry::generateNextId() {
//    static int nextId = 1;
//    std::set<int> usedIds;
//    for (ViolationNode* curr = head->next; curr; curr = curr->next)
//        usedIds.insert(curr->id);
//    while (usedIds.count(nextId)) nextId++;
//    return nextId;
//}
//
//// Парсинг строки из файла в ViolationNode
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
//// Очистка списка нарушений
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
//// Загрузка данных из файла registry.txt
//void FineRegistry::loadFromFile() {
//    std::ifstream file(filename);
//    if (!file.is_open()) return;
//
//    clearList();
//    std::string line;
//    while (std::getline(file, line)) {
//        parseLine(line);
//    }
//}
//
//// Сохранение данных в файл registry.txt
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
//// Добавление нового нарушения
//void FineRegistry::addViolation(int driverId, int cityId, int fineId, const std::string& date) {
//    const int& newId = generateNextId();
//    ViolationNode* newNode = new ViolationNode(
//        newId, driverId, cityId, fineId, date, false, head->next
//    );
//    head->next = newNode;
//    idToViolationMap.insert(newId, newNode);
//    saveToFile();
//}
//
//// Отметка нарушения как оплаченного
//void FineRegistry::markAsPaid(int recordId) {
//    void* data;
//    if (idToViolationMap.get(recordId, data)) {
//        ViolationNode* violation = static_cast<ViolationNode*>(data);
//        violation->paid = true;
//        saveToFile();
//    }
//}
//
//// Обновление ссылок на водителя при его удалении
//void FineRegistry::updateDriverReferences(int driverId) {
//    for (ViolationNode* curr = head->next; curr; curr = curr->next) {
//        if (curr->driverId == driverId) {
//            curr->driverId = -1;
//        }
//    }
//    saveToFile();
//}
//
//// Обновление ссылок на город при его удалении
//void FineRegistry::updateCityReferences(int cityId) {
//    for (ViolationNode* curr = head->next; curr; curr = curr->next) {
//        if (curr->cityId == cityId) {
//            curr->cityId = -1;
//        }
//    }
//    saveToFile();
//}
//
//// Итератор: сброс указателя на начало списка
//void FineRegistry::violationIteratorReset() const {
//    currentIterator = head->next;
//}
//
//// Проверка наличия следующего нарушения
//bool FineRegistry::violationIteratorHasNext() const {
//    return currentIterator != nullptr;
//}
//
//// Получение информации о нарушении с преобразованием ID в текстовые данные
//FineRegistry::ViolationInfo FineRegistry::violationIteratorNext(
//    const DriverTable& drivers,
//    const CityTable& cities,
//    const FineTable& fines
//) const {
//    ViolationInfo info;
//    if (!currentIterator) return info;
//
//    info.id = currentIterator->id;
//    info.driverName = drivers.getDriverInfoById(currentIterator->driverId).fullName;
//    info.cityName = cities.getCityNameById(currentIterator->cityId);
//    info.fineType = fines.getFineInfoById(currentIterator->fineId).type;
//    info.date = currentIterator->date;
//    info.amount = fines.getFineInfoById(currentIterator->fineId).amount;
//    info.paid = currentIterator->paid;
//    info.severity = fines.getFineInfoById(currentIterator->fineId).severity;
//
//    currentIterator = currentIterator->next;
//    return info;
//}


#include "FineRegistry.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>

// Конструктор
FineRegistry::FineRegistry()
    : head(new ViolationNode(-1, -1, -1, -1, "", false, nullptr)),
    currentFilter(nullptr),
    driverNameWidth(25),
    cityNameWidth(20),
    fineTypeWidth(25),
    dateWidth(12),
    amountWidth(10),
    statusWidth(12)
{
    loadFromFile();
    updateColumnWidths();
}

// Деструктор
FineRegistry::~FineRegistry() {
    clearList();
    clearFilters();
    delete head;
}

// Загрузка данных
void FineRegistry::loadFromFile() {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening registry file!" << std::endl;
        return;
    }

    clearList();
    std::string line;
    while (std::getline(file, line)) {
        parseLine(line);
    }
    updateColumnWidths();
}

// Парсинг строки
void FineRegistry::parseLine(const std::string& line) {
    std::istringstream iss(line);
    int id, driverId, cityId, fineId;
    std::string date;
    bool paid;

    iss >> id >> driverId >> cityId >> fineId >> date >> paid;
    addViolationNode(id, driverId, cityId, fineId, date, paid);
}

// Добавление узла
void FineRegistry::addViolationNode(int id, int driverId, int cityId,
    int fineId, const std::string& date, bool paid)
{
    ViolationNode* newNode = new ViolationNode(
        id, driverId, cityId, fineId, date, paid, head->next
    );
    head->next = newNode;
    idToViolationMap.insert(id, newNode);
}

// Обновление ширины колонок
void FineRegistry::updateColumnWidths() {
    ViolationNode* curr = head->next;
    size_t maxDriverLen = 0, maxCityLen = 0, maxFineLen = 0;

    while (curr) {
        maxDriverLen = std::max(maxDriverLen, getDriverName(curr).length());
        maxCityLen = std::max(maxCityLen, getCityName(curr).length());
        maxFineLen = std::max(maxFineLen, getFineType(curr).length());
        curr = curr->next;
    }

    driverNameWidth = maxDriverLen + 4;
    cityNameWidth = maxCityLen + 4;
    fineTypeWidth = maxFineLen + 4;
}

// Форматирование строки (БЕЗ ID)
std::string FineRegistry::formatNode(const ViolationNode* node) const {
    std::ostringstream oss;
    oss << std::left
        << std::setw(driverNameWidth) << getDriverName(node).substr(0, driverNameWidth - 1)
        << std::setw(cityNameWidth) << getCityName(node)
        << std::setw(fineTypeWidth) << getFineType(node)
        << std::setw(dateWidth) << node->date
        << std::setw(amountWidth) << std::fixed << std::setprecision(2) << getFineAmount(node)
        << std::setw(statusWidth) << (node->paid ? "Paid" : "Unpaid");
    return oss.str();
}

// Добавление фильтра
void FineRegistry::addFilter(const std::string& field, const std::string& pattern) {
    Filter* newFilter = new Filter{ field, pattern, nullptr };

    if (!currentFilter) {
        currentFilter = newFilter;
    }
    else {
        Filter* temp = currentFilter;
        while (temp->next) temp = temp->next;
        temp->next = newFilter;
    }
}

// Применение фильтров
FineRegistry::ViolationNode* FineRegistry::applyFilters() const {
    ViolationNode* filteredHead = new ViolationNode(-1, -1, -1, -1, "", false, nullptr);
    ViolationNode* tail = filteredHead;

    ViolationNode* curr = head->next;
    while (curr) {
        bool match = true;
        Filter* filter = currentFilter;

        while (filter) {
            if (!matchField(curr, filter->field, filter->pattern)) {
                match = false;
                break;
            }
            filter = filter->next;
        }

        if (match) {
            ViolationNode* newNode = cloneNode(curr);
            tail->next = newNode;
            tail = newNode;
        }
        curr = curr->next;
    }

    return filteredHead->next;
}

// Проверка соответствия фильтру
bool FineRegistry::matchField(const ViolationNode* node, const std::string& field,
    const std::string& pattern) const
{
    if (field == "driver") {
        return regexMatch(getDriverName(node), pattern);
    }
    else if (field == "city") {
        return regexMatch(getCityName(node), pattern);
    }
    else if (field == "fine_type") {
        return regexMatch(getFineType(node), pattern);
    }
    else if (field == "date") {
        return regexMatch(node->date, pattern);
    }
    else if (field == "amount") {
        return checkNumeric(getFineAmount(node), pattern);
    }
    else if (field == "status") {
        return pattern == (node->paid ? "Paid" : "Unpaid");
    }
    return false;
}

// Клонирование узла
FineRegistry::ViolationNode* FineRegistry::cloneNode(const ViolationNode* src) const {
    return new ViolationNode(
        src->id,
        src->driverId,
        src->cityId,
        src->fineId,
        src->date,
        src->paid,
        nullptr
    );
}

// Очистка фильтров
void FineRegistry::clearFilters() {
    Filter* current = currentFilter;
    while (current) {
        Filter* next = current->next;
        delete current;
        current = next;
    }
    currentFilter = nullptr;
}

// Вспомогательные методы
std::string FineRegistry::getDriverName(const ViolationNode* node) const {
    return "Driver Name"; // Реальная реализация через DriverTable
}

std::string FineRegistry::getCityName(const ViolationNode* node) const {
    return "City Name"; // Реальная реализация через CityTable
}

std::string FineRegistry::getFineType(const ViolationNode* node) const {
    return "Fine Type"; // Реальная реализация через FineTable
}

double FineRegistry::getFineAmount(const ViolationNode* node) const {
    return 0.0; // Реальная реализация через FineTable
}

// Итератор
void FineRegistry::violationIteratorReset(ViolationNode* start) const {
    currentIterator = start ? start : head->next;
}

bool FineRegistry::violationIteratorHasNext() const {
    return currentIterator != nullptr;
}

FineRegistry::ViolationInfo FineRegistry::violationIteratorNext() const {
    ViolationInfo info;
    if (!currentIterator) return info;

    info.driverName = getDriverName(currentIterator);
    info.cityName = getCityName(currentIterator);
    info.fineType = getFineType(currentIterator);
    info.date = currentIterator->date;
    info.amount = getFineAmount(currentIterator);
    info.paid = currentIterator->paid;

    currentIterator = currentIterator->next;
    return info;
}