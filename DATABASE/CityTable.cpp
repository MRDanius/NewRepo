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
//CityTable::CityTable() : head(new City{ 0, "���������_������", nullptr }), idToCityMap() {
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
//    head = new City{ 0, "���������_������", nullptr };
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
//    idToCityMap.insert(id, newCity);  // <- �������� ��� ������
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
//    idToCityMap.insert(newId, newCity);  // <- �������� ��� ������
//    save();
//}
//
//string CityTable::getCityName(int cityId) {
//    void* cityPtr;
//    if (idToCityMap.get(cityId, cityPtr)) {  // <- �������� ������ �����
//        City* city = static_cast<City*>(cityPtr);
//        return city->name;
//    }
//    return "�����������_�����";
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
//            idToCityMap.remove(cityId);  // <- �������� ��� ������
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
//    // ����������� ����� � enum
//    PopulationGrade grade = PopulationGrade::SMALL;
//    if (gradeStr == "�������") grade = PopulationGrade::MEDIUM;
//    else if (gradeStr == "�������") grade = PopulationGrade::LARGE;
//
//    SettlementType type = SettlementType::CITY;
//    if (typeStr == "������") type = SettlementType::TOWN;
//    else if (typeStr == "�������") type = SettlementType::VILLAGE;
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
//        static_cast<CityNode*>(data)->name : "����������� �����";
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
//    case PopulationGrade::SMALL: return "�����";
//    case PopulationGrade::MEDIUM: return "�������";
//    case PopulationGrade::LARGE: return "�������";
//    default: return "����������";
//    }
//}
//
//std::string CityTable::settlementTypeToString(SettlementType type) {
//    switch (type) {
//    case SettlementType::CITY: return "�����";
//    case SettlementType::TOWN: return "������";
//    case SettlementType::VILLAGE: return "�������";
//    default: return "����������";
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
//// �����������: ��������� ������ �� ����� ��� �������� �������
//CityTable::CityTable() : head(new CityNode(-1, "", 0, PopulationGrade::SMALL, SettlementType::CITY, nullptr)) {
//    loadFromFile();
//}
//
//// ����������: ����������� ������ � ������� ������
//CityTable::~CityTable() {
//    clearList();
//    delete head;
//}
//
//// ��������� ����������� ID ��� ������ ������
//const int& CityTable::generateNextId() {
//    static int nextId = 1;
//    std::set<int> usedIds;
//    for (CityNode* curr = head->next; curr; curr = curr->next)
//        usedIds.insert(curr->id);
//    while (usedIds.count(nextId)) nextId++;
//    return nextId;
//}
//
//// ������� ������ �� ����� � ������ CityNode
//void CityTable::parseLine(const std::string& line) {
//    if (line.empty()) return;
//
//    std::istringstream iss(line);
//    int id, population;
//    std::string name, gradeStr, typeStr;
//
//    iss >> id >> std::quoted(name) >> population >> std::quoted(gradeStr) >> std::quoted(typeStr);
//
//    // ����������� ����� � enum
//    PopulationGrade grade = PopulationGrade::SMALL;
//    if (gradeStr == "�������") {
//        grade = PopulationGrade::MEDIUM;
//    }
//    else if (gradeStr == "�������") {
//        grade = PopulationGrade::LARGE;
//    }
//
//    SettlementType type = SettlementType::CITY;
//    if (typeStr == "������") {
//        type = SettlementType::TOWN;
//    }
//    else if (typeStr == "�������") {
//        type = SettlementType::VILLAGE;
//    }
//
//    // �������� ������ ���� � ���������� � ������
//    CityNode* newNode = new CityNode(id, name, population, grade, type, head->next);
//    head->next = newNode;
//    idToCityMap.insert(id, newNode);
//    nameToIdMap[name] = id;
//}
//
//// ������� ������ �������
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
//// �������� ������ �� ����� cities.txt
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
//// ���������� ������ � ���� cities.txt
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
//// ���������� ������ ������
//void CityTable::addCity(const std::string& name, int population, PopulationGrade grade, SettlementType type) {
//    const int& newId = generateNextId();
//    CityNode* newNode = new CityNode(newId, name, population, grade, type, head->next);
//    head->next = newNode;
//    idToCityMap.insert(newId, newNode);
//    nameToIdMap[name] = newId;
//    saveToFile();
//}
//
//// �������� ������ �� �����
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
//// ��������� �������� ������ �� ID
//std::string CityTable::getCityNameById(int id) const {
//    void* data;
//    return idToCityMap.get(id, data) ?
//        static_cast<CityNode*>(data)->name : "����������� �����";
//}
//
//// ��������� ID ������ �� ��������
//int CityTable::getCityIdByName(const std::string& name) const {
//    auto it = nameToIdMap.find(name);
//    return (it != nameToIdMap.end()) ? it->second : -1;
//}
//
//// �������������� PopulationGrade � ������
//std::string CityTable::populationGradeToString(PopulationGrade grade) {
//    switch (grade) {
//    case PopulationGrade::SMALL: return "�����";
//    case PopulationGrade::MEDIUM: return "�������";
//    case PopulationGrade::LARGE: return "�������";
//    default: return "����������";
//    }
//}
//
//// �������������� SettlementType � ������
//std::string CityTable::settlementTypeToString(SettlementType type) {
//    switch (type) {
//    case SettlementType::CITY: return "�����";
//    case SettlementType::TOWN: return "������";
//    case SettlementType::VILLAGE: return "�������";
//    default: return "����������";
//    }
//}
//
//// ��������: ����� ��������� �� ������ ������
//void CityTable::cityIteratorReset() const {
//    currentIterator = head->next;
//}
//
//// �������� ������� ���������� ��������
//bool CityTable::cityIteratorHasNext() const {
//    return currentIterator != nullptr;
//}
//
//// ��������� ���������� ������
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

