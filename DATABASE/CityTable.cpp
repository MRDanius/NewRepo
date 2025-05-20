//// CityTable.cpp
//#include "CityTable.h"
//#include <fstream>
//#include <sstream>
//#include <iomanip>
//#include <iostream>
//#include <cctype>
//#include <set>
//
//using namespace std;
//
//CityTable::CityTable() : head(new City{ 0, "Служебная_запись", nullptr }), idToCityMap() {
//    load();
//}
//
//CityTable::~CityTable() {
//    clear();
//}
//
//void CityTable::clear() {
//    City* current = head;
//    while (current) {
//        City* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    head = new City{ 0, "Служебная_запись", nullptr };
//    idToCityMap.clear();
//}
//
//int CityTable::getNextId() {
//    set<int> usedIds;
//    City* current = head->next;
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
//void CityTable::parseLine(const string& line) {
//    if (line.empty()) return;
//
//    string id_str = line.substr(0, ID_LENGTH);
//    id_str.erase(id_str.find_last_not_of(' ') + 1);
//    int id = stoi(id_str);
//
//    string name = line.substr(ID_LENGTH);
//    while (!name.empty() && isspace(name.front())) {
//        name.erase(0, 1);
//    }
//
//    City* newCity = new City{ id, name, head->next };
//    head->next = newCity;
//    idToCityMap.insert(id, newCity);  // <- Добавить эту строку
//}
//
//void CityTable::load() {
//    ifstream file(filename);
//    string line;
//    clear();
//    while (getline(file, line)) {
//        parseLine(line);
//    }
//}
//
//void CityTable::save() {
//    ofstream file(filename);
//    City* current = head->next;
//    while (current) {
//        file << setw(ID_LENGTH) << left << current->id
//            << current->name << endl;
//        current = current->next;
//    }
//}
//
//void CityTable::addCity(const string& name) {
//    int newId = getNextId();
//    City* newCity = new City{ newId, name, head->next };
//    head->next = newCity;
//    idToCityMap.insert(newId, newCity);  // <- Добавить эту строку
//    save();
//}
//
//string CityTable::getCityName(int cityId) {
//    void* cityPtr;
//    if (idToCityMap.get(cityId, cityPtr)) {  // <- Заменить старый поиск
//        City* city = static_cast<City*>(cityPtr);
//        return city->name;
//    }
//    return "Неизвестный_город";
//}
//
//CityTable::City* CityTable::getAllCities() {
//    return head->next;
//}
//
//void CityTable::deleteRecord(int cityId) {
//    City* prev = head;
//    City* current = head->next;
//    while (current) {
//        if (current->id == cityId) {
//            prev->next = current->next;
//            idToCityMap.remove(cityId);  // <- Добавить эту строку
//            delete current;
//            save();
//            return;
//        }
//        prev = current;
//        current = current->next;
//    }
//}
//void CityTable::updateReferences(int oldId, int newId) {}

