﻿//#include "FineTable.h"
//#include <fstream>
//#include <sstream>
//#include <stdexcept>
//#include <iomanip>
//using namespace std;
//
//// Конструктор: инициализация заголовочного узла и загрузка данных
//FineTable::FineTable()
//    : head(new FineNode(-1, 0.0, "", Severity::LIGHT, nullptr)),
//    currentIterator(nullptr),
//    idWidth(5),
//    amountWidth(10),
//    typeWidth(30),
//    severityWidth(8)
//{
//    loadFromFile();
//}
//
//// Деструктор: очистка списка и хеш-таблицы
//FineTable::~FineTable() {
//    FineNode* current = head->next;
//    while (current) {
//        FineNode* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    delete head;
//    idToFineMap.clear();
//    typeToIdMap.clear();
//}
//
//// Загрузка данных из файла
//void FineTable::loadFromFile() {
//    ifstream file("fines.txt");
//    if (!file.is_open()) {
//        cerr << "Error opening fines file!" << endl;
//        return;
//    }
//    // Очищаем существующие данные
//    FineNode* current = head->next;
//    while (current) {
//        FineNode* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    head->next = nullptr;
//    idToFineMap.clear();
//    typeToIdMap.clear();
//
//    string line;
//    while (getline(file, line)) {
//        parseLine(line);
//    }
//    file.close();
//}
//
//// Парсинг строки: "id amount \"type\" \"severity\""
//void FineTable::parseLine(const std::string& line) {
//    if (line.empty()) return;
//    istringstream iss(line);
//    int id;
//    double amount;
//    string type, severityStr;
//    iss >> id >> amount >> quoted(type) >> quoted(severityStr);
//
//    Severity severity = Severity::LIGHT;
//    if (severityStr == "Medium") severity = Severity::MEDIUM;
//    else if (severityStr == "Heavy") severity = Severity::HEAVY;
//
//    addFineNode(id, amount, type, severity);
//}
//
//// Добавление узла в список и в хеш-таблицу
//void FineTable::addFineNode(int id, double amount, const std::string& type,
//    Severity severity)
//{
//    FineNode* newNode = new FineNode(id, amount, type, severity, head->next);
//    head->next = newNode;
//    idToFineMap.insert(id, newNode);
//    typeToIdMap[type] = id;
//}
//
//// Добавление нового штрафа (с генерацией ID)
//void FineTable::addFine(const std::string& type, double amount,
//    Severity severity)
//{
//    if (typeToIdMap.count(type))
//        throw invalid_argument("Штраф с таким типом уже существует");
//
//    // Генерация ID: максимум существующего +1
//    int newId = 1;
//    for (const auto& pair : typeToIdMap) {
//        if (pair.second >= newId) newId = pair.second + 1;
//    }
//
//    addFineNode(newId, amount, type, severity);
//}
//
//// Итератор: сброс на начало
//void FineTable::fineIteratorReset() const {
//    currentIterator = head->next;
//}
//
//// Есть ли следующий?
//bool FineTable::fineIteratorHasNext() const {
//    return currentIterator != nullptr;
//}
//
//// Получение следующего
//FineTable::FineInfo FineTable::fineIteratorNext() const {
//    FineInfo info;
//    if (!currentIterator) return info;
//    info.id = currentIterator->id;
//    info.amount = currentIterator->amount;
//    info.type = currentIterator->type;
//    info.severity = currentIterator->severity;
//    currentIterator = currentIterator->next;
//    return info;
//}
//
//std::string FineTable::getFineTypeById(int id) const {
//    FineNode* node = idToFineMap.find<FineNode>(id);
//    return node ? node->type : "";
//}
//
//// Геттер: получить ID по типу штрафа
//int FineTable::getFineIdByType(const std::string& type) const {
//    auto it = typeToIdMap.find(type);
//    return (it != typeToIdMap.end()) ? it->second : -1;
//}
//
//// Геттер: получить сумму по ID
//double FineTable::getAmountById(int id) const {
//    FineNode* node = idToFineMap.find<FineNode>(id);
//    return node ? node->amount : 0.0;
//}
//
//// Удаление штрафа по типу (только при отсутствии связанных нарушений)
//void FineTable::deleteFine(const std::string& type) {
//    auto it = typeToIdMap.find(type);
//    if (it == typeToIdMap.end()) return;
//
//    int id = it->second;
//    FineNode* prev = head;
//    FineNode* curr = head->next;
//    while (curr) {
//        if (curr->id == id) {
//            prev->next = curr->next;
//            idToFineMap.remove(id);
//            typeToIdMap.erase(type);
//            delete curr;
//            return;
//        }
//        prev = curr;
//        curr = curr->next;
//    }
//}
//
//// Сохранение данных в файл
//void FineTable::saveToFile() const {
//    ofstream file("fines.txt");
//    if (!file.is_open()) {
//        cerr << "Error opening fines file for writing!" << endl;
//        return;
//    }
//    FineNode* curr = head->next;
//    while (curr) {
//        file << curr->id << ' '
//            << curr->amount << ' '
//            << quoted(curr->type) << ' '
//            << quoted(severityToString(curr->severity))
//            << '\n';
//        curr = curr->next;
//    }
//    file.close();
//}
//
//// Преобразование Severity в строку
//std::string FineTable::severityToString(Severity severity) {
//    switch (severity) {
//    case Severity::LIGHT:  return "Light";
//    case Severity::MEDIUM: return "Medium";
//    case Severity::HEAVY:  return "Heavy";
//    default:               return "Unknown";
//    }
//}