// CityTable.cpp

// CityTable.cpp

#include "CityTable.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <iomanip>
using namespace std;

// �����������: ������������� ������������� ���� � �������� ������
CityTable::CityTable()
    : head(new CityNode(-1, "", 0, PopulationGrade::SMALL, SettlementType::CITY, nullptr)),
    currentFilter(nullptr),
    idWidth(5),
    nameWidth(20),
    populationWidth(12),
    typeWidth(10)
{
    loadFromFile();
    updateColumnWidths(); // �������������� ������ ������ ��������
}

// ����������: ������� ������ � ��������
CityTable::~CityTable() {
    // ������� ��� ���� ������
    CityNode* curr = head->next;
    while (curr) {
        CityNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete head;
    // ������� �������
    clearFilters();
}

// �������� ������ �� �����
void CityTable::loadFromFile() {
    std::ifstream file("cities.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening cities file!" << std::endl;
        return;
    }
    // ������� ������������ ������
    CityNode* current = head->next;
    while (current) {
        CityNode* temp = current;
        current = current->next;
        delete temp;
    }
    head->next = nullptr;
    idToCityMap.clear();
    nameToIdMap.clear();

    std::string line;
    while (std::getline(file, line)) {
        parseLine(line);
    }
    updateColumnWidths(); // ��������� ������ ����� ��������
}

// ������� ������: "id \"name\" population \"grade\" \"type\""
void CityTable::parseLine(const std::string& line) {
    if (line.empty()) return;
    std::istringstream iss(line);
    int id, population;
    std::string name, gradeStr, typeStr;
    iss >> id >> std::quoted(name) >> population >> std::quoted(gradeStr) >> std::quoted(typeStr);

    // ����������� ������ � enum
    PopulationGrade grade = PopulationGrade::SMALL;
    if (gradeStr == "Medium")  grade = PopulationGrade::MEDIUM;
    else if (gradeStr == "Large") grade = PopulationGrade::LARGE;

    SettlementType type = SettlementType::CITY;
    if (typeStr == "Town")    type = SettlementType::TOWN;
    else if (typeStr == "Village") type = SettlementType::VILLAGE;

    addCityNode(id, name, population, grade, type);
}

// ���������� ���� � ������ � � ���-�������
void CityTable::addCityNode(int id, const std::string& name, int population,
    PopulationGrade grade, SettlementType type)
{
    CityNode* newNode = new CityNode(id, name, population, grade, type, head->next);
    head->next = newNode;
    idToCityMap.insert(id, newNode);
    nameToIdMap[name] = id;
}

// ���������� ������ ������ (� ���������� ID)
void CityTable::addCity(const std::string& name, int population,
    PopulationGrade grade, SettlementType type)
{
    // ��������� ID: �������� ������������� +1
    int newId = 1;
    for (const auto& pair : nameToIdMap) {
        if (pair.second >= newId) newId = pair.second + 1;
    }
    addCityNode(newId, name, population, grade, type);
}

// ���������� ������ �������� (ID � name) �� ������ ������
void CityTable::updateColumnWidths() {
    CityNode* curr = head->next;
    int maxIdLen = 1;
    size_t maxNameLen = 0;
    while (curr) {
        int idLen = static_cast<int>(std::to_string(curr->id).length());
        if (idLen > maxIdLen) maxIdLen = idLen;
        if (curr->name.length() > maxNameLen) {
            maxNameLen = curr->name.length();
        }
        curr = curr->next;
    }
    idWidth = maxIdLen + 2;
    nameWidth = static_cast<int>(maxNameLen) + 4;
}

// �������������� ���� ��� ������ � ������ ������ ��������
std::string CityTable::formatNode(const CityNode* node) const {
    std::ostringstream oss;
    oss << std::left
        << std::setw(idWidth) << node->id
        << std::setw(nameWidth) << node->name
        << std::setw(populationWidth) << node->population
        << std::setw(typeWidth) << settlementTypeToString(node->type);
    return oss.str();
}

// ���������� ������� (������� ��������� List)
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

// ������� ��� �������
void CityTable::clearFilters() {
    Filter* current = currentFilter;
    while (current) {
        Filter* next = current->next;
        delete current;
        current = next;
    }
    currentFilter = nullptr;
}

// ���������� ���� �������� ��������; ���������� ����� ������ ��������������� �����
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

// �������� ������������ ���������� ���� ������� (��� name � type � regex; ��� population � �������� ��������)
bool CityTable::matchField(const CityNode* node, const std::string& field, const std::string& pattern) const {
    if (field == "name") {
        return std::regex_match(node->name, std::regex(pattern));
    }
    else if (field == "population") {
        return checkNumeric(node->population, pattern);
    }
    else if (field == "type") {
        return std::regex_match(settlementTypeToString(node->type), std::regex(pattern));
    }
    return false;
}

// �������� ��������� �������: ">=1000", "<500" ��� ������ ���������
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

// ������������ ���� (��� ����������� next)
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

// �������������� PopulationGrade � ������
std::string CityTable::populationGradeToString(PopulationGrade grade) {
    switch (grade) {
    case PopulationGrade::SMALL:  return "Small";
    case PopulationGrade::MEDIUM: return "Medium";
    case PopulationGrade::LARGE:  return "Large";
    default:                      return "Unknown";
    }
}

// �������������� SettlementType � ������
std::string CityTable::settlementTypeToString(SettlementType type) {
    switch (type) {
    case SettlementType::CITY:    return "City";
    case SettlementType::TOWN:    return "Town";
    case SettlementType::VILLAGE: return "Village";
    default:                      return "Unknown";
    }
}

// �������� �� ������ �������: ����� �� ������ (��� �� ���������� ����)
void CityTable::cityIteratorReset(CityNode* start) const {
    currentIterator = start ? start : head->next;
}

// �������� ������� ���������� �������� ���������
bool CityTable::cityIteratorHasNext() const {
    return currentIterator != nullptr;
}

// ��������� ���������� �������� ���������
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

// �������� ������ �� �����: ������� ID, ������� ���� �� ������ � ���-������
void CityTable::deleteCity(const std::string& name) {
    auto it = nameToIdMap.find(name);
    if (it == nameToIdMap.end()) return;

    int id = it->second;
    CityNode* prev = head;
    CityNode* curr = head->next;
    while (curr) {
        if (curr->id == id) {
            prev->next = curr->next;
            idToCityMap.remove(id);
            nameToIdMap.erase(name);
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// ���������� �������� ������ ������� � ����
void CityTable::saveToFile() const {
    std::ofstream file("cities.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening cities file for writing!" << std::endl;
        return;
    }
    CityNode* curr = head->next;
    while (curr) {
        file << curr->id << ' '
            << std::quoted(curr->name) << ' '
            << curr->population << ' '
            << std::quoted(populationGradeToString(curr->grade)) << ' '
            << std::quoted(settlementTypeToString(curr->type))
            << '\n';
        curr = curr->next;
    }
    file.close();
}

// ������: ���������� ��� ������ �� ��� ID (��� ������ ������, ���� �� ������)
std::string CityTable::getCityNameById(int id) const {
    CityNode* node = idToCityMap.find<CityNode>(id);
    return node ? node->name : "";
}

// ������: ���������� ID ������ �� ��� ����� (��� -1, ���� �� ������)
int CityTable::getCityIdByName(const std::string& name) const {
    auto it = nameToIdMap.find(name);
    return (it != nameToIdMap.end()) ? it->second : -1;
}