//#include "CityTable.h"
//#include <fstream>
//#include <sstream>
//#include <iomanip>
//#include <set>
//
//CityTable::CityTable()
//    : head(new CityNode(-1, "HEAD", nullptr)), currentIterator(nullptr) {
//    loadFromFile();
//}
//
//CityTable::~CityTable() {
//    clearList();
//    delete head;
//}
//
//const int& CityTable::generateNextId() {
//    static int nextId = 1;
//    std::set<int> usedIds;
//    for (CityNode* curr = head->next; curr; curr = curr->next)
//        usedIds.insert(curr->id);
//    while (usedIds.count(nextId))
//        nextId++;
//    return nextId;
//}
//
//void CityTable::parseLine(const std::string& line) {
//    if (line.empty()) return;
//
//    std::string idStr = line.substr(0, ID_LENGTH);
//    int id = std::stoi(idStr);
//
//    std::string name = line.substr(ID_LENGTH);
//    name.erase(0, name.find_first_not_of(' '));
//    name.erase(name.find_last_not_of(' ') + 1);
//
//    CityNode* newNode = new CityNode(id, name, head->next);
//    head->next = newNode;
//    idToCityMap.insert(id, newNode);
//    nameToIdMap[name] = id;
//}
//
//void CityTable::clearList() {
//    CityNode* current = head->next;
//    while (current) {
//        CityNode* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    head->next = nullptr;
//}
//
//void CityTable::loadFromFile() {
//    std::ifstream file(filename);
//    if (!file.is_open()) return;
//
//    clearList();
//    std::string line;
//    while (std::getline(file, line))
//        parseLine(line);
//}
//
//void CityTable::saveToFile() {
//    std::ofstream file(filename);
//    for (CityNode* curr = head->next; curr; curr = curr->next)
//        file << std::setw(ID_LENGTH) << std::left << curr->id << curr->name << std::endl;
//}
//
//void CityTable::addCity(const std::string& name) {
//    const int& newId = generateNextId();
//    CityNode* newNode = new CityNode(newId, name, head->next);
//    head->next = newNode;
//    idToCityMap.insert(newId, newNode);
//    nameToIdMap[name] = newId;
//    saveToFile();
//}
//
//void CityTable::deleteCity(const std::string& name) {
//    auto it = nameToIdMap.find(name);
//    if (it == nameToIdMap.end()) return;
//
//    const int& targetId = it->second;
//    CityNode* prev = head;
//    CityNode* current = head->next;
//    while (current) {
//        if (current->id == targetId) {
//            prev->next = current->next;
//            idToCityMap.remove(targetId);
//            nameToIdMap.erase(current->name);
//            delete current;
//            saveToFile();
//            return;
//        }
//        prev = current;
//        current = current->next;
//    }
//}
//
//std::string CityTable::getCityNameById(const int& id) const {
//    void* data;
//    return idToCityMap.get(id, data) ? static_cast<CityNode*>(data)->name : "UNKNOWN_CITY";
//}
//
//const int& CityTable::getCityIdByName(const std::string& name) const {
//    static const int invalidId = -1;
//    auto it = nameToIdMap.find(name);
//    return (it != nameToIdMap.end()) ? it->second : invalidId;
//}
//
//void CityTable::cityIteratorReset() const {
//    currentIterator = head->next;
//}
//
//bool CityTable::cityIteratorHasNext() const {
//    return currentIterator != nullptr;
//}
//
//std::string CityTable::cityIteratorNext() {
//    if (!currentIterator) return "";
//    std::string name = currentIterator->name;
//    currentIterator = currentIterator->next;
//    return name;
//}