//// FineTable.cpp
//#include "FineTable.h"
//#include <fstream>
//#include <sstream>
//#include <stdexcept>
//#include <iomanip>
//using namespace std;
//
//FineTable::FineTable()
//    : head(new FineNode(-1, 0.0, "", Severity::LIGHT, nullptr)),
//    currentIterator(nullptr),
//    idWidth(5),
//    amountWidth(10),
//    typeWidth(30),
//    severityWidth(8)
//{
//    loadFromFile();
//}
//
//FineTable::~FineTable() {
//    FineNode* current = head->next;
//    while (current) {
//        FineNode* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    delete head;
//    idToFineMap.clear();
//    typeToIdMap.clear();
//}
//
//void FineTable::loadFromFile() {
//    ifstream file("fines.txt");
//    if (!file.is_open()) {
//        cerr << "Error opening fines file!" << endl;
//        return;
//    }
//    FineNode* current = head->next;
//    while (current) {
//        FineNode* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    head->next = nullptr;
//    idToFineMap.clear();
//    typeToIdMap.clear();
//
//    string line;
//    while (getline(file, line)) {
//        parseLine(line);
//    }
//    file.close();
//}
//
//void FineTable::parseLine(const std::string& line) {
//    if (line.empty()) return;
//    istringstream iss(line);
//    int id;
//    double amount;
//    string type, severityStr;
//    iss >> id >> amount >> quoted(type) >> quoted(severityStr);
//
//    Severity severity = Severity::LIGHT;
//    if (severityStr == "Medium") severity = Severity::MEDIUM;
//    else if (severityStr == "Heavy") severity = Severity::HEAVY;
//
//    addFineNode(id, amount, type, severity);
//}
//
//void FineTable::addFine(const std::string& type, double amount,
//    Severity severity)
//{
//    if (typeToIdMap.count(type))
//        throw invalid_argument("Fine with that type already exists");
//    int newId = 1;
//    for (auto& pair : typeToIdMap) {
//        if (pair.second >= newId) newId = pair.second + 1;
//    }
//    addFineNode(newId, amount, type, severity);
//}
//
//void FineTable::addFineNode(int id, double amount, const std::string& type,
//    Severity severity)
//{
//    FineNode* newNode = new FineNode(id, amount, type, severity, head->next);
//    head->next = newNode;
//    idToFineMap.insert(id, newNode);
//    typeToIdMap[type] = id;
//}
//
//void FineTable::deleteFine(const std::string& type) {
//    auto it = typeToIdMap.find(type);
//    if (it == typeToIdMap.end()) return;
//    int id = it->second;
//    FineNode* prev = head;
//    FineNode* curr = head->next;
//    while (curr) {
//        if (curr->id == id) {
//            prev->next = curr->next;
//            idToFineMap.remove(id);
//            typeToIdMap.erase(type);
//            delete curr;
//            return;
//        }
//        prev = curr;
//        curr = curr->next;
//    }
//}
//
//void FineTable::fineIteratorReset() const {
//    currentIterator = head->next;
//}
//
//bool FineTable::fineIteratorHasNext() const {
//    return currentIterator != nullptr;
//}
//
//FineTable::FineInfo FineTable::fineIteratorNext() const {
//    FineInfo info{};
//    if (!currentIterator) return info;
//    info.id = currentIterator->id;
//    info.amount = currentIterator->amount;
//    info.type = currentIterator->type;
//    info.severity = currentIterator->severity;
//    currentIterator = currentIterator->next;
//    return info;
//}
//
//int FineTable::getFineIdByType(const std::string& type) const {
//    auto it = typeToIdMap.find(type);
//    return (it != typeToIdMap.end()) ? it->second : -1;
//}
//
//double FineTable::getAmountById(int id) const {
//    FineNode* node = idToFineMap.find<FineNode>(id);
//    return node ? node->amount : 0.0;
//}
//
//string FineTable::severityToString(Severity severity) {
//    switch (severity) {
//    case Severity::LIGHT:  return "Light";
//    case Severity::MEDIUM: return "Medium";
//    case Severity::HEAVY:  return "Heavy";
//    default:               return "Unknown";
//    }
//}
//
//string FineTable::getFineTypeById(int id) const {
//    FineNode* node = idToFineMap.find<FineNode>(id);
//    return node ? node->type : "";
//}
//
//// Редактирование
//bool FineTable::updateFineType(int id, const std::string& newType) {
//    if (typeToIdMap.count(newType)) return false;
//    FineNode* node = idToFineMap.find<FineNode>(id);
//    if (!node) return false;
//    typeToIdMap.erase(node->type);
//    node->type = newType;
//    typeToIdMap[newType] = id;
//    return true;
//}
//
//bool FineTable::updateFineAmount(int id, double newAmount) {
//    FineNode* node = idToFineMap.find<FineNode>(id);
//    if (!node) return false;
//    node->amount = newAmount;
//    return true;
//}
//
//bool FineTable::updateFineSeverity(int id, Severity newSeverity) {
//    FineNode* node = idToFineMap.find<FineNode>(id);
//    if (!node) return false;
//    node->severity = newSeverity;
//    return true;
//}
//
//void FineTable::saveToFile() const {
//    ofstream file("fines.txt");
//    if (!file.is_open()) {
//        cerr << "Error opening fines file for writing!" << endl;
//        return;
//    }
//    FineNode* curr = head->next;
//    while (curr) {
//        file << curr->id << ' '
//            << curr->amount << ' '
//            << quoted(curr->type) << ' '
//            << quoted(severityToString(curr->severity))
//            << '\n';
//        curr = curr->next;
//    }
//    file.close();
//}


