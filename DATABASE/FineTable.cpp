//// FineTable.cpp
//#include "FineTable.h"
//#include <fstream>
//#include <sstream>
//#include <iomanip>
//#include <iostream>
//#include <cctype>
//#include <set>
//
//using namespace std;
//
//FineTable::FineTable() : head(new Fine{ 0, 0.0, "", nullptr }), idToFineMap() {
//    load();
//}
//
//FineTable::~FineTable() {
//    clear();
//}
//
//void FineTable::clear() {
//    Fine* current = head;
//    while (current) {
//        Fine* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    head = new Fine{ 0, 0.0, "", nullptr };
//    idToFineMap.clear();
//}
//
//int FineTable::getNextId() {
//    set<int> usedIds;
//    Fine* current = head->next;
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
//void FineTable::parseLine(const string& line) {
//    if (line.empty()) return;
//
//    string id_str = line.substr(0, ID_LENGTH);
//    id_str.erase(id_str.find_last_not_of(' ') + 1);
//    int id = stoi(id_str);
//
//    string data = line.substr(ID_LENGTH);
//    istringstream iss(data);
//    double amount;
//    string type;
//    iss >> amount >> type;
//
//    Fine* newFine = new Fine{ id, amount, type, head->next };
//    head->next = newFine;
//    idToFineMap.insert(id, newFine);
//}
//
//void FineTable::load() {
//    ifstream file(filename);
//    string line;
//    clear();
//    while (getline(file, line)) {
//        parseLine(line);
//    }
//}
//
//void FineTable::save() {
//    ofstream file(filename);
//    Fine* current = head->next;
//    while (current) {
//        file << setw(ID_LENGTH) << left << current->id
//            << current->amount << " "
//            << current->type << endl;
//        current = current->next;
//    }
//}
//
//void FineTable::addFine(double amount, const string& type) {
//    int newId = getNextId();
//    Fine* newFine = new Fine{ newId, amount, type, head->next };
//    head->next = newFine;
//    idToFineMap.insert(newId, newFine);
//    save();
//}
//
//FineTable::Fine* FineTable::getFineById(int fineId) {
//    void* finePtr;
//    if (idToFineMap.get(fineId, finePtr)) {  // <- �������� �����
//        return static_cast<Fine*>(finePtr);
//    }
//    return nullptr;
//}
//
//FineTable::Fine* FineTable::getAllFines() {
//    return head->next;
//}
//
//void FineTable::deleteRecord(int fineId) {
//    Fine* prev = head;
//    Fine* current = head->next;
//    while (current) {
//        if (current->id == fineId) {
//            prev->next = current->next;
//            idToFineMap.remove(fineId);
//            delete current;
//            save();
//            return;
//        }
//        prev = current;
//        current = current->next;
//    }
//}
//
//void FineTable::updateReferences(int oldId, int newId) {}


