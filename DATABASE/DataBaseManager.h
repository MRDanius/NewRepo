//#pragma once
//#include "CityTable.h"
//#include "DriverTable.h"
//#include "FineTable.h"
//#include "FineRegistry.h"
//#include <stdexcept>
//#include <map>
//
//class DatabaseManager {
//    CityTable cities;
//    DriverTable drivers;
//    FineTable fines;
//    FineRegistry registry;
//
//public:
//    void loadAll();
//    void saveAll();
//
//    // Управление городами
//    void addCity(const std::string& name);
//    void deleteCity(int cityId);
//
//    // Управление водителями
//    void addDriver(const std::string& fullName, const std::string& birthDate, int cityId);
//    void deleteDriver(int driverId);
//
//    // Управление штрафами
//    void addFine(double amount, const std::string& type);
//    void addViolation(int driverId, int fineId, const std::string& date);
//    void markFineAsPaid(int recordId);
//
//    // Валидация
//    bool isValidDriver(int driverId);
//    bool isValidCity(int cityId);
//    bool isValidFine(int fineId);
//
//    // Геттеры
//    CityTable& getCities() { return cities; }
//    DriverTable& getDrivers() { return drivers; }
//    FineTable& getFines() { return fines; }
//    FineRegistry& getRegistry() { return registry; }
//};


//#pragma once
//#include "CityTable.h"
//#include "DriverTable.h"
//#include "FineTable.h"
//#include "FineRegistry.h"
//#include <stdexcept>
//
//class DatabaseManager {
//    CityTable cities;
//    DriverTable drivers;
//    FineTable fines;
//    FineRegistry registry;
//
//public:
//    void loadAll();
//    void saveAll();
//
//    void addCity(const std::string& name);
//    void deleteCity(const std::string& name);
//
//    void addDriver(const std::string& fullName,
//        const std::string& birthDate,
//        const std::string& cityName);
//    void deleteDriver(const std::string& name);
//
//    void addFine(const std::string& type, double amount);
//    void addViolation(const std::string& driverName,
//        const std::string& fineType,
//        const std::string& date);
//    void markFineAsPaid(int recordId);
//
//    bool isValidDriver(const std::string& name) const;
//    bool isValidCity(const std::string& name) const;
//    bool isValidFine(const std::string& type) const;
//
//    CityTable& getCities() { return cities; }
//    DriverTable& getDrivers() { return drivers; }
//    FineTable& getFines() { return fines; }
//    FineRegistry& getRegistry() { return registry; }
//};


//#pragma once
//#include "CityTable.h"
//#include "DriverTable.h"
//#include "FineTable.h"
//#include "FineRegistry.h"
//#include <stdexcept>
//
//class DatabaseManager {
//    CityTable cities;
//    DriverTable drivers;
//    FineTable fines;
//    FineRegistry registry;
//
//public:
//    void loadAll();
//    void saveAll();
//
//    void addCity(const std::string& name, int population = 0,
//        CityTable::PopulationGrade grade = CityTable::PopulationGrade::SMALL,
//        CityTable::SettlementType type = CityTable::SettlementType::CITY);
//
//    void deleteCity(const std::string& name);
//
//    void addDriver(const std::string& fullName,
//        const std::string& birthDate,
//        const std::string& cityName);
//
//    void deleteDriver(const std::string& name);
//
//    void addFine(const std::string& type, double amount,
//        FineTable::Severity severity = FineTable::Severity::LIGHT);
//
//    void addViolation(const std::string& driverName,
//        const std::string& fineType,
//        const std::string& date);
//
//    void markFineAsPaid(int recordId);
//
//    CityTable& getCities() { return cities; }
//    DriverTable& getDrivers() { return drivers; }
//    FineTable& getFines() { return fines; }
//    FineRegistry& getRegistry() { return registry; }
//};

//#pragma once
//#include "CityTable.h"
//#include "DriverTable.h"
//#include "FineTable.h"
//#include "FineRegistry.h"
//#include <vector>
//
//class DatabaseManager {
//    CityTable cities;
//    DriverTable drivers;
//    FineTable fines;
//    FineRegistry registry;
//
//public:
//    void loadAll();
//    void saveAll();
//
//    // Города
//    void addCity(const std::string& name, int population,
//        CityTable::PopulationGrade grade,
//        CityTable::SettlementType type);
//
//    void deleteCity(const std::string& name);
//
//    // Водители
//    void addDriver(const std::string& name,
//        const std::string& birthDate,
//        const std::string& city);
//
//    void deleteDriver(const std::string& name);
//    void markFineAsPaid(int recordId);
//
//    // Штрафы
//    void addFine(const std::string& type,
//        double amount,
//        FineTable::Severity severity);
//
//    // Нарушения
//    void addViolation(const std::string& driverName,
//        const std::string& fineType,
//        const std::string& date);
//
//
//
//    // Геттеры
//    CityTable& getCities() { return cities; }
//    DriverTable& getDrivers() { return drivers; }
//    FineTable& getFines() { return fines; }
//    FineRegistry& getRegistry() { return registry; }
//
//    std::vector<FineRegistry::ViolationInfo> getAllViolations();
//};


#include "DatabaseManager.h"
#include <stdexcept>

void DatabaseManager::loadAll() {
    cities.loadFromFile();
    drivers.loadFromFile();
    fines.loadFromFile();
    registry.loadFromFile();
}

void DatabaseManager::saveAll() {
    cities.saveToFile();
    drivers.saveToFile();
    fines.saveToFile();
    registry.saveToFile();
}

// Добавление города с автоматической синхронизацией
void DatabaseManager::addCity(const std::string& name, int population,
    CityTable::PopulationGrade grade, CityTable::SettlementType type)
{
    cities.addCity(name, population, grade, type);
    // Автоматическое обновление связанных данных
    drivers.updateCityReferences(cities.getCityIdByName(name));
}

// Удаление города с каскадным обновлением
void DatabaseManager::deleteCity(const std::string& name) {
    const int cityId = cities.getCityIdByName(name);
    if (cityId == -1) throw std::invalid_argument("City not found");

    cities.deleteCity(name);
    drivers.updateCityReferences(cityId);
    registry.updateCityReferences(cityId);
}

// Добавление водителя с проверкой города
void DatabaseManager::addDriver(const std::string& fullName,
    const std::string& birthDate, const std::string& cityName)
{
    const int cityId = cities.getCityIdByName(cityName);
    if (cityId == -1) throw std::invalid_argument("Invalid city");

    drivers.addDriver(fullName, birthDate, cityId);
}

// Полная цепочка добавления нарушения
void DatabaseManager::addViolation(const std::string& driverName,
    const std::string& fineType, const std::string& date)
{
    const int driverId = drivers.getDriverId(driverName);
    const int cityId = drivers.getCityIdForDriver(driverName);
    const int fineId = fines.getFineIdByType(fineType);

    if (driverId == -1 || cityId == -1 || fineId == -1) {
        throw std::invalid_argument("Invalid violation data");
    }

    registry.addViolation(driverId, cityId, fineId, date);
}