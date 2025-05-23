//#include "DriverTable.h"
//#include <fstream>
//#include <sstream>
//#include <stdexcept>
//#include <iomanip>
//using namespace std;
//
//// Конструктор: инициализация заголовочного узла и загрузка данных
//DriverTable::DriverTable()
//    : head(new DriverNode(-1, "", "", -1, nullptr)),
//    currentIterator(nullptr),
//    idWidth(5),
//    nameWidth(30),
//    birthDateWidth(12),
//    cityIdWidth(5)
//{
//    loadFromFile();
//}
//
//// Деструктор: очистка списка и хеш-таблицы
//DriverTable::~DriverTable() {
//    DriverNode* current = head->next;
//    while (current) {
//        DriverNode* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    delete head;
//    idToDriverMap.clear();
//    nameToIdMap.clear();
//}
//
//// Загрузка данных из файла
//void DriverTable::loadFromFile() {
//    ifstream file("drivers.txt");
//    if (!file.is_open()) {
//        cerr << "Error opening drivers file!" << endl;
//        return;
//    }
//    // Очищаем существующие данные
//    DriverNode* current = head->next;
//    while (current) {
//        DriverNode* temp = current;
//        current = current->next;
//        delete temp;
//    }
//    head->next = nullptr;
//    idToDriverMap.clear();
//    nameToIdMap.clear();
//
//    string line;
//    while (getline(file, line)) {
//        parseLine(line);
//    }
//    file.close();
//}
//
//// Парсинг строки: "id \"fullName\" \"birthDate\" cityId"
//void DriverTable::parseLine(const std::string& line) {
//    if (line.empty()) return;
//    istringstream iss(line);
//    int id, cityId;
//    string fullName, birthDate;
//    iss >> id >> quoted(fullName) >> quoted(birthDate) >> cityId;
//
//    addDriverNode(id, fullName, birthDate, cityId);
//}
//
//// Добавление узла в список и в хеш-таблицу
//void DriverTable::addDriverNode(int id, const std::string& fullName,
//    const std::string& birthDate, int cityId)
//{
//    DriverNode* newNode = new DriverNode(id, fullName, birthDate, cityId, head->next);
//    head->next = newNode;
//    idToDriverMap.insert(id, newNode);
//    nameToIdMap[fullName] = id;
//}
//
//// Валидация ФИО (только буквы и пробелы)
//bool DriverTable::validateName(const std::string& name) const {
//    static const regex pattern("^[А-Яа-яA-Za-z\\s]+$");
//    return regex_match(name, pattern);
//}
//
//// Валидация даты (формат ДД.MM.ГГГГ)
//bool DriverTable::validateDate(const std::string& date) const {
//    static const regex pattern("^\\d{2}\\.\\d{2}\\.\\d{4}$");
//    return regex_match(date, pattern);
//}
//
//// Добавление водителя (с валидацией)
//void DriverTable::addDriver(const std::string& fullName,
//    const std::string& birthDate, int cityId)
//{
//    if (!validateName(fullName))
//        throw invalid_argument("Недопустимые символы в ФИО");
//    if (!validateDate(birthDate))
//        throw invalid_argument("Неправильный формат даты");
//
//    // Генерация ID: максимум существующего +1
//    int newId = 1;
//    for (auto pair : nameToIdMap) {
//        if (pair.second >= newId) newId = pair.second + 1;
//    }
//
//    addDriverNode(newId, fullName, birthDate, cityId);
//}
//
//// Новый метод: удаление водителя по ID
//void DriverTable::deleteDriverById(int id) {
//    DriverNode* prev = head;
//    DriverNode* curr = head->next;
//    while (curr) {
//        if (curr->id == id) {
//            prev->next = curr->next;
//            idToDriverMap.remove(id);
//            nameToIdMap.erase(curr->fullName);
//            delete curr;
//            return;
//        }
//        prev = curr;
//        curr = curr->next;
//    }
//}
//
//// Итератор: сброс на начало
//void DriverTable::driverIteratorReset() const {
//    currentIterator = head->next;
//}
//
//// Есть ли следующий?
//bool DriverTable::driverIteratorHasNext() const {
//    return currentIterator != nullptr;
//}
//
//// Получение следующего
//DriverTable::DriverInfo DriverTable::driverIteratorNext() const {
//    DriverInfo info;
//    if (!currentIterator) return info;
//    info.id = currentIterator->id;
//    info.fullName = currentIterator->fullName;
//    info.birthDate = currentIterator->birthDate;
//    info.cityId = currentIterator->cityId;
//    currentIterator = currentIterator->next;
//    return info;
//}
//
//// Геттер: получить ID по ФИО
//int DriverTable::getDriverId(const std::string& fullName) const {
//    auto it = nameToIdMap.find(fullName);
//    return (it != nameToIdMap.end()) ? it->second : -1;
//}
//
//// Геттер: получить ID города для водителя
//int DriverTable::getCityIdForDriver(const std::string& fullName) const {
//    int id = getDriverId(fullName);
//    if (id == -1) return -1;
//    DriverNode* node = idToDriverMap.find<DriverNode>(id);
//    return node ? node->cityId : -1;
//}
//
//std::string DriverTable::getDriverNameById(int id) const {
//    DriverNode* node = idToDriverMap.find<DriverNode>(id);
//    return node ? node->fullName : "";
//}
//
//// Удаление водителя по ФИО
//void DriverTable::deleteDriver(const std::string& fullName) {
//    auto it = nameToIdMap.find(fullName);
//    if (it == nameToIdMap.end()) return;
//
//    int id = it->second;
//    deleteDriverById(id);
//}
//
//// Обновление ссылок при удалении города (устанавливаем cityId = -1)
//void DriverTable::updateCityReferences(int deletedCityId) {
//    DriverNode* curr = head->next;
//    while (curr) {
//        if (curr->cityId == deletedCityId) {
//            curr->cityId = -1;
//        }
//        curr = curr->next;
//    }
//}
//
//bool DriverTable::updateDriverCity(const std::string& fullName, int newCityId) {
//    bool updated = false;
//    DriverNode* current = head->next;
//    while (current) {
//        if (current->fullName == fullName) {
//            current->cityId = newCityId;
//            updated = true;
//        }
//        current = current->next;
//    }
//    return updated;
//}
//
//// Сохранение данных в файл
//void DriverTable::saveToFile() const {
//    ofstream file("drivers.txt");
//    if (!file.is_open()) {
//        cerr << "Error opening drivers file for writing!" << endl;
//        return;
//    }
//    DriverNode* curr = head->next;
//    while (curr) {
//        file << curr->id << ' '
//            << quoted(curr->fullName) << ' '
//            << quoted(curr->birthDate) << ' '
//            << curr->cityId << '\n';
//        curr = curr->next;
//    }
//    file.close();
//}