//#include "CityTable.h"
//#include <fstream>
//#include <sstream>
//#include <iomanip>
//#include <set>
//
//CityTable::CityTable()
//    : head(new CityNode(-1, "", 0, PopulationGrade::SMALL, SettlementType::CITY, nullptr)),
//    currentIterator(nullptr) {
//    loadFromFile();
//}
//
//CityTable::~CityTable() {
//    clearList();
//    delete head;
//}
//
//const int& CityTable::generateNextId() {
//    static int nextId = 1;
//    std::set<int> usedIds;
//    for (CityNode* curr = head->next; curr; curr = curr->next)
//        usedIds.insert(curr->id);
//    while (usedIds.count(nextId)) nextId++;
//    return nextId;
//}
//
//void CityTable::parseLine(const std::string& line) {
//    if (line.empty()) return;
//
//    std::istringstream iss(line);
//    int id, population;
//    std::string name, gradeStr, typeStr;
//
//    iss >> id >> std::quoted(name) >> population
//        >> std::quoted(gradeStr) >> std::quoted(typeStr);
//
//    // Конвертация строк в enum
//    PopulationGrade grade = PopulationGrade::SMALL;
//    if (gradeStr == "Средний") grade = PopulationGrade::MEDIUM;
//    else if (gradeStr == "Крупный") grade = PopulationGrade::LARGE;
//
//    SettlementType type = SettlementType::CITY;
//    if (typeStr == "Посёлок") type = SettlementType::TOWN;
//    else if (typeStr == "Деревня") type = SettlementType::VILLAGE;
//
//    CityNode* newNode = new CityNode(id, name, population, grade, type, head->next);
//    head->next = newNode;
//    idToCityMap.insert(id, newNode);
//    nameToIdMap[name] = id;
//}
//
//void CityTable::clearList() {
//    CityNode* current = head->next;
//    while (current) {
//        CityNode* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    head->next = nullptr;
//    idToCityMap.clear();
//    nameToIdMap.clear();
//}
//
//void CityTable::loadFromFile() {
//    std::ifstream file(filename);
//    if (!file.is_open()) return;
//
//    clearList();
//    std::string line;
//    while (std::getline(file, line))
//        parseLine(line);
//}
//
//void CityTable::saveToFile() {
//    std::ofstream file(filename);
//    for (CityNode* curr = head->next; curr; curr = curr->next) {
//        file << std::setw(5) << std::left << curr->id
//            << std::quoted(curr->name) << " "
//            << curr->population << " "
//            << std::quoted(populationGradeToString(curr->populationGrade)) << " "
//            << std::quoted(settlementTypeToString(curr->settlementType)) << "\n";
//    }
//}
//
//void CityTable::addCity(const std::string& name, int population,
//    PopulationGrade grade, SettlementType type) {
//    const int& newId = generateNextId();
//    CityNode* newNode = new CityNode(newId, name, population, grade, type, head->next);
//    head->next = newNode;
//    idToCityMap.insert(newId, newNode);
//    nameToIdMap[name] = newId;
//    saveToFile();
//}
//
//void CityTable::deleteCity(const std::string& name) {
//    auto it = nameToIdMap.find(name);
//    if (it == nameToIdMap.end()) return;
//
//    const int& targetId = it->second;
//    CityNode* prev = head;
//    CityNode* current = head->next;
//    while (current) {
//        if (current->id == targetId) {
//            prev->next = current->next;
//            idToCityMap.remove(targetId);
//            nameToIdMap.erase(current->name);
//            delete current;
//            saveToFile();
//            return;
//        }
//        prev = current;
//        current = current->next;
//    }
//}
//
//std::string CityTable::getCityNameById(const int& id) const {
//    void* data;
//    return idToCityMap.get(id, data) ?
//        static_cast<CityNode*>(data)->name : "Неизвестный город";
//}
//
//const int& CityTable::getCityIdByName(const std::string& name) const {
//    static const int invalidId = -1;
//    auto it = nameToIdMap.find(name);
//    return (it != nameToIdMap.end()) ? it->second : invalidId;
//}
//
//std::string CityTable::populationGradeToString(PopulationGrade grade) {
//    switch (grade) {
//    case PopulationGrade::SMALL: return "Малый";
//    case PopulationGrade::MEDIUM: return "Средний";
//    case PopulationGrade::LARGE: return "Крупный";
//    default: return "Неизвестно";
//    }
//}
//
//std::string CityTable::settlementTypeToString(SettlementType type) {
//    switch (type) {
//    case SettlementType::CITY: return "Город";
//    case SettlementType::TOWN: return "Посёлок";
//    case SettlementType::VILLAGE: return "Деревня";
//    default: return "Неизвестно";
//    }
//}
//
//void CityTable::cityIteratorReset() const {
//    currentIterator = head->next;
//}
//
//bool CityTable::cityIteratorHasNext() const {
//    return currentIterator != nullptr;
//}
//
//CityTable::CityInfo CityTable::cityIteratorNext() {
//    CityInfo info;
//    if (!currentIterator) return info;
//
//    info.id = currentIterator->id;
//    info.name = currentIterator->name;
//    info.population = currentIterator->population;
//    info.grade = currentIterator->populationGrade;
//    info.type = currentIterator->settlementType;
//
//    currentIterator = currentIterator->next;
//    return info;
//}