//#include "FineTable.h"
//#include <fstream>
//#include <sstream>
//#include <iomanip>
//#include <set>
//
//FineTable::FineTable()
//    : head(new FineNode(-1, "", 0.0, Severity::LIGHT, nullptr)),
//    currentIterator(nullptr) {
//    loadFromFile();
//}
//
//FineTable::~FineTable() {
//    clearList();
//    delete head;
//}
//
//const int& FineTable::generateNextId() {
//    static int nextId = 1;
//    std::set<int> usedIds;
//    for (FineNode* curr = head->next; curr; curr = curr->next)
//        usedIds.insert(curr->id);
//    while (usedIds.count(nextId)) nextId++;
//    return nextId;
//}
//
//void FineTable::parseLine(const std::string& line) {
//    if (line.empty()) return;
//
//    std::istringstream iss(line);
//    int id;
//    std::string type, severityStr;
//    double amount;
//
//    iss >> id >> std::quoted(type) >> amount >> std::quoted(severityStr);
//
//    Severity severity = Severity::LIGHT;
//    if (severityStr == "�������") severity = Severity::MEDIUM;
//    else if (severityStr == "�������") severity = Severity::HEAVY;
//
//    FineNode* newNode = new FineNode(id, type, amount, severity, head->next);
//    head->next = newNode;
//    idToFineMap.insert(id, newNode);
//    typeToIdMap[type] = id;
//}
//
//void FineTable::clearList() {
//    FineNode* current = head->next;
//    while (current) {
//        FineNode* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    head->next = nullptr;
//    idToFineMap.clear();
//    typeToIdMap.clear();
//}
//
//void FineTable::loadFromFile() {
//    std::ifstream file(filename);
//    if (!file.is_open()) return;
//
//    clearList();
//    std::string line;
//    while (std::getline(file, line))
//        parseLine(line);
//}
//
//void FineTable::saveToFile() {
//    std::ofstream file(filename);
//    for (FineNode* curr = head->next; curr; curr = curr->next) {
//        file << std::setw(5) << std::left << curr->id
//            << std::quoted(curr->type) << " "
//            << curr->amount << " "
//            << std::quoted(severityToString(curr->severity)) << "\n";
//    }
//}
//
//void FineTable::addFine(const std::string& type, double amount, Severity severity) {
//    const int& newId = generateNextId();
//    FineNode* newNode = new FineNode(newId, type, amount, severity, head->next);
//    head->next = newNode;
//    idToFineMap.insert(newId, newNode);
//    typeToIdMap[type] = newId;
//    saveToFile();
//}
//
//void FineTable::deleteFine(const std::string& type) {
//    auto it = typeToIdMap.find(type);
//    if (it == typeToIdMap.end()) return;
//
//    const int& targetId = it->second;
//    FineNode* prev = head;
//    FineNode* current = head->next;
//    while (current) {
//        if (current->id == targetId) {
//            prev->next = current->next;
//            idToFineMap.remove(targetId);
//            typeToIdMap.erase(current->type);
//            delete current;
//            saveToFile();
//            return;
//        }
//        prev = current;
//        current = current->next;
//    }
//}
//
//std::string FineTable::severityToString(Severity severity) {
//    switch (severity) {
//    case Severity::LIGHT: return "������";
//    case Severity::MEDIUM: return "�������";
//    case Severity::HEAVY: return "�������";
//    default: return "����������";
//    }
//}
//
//const int& FineTable::getFineIdByType(const std::string& type) const {
//    static const int invalidId = -1;
//    auto it = typeToIdMap.find(type);
//    return (it != typeToIdMap.end()) ? it->second : invalidId;
//}
//
//FineTable::FineInfo FineTable::getFineInfoById(int fineId) const {
//    FineInfo info;
//    void* data;
//    if (idToFineMap.get(fineId, data)) {
//        FineNode* fine = static_cast<FineNode*>(data);
//        info.type = fine->type;
//        info.amount = fine->amount;
//        info.severity = fine->severity;
//    }
//    return info;
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
//FineTable::FineInfo FineTable::fineIteratorNext() {
//    FineInfo info;
//    if (!currentIterator) return info;
//
//    info.type = currentIterator->type;
//    info.amount = currentIterator->amount;
//    info.severity = currentIterator->severity;
//
//    currentIterator = currentIterator->next;
//    return info;
//}


#include "FineTable.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <set>
#include <iostream>

// �����������: ������������� ������ � �������� ������
FineTable::FineTable()
    : head(new FineNode(-1, "", 0.0, Severity::LIGHT, nullptr)),
    currentIterator(nullptr) {
    loadFromFile();
}

// ����������: ������� ������ � ������������ ������
FineTable::~FineTable() {
    clearList();
    delete head;
}

// ��������� ����������� ID ��� ������ ������
const int& FineTable::generateNextId() {
    static int nextId = 1;
    std::set<int> usedIds;
    for (FineNode* curr = head->next; curr; curr = curr->next)
        usedIds.insert(curr->id);
    while (usedIds.count(nextId)) nextId++;
    return nextId;
}