// FineTable.cpp
#include "FineTable.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
using namespace std;

FineTable::FineTable()
    : head(new FineNode(-1, 0.0, "", Severity::LIGHT, nullptr)),
    currentIterator(nullptr),
    currentFilter(nullptr),
    idWidth(5),
    amountWidth(10),
    typeWidth(30),
    severityWidth(8)
{
    loadFromFile();
}

FineTable::~FineTable() {
    FineNode* current = head->next;
    while (current) {
        FineNode* temp = current;
        current = current->next;
        delete temp;
    }
    delete head;
    idToFineMap.clear();
    typeToIdMap.clear();

    Filter* f = currentFilter;
    while (f) {
        Filter* nxt = f->next;
        delete f;
        f = nxt;
    }
}

void FineTable::loadFromFile() {
    ifstream file("fines.txt");
    if (!file.is_open()) {
        cerr << "Error opening fines file!" << endl;
        return;
    }
    FineNode* current = head->next;
    while (current) {
        FineNode* temp = current;
        current = current->next;
        delete temp;
    }
    head->next = nullptr;
    idToFineMap.clear();
    typeToIdMap.clear();

    string line;
    while (getline(file, line)) {
        parseLine(line);
    }
    file.close();
}

void FineTable::parseLine(const std::string& line) {
    if (line.empty()) return;
    istringstream iss(line);
    int id;
    double amount;
    string type, severityStr;
    iss >> id >> amount >> quoted(type) >> quoted(severityStr);

    Severity severity = Severity::LIGHT;
    if (severityStr == "Medium") severity = Severity::MEDIUM;
    else if (severityStr == "Heavy") severity = Severity::HEAVY;

    addFineNode(id, amount, type, severity);
}