#include "CityTable.h"
//#include <fstream>
//#include <sstream>
//#include <iomanip>
//#include <set>
//
//// Конструктор: загружает данные из файла при создании объекта
//CityTable::CityTable() : head(new CityNode(-1, "", 0, PopulationGrade::SMALL, SettlementType::CITY, nullptr)) {
//    loadFromFile();
//}
//
//// Деструктор: освобождает память и удаляет список
//CityTable::~CityTable() {
//    clearList();
//    delete head;
//}
//
//// Генерация уникального ID для нового города
//const int& CityTable::generateNextId() {
//    static int nextId = 1;
//    std::set<int> usedIds;
//    for (CityNode* curr = head->next; curr; curr = curr->next)
//        usedIds.insert(curr->id);
//    while (usedIds.count(nextId)) nextId++;
//    return nextId;
//}
//
//// Парсинг строки из файла в объект CityNode
//void CityTable::parseLine(const std::string& line) {
//    if (line.empty()) return;
//
//    std::istringstream iss(line);
//    int id, population;
//    std::string name, gradeStr, typeStr;
//
//    iss >> id >> std::quoted(name) >> population >> std::quoted(gradeStr) >> std::quoted(typeStr);
//
//    // Конвертация строк в enum
//    PopulationGrade grade = PopulationGrade::SMALL;
//    if (gradeStr == "Средний") {
//        grade = PopulationGrade::MEDIUM;
//    }
//    else if (gradeStr == "Крупный") {
//        grade = PopulationGrade::LARGE;
//    }
//
//    SettlementType type = SettlementType::CITY;
//    if (typeStr == "Посёлок") {
//        type = SettlementType::TOWN;
//    }
//    else if (typeStr == "Деревня") {
//        type = SettlementType::VILLAGE;
//    }
//
//    // Создание нового узла и добавление в список
//    CityNode* newNode = new CityNode(id, name, population, grade, type, head->next);
//    head->next = newNode;
//    idToCityMap.insert(id, newNode);
//    nameToIdMap[name] = id;
//}
//
//// Очистка списка городов
//void CityTable::clearList() {
//    CityNode* current = head->next;
//    while (current) {
//        CityNode* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    head->next = nullptr;
//    idToCityMap.clear();
//    nameToIdMap.clear();
//}
//
//// Загрузка данных из файла cities.txt
//void CityTable::loadFromFile() {
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
//// Сохранение данных в файл cities.txt
//void CityTable::saveToFile() {
//    std::ofstream file(filename);
//    for (CityNode* curr = head->next; curr; curr = curr->next) {
//        file << std::setw(5) << std::left << curr->id
//            << std::quoted(curr->name) << " "
//            << curr->population << " "
//            << std::quoted(populationGradeToString(curr->grade)) << " "
//            << std::quoted(settlementTypeToString(curr->type)) << "\n";
//    }
//}
//
//// Добавление нового города
//void CityTable::addCity(const std::string& name, int population, PopulationGrade grade, SettlementType type) {
//    const int& newId = generateNextId();
//    CityNode* newNode = new CityNode(newId, name, population, grade, type, head->next);
//    head->next = newNode;
//    idToCityMap.insert(newId, newNode);
//    nameToIdMap[name] = newId;
//    saveToFile();
//}
//
//// Удаление города по имени
//void CityTable::deleteCity(const std::string& name) {
//    auto it = nameToIdMap.find(name);
//    if (it == nameToIdMap.end()) return;
//
//    const int targetId = it->second;
//    CityNode* prev = head;
//    CityNode* current = head->next;
//
//    while (current) {
//        if (current->id == targetId) {
//            prev->next = current->next;
//            idToCityMap.remove(targetId);
//            nameToIdMap.erase(current->name);
//            delete current;
//            saveToFile();
//            return;
//        }
//        prev = current;
//        current = current->next;
//    }
//}
//
//// Получение названия города по ID
//std::string CityTable::getCityNameById(int id) const {
//    void* data;
//    return idToCityMap.get(id, data) ?
//        static_cast<CityNode*>(data)->name : "Неизвестный город";
//}
//
//// Получение ID города по названию
//int CityTable::getCityIdByName(const std::string& name) const {
//    auto it = nameToIdMap.find(name);
//    return (it != nameToIdMap.end()) ? it->second : -1;
//}
//
//// Преобразование PopulationGrade в строку
//std::string CityTable::populationGradeToString(PopulationGrade grade) {
//    switch (grade) {
//    case PopulationGrade::SMALL: return "Малый";
//    case PopulationGrade::MEDIUM: return "Средний";
//    case PopulationGrade::LARGE: return "Крупный";
//    default: return "Неизвестно";
//    }
//}
//
//// Преобразование SettlementType в строку
//std::string CityTable::settlementTypeToString(SettlementType type) {
//    switch (type) {
//    case SettlementType::CITY: return "Город";
//    case SettlementType::TOWN: return "Посёлок";
//    case SettlementType::VILLAGE: return "Деревня";
//    default: return "Неизвестно";
//    }
//}
//
//// Итератор: сброс указателя на начало списка
//void CityTable::cityIteratorReset() const {
//    currentIterator = head->next;
//}
//
//// Проверка наличия следующего элемента
//bool CityTable::cityIteratorHasNext() const {
//    return currentIterator != nullptr;
//}
//
//// Получение следующего города
//CityTable::CityInfo CityTable::cityIteratorNext() const {
//    CityInfo info;
//    if (!currentIterator) return info;
//
//    info.id = currentIterator->id;
//    info.name = currentIterator->name;
//    info.population = currentIterator->population;
//    info.grade = currentIterator->grade;
//    info.type = currentIterator->type;
//
//    currentIterator = currentIterator->next;
//    return info;
//}