// DriverTable.cpp
#include "DriverTable.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <ctime>
using namespace std;

static bool parseDateParts(const string& dateStr, int& day, int& month, int& year) {
    if (dateStr.size() != 10) return false;
    if (dateStr[2] != '.' || dateStr[5] != '.') return false;
    try {
        day = stoi(dateStr.substr(0, 2));
        month = stoi(dateStr.substr(3, 2));
        year = stoi(dateStr.substr(6, 4));
    }
    catch (...) {
        return false;
    }
    return true;
}

static int calculateAgeFromBirth(const string& birthDateStr) {
    int day, month, year;
    if (!parseDateParts(birthDateStr, day, month, year)) return -1;
    time_t t = time(nullptr);
    tm nowStruct;
    localtime_s(&nowStruct, &t);
    int cy = nowStruct.tm_year + 1900;
    int cm = nowStruct.tm_mon + 1;
    int cd = nowStruct.tm_mday;
    int age = cy - year;
    if (cm < month || (cm == month && cd < day)) age--;
    return age;
}

DriverTable::DriverTable()
    : head(new DriverNode(-1, "", "", -1, nullptr)),
    currentIterator(nullptr),
    idWidth(5),
    nameWidth(30),
    birthDateWidth(12),
    cityIdWidth(5)
{
    loadFromFile();
}

DriverTable::~DriverTable() {
    DriverNode* current = head->next;
    while (current) {
        DriverNode* temp = current;
        current = current->next;
        delete temp;
    }
    delete head;
    idToDriverMap.clear();
    nameToIdMap.clear();
}

void DriverTable::loadFromFile() {
    ifstream file("drivers.txt");
    if (!file.is_open()) {
        cerr << "Error opening drivers file!" << endl;
        return;
    }
    DriverNode* current = head->next;
    while (current) {
        DriverNode* temp = current;
        current = current->next;
        delete temp;
    }
    head->next = nullptr;
    idToDriverMap.clear();
    nameToIdMap.clear();

    string line;
    while (getline(file, line)) {
        parseLine(line);
    }
    file.close();
}

void DriverTable::parseLine(const std::string& line) {
    if (line.empty()) return;
    istringstream iss(line);
    int id, cityId;
    string fullName, birthDate;
    iss >> id >> quoted(fullName) >> quoted(birthDate) >> cityId;
    addDriverNode(id, fullName, birthDate, cityId);
}

void DriverTable::addDriverNode(int id, const std::string& fullName,
    const std::string& birthDate, int cityId)
{
    DriverNode* newNode = new DriverNode(id, fullName, birthDate, cityId, head->next);
    head->next = newNode;
    idToDriverMap.insert(id, newNode);
    nameToIdMap[fullName] = id;
}

