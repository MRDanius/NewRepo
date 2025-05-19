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


#pragma once
#include "CityTable.h"
#include "DriverTable.h"
#include "FineTable.h"
#include "FineRegistry.h"
#include <stdexcept>

class DatabaseManager {
    CityTable cities;
    DriverTable drivers;
    FineTable fines;
    FineRegistry registry;

public:
    void loadAll();
    void saveAll();

    void addCity(const std::string& name, int population = 0,
        CityTable::PopulationGrade grade = CityTable::PopulationGrade::SMALL,
        CityTable::SettlementType type = CityTable::SettlementType::CITY);

    void deleteCity(const std::string& name);

    void addDriver(const std::string& fullName,
        const std::string& birthDate,
        const std::string& cityName);

    void deleteDriver(const std::string& name);

    void addFine(const std::string& type, double amount,
        FineTable::Severity severity = FineTable::Severity::LIGHT);

    void addViolation(const std::string& driverName,
        const std::string& fineType,
        const std::string& date);

    void markFineAsPaid(int recordId);

    CityTable& getCities() { return cities; }
    DriverTable& getDrivers() { return drivers; }
    FineTable& getFines() { return fines; }
    FineRegistry& getRegistry() { return registry; }
};