#include "CityTable.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <set>
#include <regex>

// Конструктор: инициализация заголовочного узла и загрузка данных
CityTable::CityTable()
    : head(new CityNode(-1, "", 0, PopulationGrade::SMALL, SettlementType::CITY, nullptr)),
    currentFilter(nullptr),
    idWidth(5),
    nameWidth(20),
    populationWidth(12),
    typeWidth(10)
{
    loadFromFile();
    updateColumnWidths(); // Первоначальный расчет ширины столбцов
}

// Деструктор: очистка списка и фильтров
CityTable::~CityTable() {
    clearList();
    clearFilters();
    delete head;
}

// Загрузка данных из файла
void CityTable::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening cities file!" << std::endl;
        return;
    }

    clearList();
    std::string line;
    while (std::getline(file, line)) {
        parseLine(line);
    }
    updateColumnWidths(); // Обновляем ширину после загрузки
}

// Парсинг строки файла
void CityTable::parseLine(const std::string& line) {
    if (line.empty()) return;

    std::istringstream iss(line);
    int id, population;
    std::string name, gradeStr, typeStr;

    iss >> id >> std::quoted(name) >> population >> std::quoted(gradeStr) >> std::quoted(typeStr);

    // Конвертация строк в enum
    PopulationGrade grade = PopulationGrade::SMALL;
    if (gradeStr == "Medium") grade = PopulationGrade::MEDIUM;
    else if (gradeStr == "Large") grade = PopulationGrade::LARGE;

    SettlementType type = SettlementType::CITY;
    if (typeStr == "Town") type = SettlementType::TOWN;
    else if (typeStr == "Village") type = SettlementType::VILLAGE;

    addCityNode(id, name, population, grade, type);
}

// Добавление узла в список
void CityTable::addCityNode(int id, const std::string& name, int population,
    PopulationGrade grade, SettlementType type)
{
    CityNode* newNode = new CityNode(id, name, population, grade, type, head->next);
    head->next = newNode;
    idToCityMap.insert(id, newNode);
    nameToIdMap[name] = id;
}

// Обновление ширины столбцов на основе данных
void CityTable::updateColumnWidths() {
    CityNode* curr = head->next;
    int maxIdLen = 1;
    size_t maxNameLen = 0;

    while (curr) {
        // Расчет ширины для ID
        int idLen = static_cast<int>(std::to_string(curr->id).length());
        if (idLen > maxIdLen) maxIdLen = idLen;

        // Расчет ширины для названия
        if (curr->name.length() > maxNameLen) {
            maxNameLen = curr->name.length();
        }

        curr = curr->next;
    }

    idWidth = maxIdLen + 2;
    nameWidth = maxNameLen + 4;
}