bool DriverTable::validateName(const std::string& name) const {
    static const regex pattern("^[A-Za-z\\s]+$");
    return regex_match(name, pattern);
}

bool DriverTable::validateDate(const std::string& date) const {
    static const regex pattern("^\\d{2}\\.\\d{2}\\.\\d{4}$");
    return regex_match(date, pattern);
}

bool DriverTable::validateAge(const std::string& birthDate) const {
    int age = calculateAgeFromBirth(birthDate);
    return age >= 18 && age <= 100;
}

void DriverTable::addDriver(const std::string& fullName,
    const std::string& birthDate, int cityId)
{
    if (!validateName(fullName))
        throw invalid_argument("Invalid characters in name");
    if (!validateDate(birthDate))
        throw invalid_argument("Incorrect date format");
    if (!validateAge(birthDate))
        throw invalid_argument("Driver must be between 18 and 100 years old");

    int newId = 1;
    for (auto pair : nameToIdMap) {
        if (pair.second >= newId) newId = pair.second + 1;
    }
    addDriverNode(newId, fullName, birthDate, cityId);
}

void DriverTable::deleteDriver(const std::string& fullName) {
    auto it = nameToIdMap.find(fullName);
    if (it == nameToIdMap.end()) return;
    int id = it->second;
    deleteDriverById(id);
}

void DriverTable::deleteDriverById(int id) {
    DriverNode* prev = head;
    DriverNode* curr = head->next;
    while (curr) {
        if (curr->id == id) {
            prev->next = curr->next;
            idToDriverMap.remove(id);
            nameToIdMap.erase(curr->fullName);
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void DriverTable::driverIteratorReset() const {
    currentIterator = head->next;
}

bool DriverTable::driverIteratorHasNext() const {
    return currentIterator != nullptr;
}

DriverTable::DriverInfo DriverTable::driverIteratorNext() const {
    DriverInfo info{};
    if (!currentIterator) return info;
    info.id = currentIterator->id;
    info.fullName = currentIterator->fullName;
    info.birthDate = currentIterator->birthDate;
    info.cityId = currentIterator->cityId;
    currentIterator = currentIterator->next;
    return info;
}

int DriverTable::getDriverId(const std::string& fullName) const {
    auto it = nameToIdMap.find(fullName);
    return (it != nameToIdMap.end()) ? it->second : -1;
}

int DriverTable::getCityIdForDriver(const std::string& fullName) const {
    int id = getDriverId(fullName);
    if (id == -1) return -1;
    DriverNode* node = idToDriverMap.find<DriverNode>(id);
    return node ? node->cityId : -1;
}

string DriverTable::getDriverNameById(int id) const {
    DriverNode* node = idToDriverMap.find<DriverNode>(id);
    return node ? node->fullName : "";
}

void DriverTable::updateCityReferences(int deletedCityId) {
    DriverNode* curr = head->next;
    while (curr) {
        if (curr->cityId == deletedCityId) {
            curr->cityId = -1;
        }
        curr = curr->next;
    }
}

bool DriverTable::updateDriverCity(const std::string& fullName, int newCityId) {
    bool updated = false;
    DriverNode* curr = head->next;
    while (curr) {
        if (curr->fullName == fullName) {
            curr->cityId = newCityId;
            updated = true;
        }
        curr = curr->next;
    }
    return updated;
}

// Редактирование
bool DriverTable::updateDriverName(int id, const std::string& newName) {
    if (!validateName(newName)) return false;
    DriverNode* node = idToDriverMap.find<DriverNode>(id);
    if (!node) return false;
    nameToIdMap.erase(node->fullName);
    node->fullName = newName;
    nameToIdMap[newName] = id;
    return true;
}

bool DriverTable::updateDriverBirthDate(int id, const std::string& newBirthDate) {
    if (!validateDate(newBirthDate) || !validateAge(newBirthDate)) return false;
    DriverNode* node = idToDriverMap.find<DriverNode>(id);
    if (!node) return false;
    node->birthDate = newBirthDate;
    return true;
}

bool DriverTable::updateDriverCity(int id, int newCityId) {
    DriverNode* node = idToDriverMap.find<DriverNode>(id);
    if (!node) return false;
    node->cityId = newCityId;
    return true;
}

void DriverTable::saveToFile() const {
    ofstream file("drivers.txt");
    if (!file.is_open()) {
        cerr << "Error opening drivers file for writing!" << endl;
        return;
    }
    DriverNode* curr = head->next;
    while (curr) {
        file << curr->id << ' '
            << quoted(curr->fullName) << ' '
            << quoted(curr->birthDate) << ' '
            << curr->cityId << '\n';
        curr = curr->next;
    }
    file.close();
}