void FineTable::addFineNode(int id, double amount, const std::string& type,
    Severity severity)
{
    FineNode* newNode = new FineNode(id, amount, type, severity, head->next);
    head->next = newNode;
    idToFineMap.insert(id, newNode);
    typeToIdMap[type] = id;
}

void FineTable::addFine(const std::string& type, double amount,
    Severity severity)
{
    if (typeToIdMap.count(type))
        throw invalid_argument("Fine with that type already exists");

    int newId = 1;
    for (auto& pair : typeToIdMap) {
        if (pair.second >= newId) newId = pair.second + 1;
    }
    addFineNode(newId, amount, type, severity);
}

void FineTable::deleteFine(const std::string& type) {
    auto it = typeToIdMap.find(type);
    if (it == typeToIdMap.end()) return;
    int id = it->second;
    FineNode* prev = head;
    FineNode* curr = head->next;
    while (curr) {
        if (curr->id == id) {
            prev->next = curr->next;
            idToFineMap.remove(id);
            typeToIdMap.erase(type);
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void FineTable::saveToFile() const {
    ofstream file("fines.txt");
    if (!file.is_open()) {
        cerr << "Error opening fines file for writing!" << endl;
        return;
    }
    FineNode* curr = head->next;
    while (curr) {
        file << curr->id << ' '
            << curr->amount << ' '
            << quoted(curr->type) << ' '
            << quoted(severityToString(curr->severity))
            << '\n';
        curr = curr->next;
    }
    file.close();
}

void FineTable::fineIteratorReset() const {
    currentIterator = head->next;
}

bool FineTable::fineIteratorHasNext() const {
    return currentIterator != nullptr;
}

FineTable::FineInfo FineTable::fineIteratorNext() const {
    FineInfo info{};
    if (!currentIterator) return info;
    info.id = currentIterator->id;
    info.amount = currentIterator->amount;
    info.type = currentIterator->type;
    info.severity = currentIterator->severity;
    currentIterator = currentIterator->next;
    return info;
}

int FineTable::getFineIdByType(const std::string& type) const {
    auto it = typeToIdMap.find(type);
    return (it != typeToIdMap.end()) ? it->second : -1;
}

double FineTable::getAmountById(int id) const {
    FineNode* node = idToFineMap.find<FineNode>(id);
    return node ? node->amount : 0.0;
}

std::string FineTable::severityToString(Severity severity) {
    switch (severity) {
    case Severity::LIGHT:  return "Light";
    case Severity::MEDIUM: return "Medium";
    case Severity::HEAVY:  return "Heavy";
    default:               return "Unknown";
    }
}

std::string FineTable::getFineTypeById(int id) const {
    FineNode* node = idToFineMap.find<FineNode>(id);
    return node ? node->type : "";
}

bool FineTable::updateFineType(int id, const std::string& newType) {
    if (typeToIdMap.count(newType)) return false;
    FineNode* node = idToFineMap.find<FineNode>(id);
    if (!node) return false;
    typeToIdMap.erase(node->type);
    node->type = newType;
    typeToIdMap[newType] = id;
    return true;
}

bool FineTable::updateFineAmount(int id, double newAmount) {
    FineNode* node = idToFineMap.find<FineNode>(id);
    if (!node) return false;
    node->amount = newAmount;
    return true;
}

bool FineTable::updateFineSeverity(int id, Severity newSeverity) {
    FineNode* node = idToFineMap.find<FineNode>(id);
    if (!node) return false;
    node->severity = newSeverity;
    return true;
}

void FineTable::addFilter(const std::string& field, int cmpType, const std::string& value) {
    Filter* newFilter = new Filter{ field, cmpType, value, nullptr };
    if (!currentFilter) {
        currentFilter = newFilter;
    }
    else {
        Filter* temp = currentFilter;
        while (temp->next) temp = temp->next;
        temp->next = newFilter;
    }
}

void FineTable::clearFilters() {
    Filter* f = currentFilter;
    while (f) {
        Filter* nxt = f->next;
        delete f;
        f = nxt;
    }
    currentFilter = nullptr;
}

bool FineTable::matchField(const FineNode* node, const std::string& field,
    int cmpType, const std::string& value) const
{
    if (field == "type") {
        if (cmpType == 1) return node->type.find(value) != string::npos;
        if (cmpType == 2) return node->type == value;
    }
    else if (field == "amount") {
        double v = stod(value);
        if (cmpType == 3) return node->amount < v;
        if (cmpType == 4) return node->amount > v;
        return node->amount == v;
    }
    return false;
}

FineTable::FineInfo* FineTable::applyFilters(int& outCount) const {
    int count = 0;
    FineNode* curr = head->next;
    while (curr) {
        bool match = true;
        Filter* f = currentFilter;
        while (f) {
            if (!matchField(curr, f->field, f->cmpType, f->value)) {
                match = false;
                break;
            }
            f = f->next;
        }
        if (match) count++;
        curr = curr->next;
    }
    if (count == 0) {
        outCount = 0;
        return nullptr;
    }
    FineInfo* arr = new FineInfo[count];
    int idx = 0;
    curr = head->next;
    while (curr) {
        bool match = true;
        Filter* f = currentFilter;
        while (f) {
            if (!matchField(curr, f->field, f->cmpType, f->value)) {
                match = false;
                break;
            }
            f = f->next;
        }
        if (match) {
            arr[idx++] = cloneInfo(curr);
        }
        curr = curr->next;
    }
    outCount = count;
    return arr;
}

FineTable::FineInfo FineTable::cloneInfo(const FineNode* node) const {
    FineInfo info;
    info.id = node->id;
    info.amount = node->amount;
    info.type = node->type;
    info.severity = node->severity;
    return info;
}

int FineTable::getFilterCount() const {
    int count = 0;
    Filter* f = currentFilter;
    while (f) {
        count++;
        f = f->next;
    }
    return count;
}

std::string FineTable::getFilterDescription(int index) const {
    int i = 0;
    Filter* f = currentFilter;
    while (f) {
        if (i == index) {
            ostringstream oss;
            if (f->field == "type") {
                if (f->cmpType == 1) oss << "Type contains \"" << f->value << "\"";
                else oss << "Type equals \"" << f->value << "\"";
            }
            else if (f->field == "amount") {
                if (f->cmpType == 3) oss << "Amount < " << f->value;
                else if (f->cmpType == 4) oss << "Amount > " << f->value;
                else oss << "Amount = " << f->value;
            }
            return oss.str();
        }
        f = f->next;
        i++;
    }
    return "";
}

void FineTable::removeFilterAt(int index) {
    if (!currentFilter) return;
    if (index == 0) {
        Filter* toDelete = currentFilter;
        currentFilter = toDelete->next;
        delete toDelete;
        return;
    }
    int i = 0;
    Filter* prev = currentFilter;
    while (prev && prev->next) {
        if (i + 1 == index) {
            Filter* toDelete = prev->next;
            prev->next = toDelete->next;
            delete toDelete;
            return;
        }
        prev = prev->next;
        i++;
    }
}