// ������� ������ �� ����� � ������ FineNode
void FineTable::parseLine(const std::string& line) {
    if (line.empty()) return;

    std::istringstream iss(line);
    int id;
    std::string type, severityStr;
    double amount;

    iss >> id >> std::quoted(type) >> amount >> std::quoted(severityStr);

    // ����������� ������ � enum Severity
    Severity severity = Severity::LIGHT;
    if (severityStr == "�������")
        severity = Severity::MEDIUM;
    else if (severityStr == "�������")
        severity = Severity::HEAVY;

    // �������� ���� � ���������� � ������
    FineNode* newNode = new FineNode(id, type, amount, severity, head->next);
    head->next = newNode;
    idToFineMap.insert(id, newNode);
    typeToIdMap[type] = id;
}

// ������� ������ �������
void FineTable::clearList() {
    FineNode* current = head->next;
    while (current) {
        FineNode* temp = current;
        current = current->next;
        delete temp;
    }
    head->next = nullptr;
    idToFineMap.clear();
    typeToIdMap.clear();
}

// �������� ������ �� ����� fines.txt
void FineTable::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    clearList();
    std::string line;
    while (std::getline(file, line)) {
        parseLine(line);
    }
}

// ���������� ������ � ���� fines.txt
void FineTable::saveToFile() {
    std::ofstream file(filename);
    for (FineNode* curr = head->next; curr; curr = curr->next) {
        file << std::setw(5) << std::left << curr->id
            << std::quoted(curr->type) << " "
            << curr->amount << " "
            << std::quoted(severityToString(curr->severity)) << "\n";
    }
}

// ���������� ������ ������
void FineTable::addFine(const std::string& type, double amount, Severity severity) {
    const int& newId = generateNextId();
    FineNode* newNode = new FineNode(newId, type, amount, severity, head->next);
    head->next = newNode;
    idToFineMap.insert(newId, newNode);
    typeToIdMap[type] = newId;
    saveToFile();
}

// �������� ������ �� ����
void FineTable::deleteFine(const std::string& type) {
    auto it = typeToIdMap.find(type);
    if (it == typeToIdMap.end()) {
        std::cerr << "����� �� ������!\n";
        return;
    }

    const int targetId = it->second;
    FineNode* prev = head;
    FineNode* current = head->next;
    while (current) {
        if (current->id == targetId) {
            prev->next = current->next;
            idToFineMap.remove(targetId);
            typeToIdMap.erase(current->type);
            delete current;
            saveToFile();
            std::cout << "����� ������!\n";
            return;
        }
        prev = current;
        current = current->next;
    }
}

// �������������� Severity � ������
std::string FineTable::severityToString(Severity severity) {
    switch (severity) {
    case Severity::LIGHT: return "������";
    case Severity::MEDIUM: return "�������";
    case Severity::HEAVY: return "�������";
    default: return "����������";
    }
}

// ��������� ID ������ �� ����
const int& FineTable::getFineIdByType(const std::string& type) const {
    static const int invalidId = -1;
    auto it = typeToIdMap.find(type);
    return (it != typeToIdMap.end()) ? it->second : invalidId;
}

// ��������� ���������� � ������ �� ID
FineTable::FineInfo FineTable::getFineInfoById(int fineId) const {
    FineInfo info;
    void* data;
    if (idToFineMap.get(fineId, data)) {
        FineNode* fine = static_cast<FineNode*>(data);
        info.type = fine->type;
        info.amount = fine->amount;
        info.severity = fine->severity;
    }
    return info;
}

// ��������: ����� ��������� �� ������ ������
void FineTable::fineIteratorReset() const {
    currentIterator = head->next;
}

// �������� ������� ���������� ��������
bool FineTable::fineIteratorHasNext() const {
    return currentIterator != nullptr;
}

// ��������� ���������� ������
FineTable::FineInfo FineTable::fineIteratorNext() const {
    FineInfo info;
    if (!currentIterator) return info;

    info.type = currentIterator->type;
    info.amount = currentIterator->amount;
    info.severity = currentIterator->severity;

    currentIterator = currentIterator->next;
    return info;
}