// Форматирование узла для вывода с учетом ширины
std::string CityTable::formatNode(const CityNode* node) const {
    std::ostringstream oss;
    oss << std::left
        << std::setw(idWidth) << node->id
        << std::setw(nameWidth) << node->name
        << std::setw(populationWidth) << node->population
        << std::setw(typeWidth) << settlementTypeToString(node->type);
    return oss.str();
}

// Добавление фильтра
void CityTable::addFilter(const std::string& field, const std::string& pattern) {
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

// Применение всех активных фильтров
CityTable::CityNode* CityTable::applyFilters() const {
    CityNode* filteredHead = new CityNode(-1, "", 0, PopulationGrade::SMALL, SettlementType::CITY, nullptr);
    CityNode* tail = filteredHead;

    CityNode* curr = head->next;
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
            CityNode* newNode = cloneNode(curr);
            tail->next = newNode;
            tail = newNode;
        }
        curr = curr->next;
    }

    return filteredHead->next;
}

// Проверка соответствия поля фильтру
bool CityTable::matchField(const CityNode* node, const std::string& field,
    const std::string& pattern) const
{
    if (field == "name") {
        return std::regex_match(node->name, std::regex(pattern));
    }
    else if (field == "population") {
        return checkNumeric(node->population, pattern);
    }
    else if (field == "type") {
        return std::regex_match(settlementTypeToString(node->type),
            std::regex(pattern));
    }
    return false;
}

// Проверка числовых условий (>1000, <500 и т.д.)
bool CityTable::checkNumeric(int value, const std::string& pattern) const {
    if (pattern.empty()) return true;

    if (pattern[0] == '>') {
        return value > std::stoi(pattern.substr(1));
    }
    else if (pattern[0] == '<') {
        return value < std::stoi(pattern.substr(1));
    }
    return value == std::stoi(pattern);
}

// Очистка фильтров
void CityTable::clearFilters() {
    Filter* current = currentFilter;
    while (current) {
        Filter* next = current->next;
        delete current;
        current = next;
    }
    currentFilter = nullptr;
}

// Клонирование узла (для создания отфильтрованного списка)
CityTable::CityNode* CityTable::cloneNode(const CityNode* src) const {
    return new CityNode(
        src->id,
        src->name,
        src->population,
        src->grade,
        src->type,
        nullptr
    );
}

// Преобразование PopulationGrade в строку
std::string CityTable::populationGradeToString(PopulationGrade grade) {
    switch (grade) {
    case PopulationGrade::SMALL: return "Small";
    case PopulationGrade::MEDIUM: return "Medium";
    case PopulationGrade::LARGE: return "Large";
    default: return "Unknown";
    }
}

// Преобразование SettlementType в строку
std::string CityTable::settlementTypeToString(SettlementType type) {
    switch (type) {
    case SettlementType::CITY: return "City";
    case SettlementType::TOWN: return "Town";
    case SettlementType::VILLAGE: return "Village";
    default: return "Unknown";
    }
}

// Итератор: сброс указателя на начало
void CityTable::cityIteratorReset(CityNode* start) const {
    currentIterator = start ? start : head->next;
}

// Проверка наличия следующего элемента
bool CityTable::cityIteratorHasNext() const {
    return currentIterator != nullptr;
}

// Получение следующего элемента
CityTable::CityInfo CityTable::cityIteratorNext() const {
    CityInfo info;
    if (!currentIterator) return info;

    info.id = currentIterator->id;
    info.name = currentIterator->name;
    info.population = currentIterator->population;
    info.grade = currentIterator->grade;
    info.type = currentIterator->type;

    currentIterator = currentIterator->next;
    return info;
}

// Очистка списка
void CityTable::clearList() {
    CityNode* current = head->next;
    while (current) {
        CityNode* temp = current;
        current = current->next;
        delete temp;
    }
    head->next = nullptr;
    idToCityMap.clear();
    nameToIdMap.clear();
}