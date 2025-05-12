#pragma once
#include "CityTable.h"
#include "DriverTable.h"
#include "FineTable.h"
#include "FineRegistry.h"
#include <stdexcept>
#include <map>

class DatabaseManager {
    CityTable cities;
    DriverTable drivers;
    FineTable fines;
    FineRegistry registry;

public:
    void loadAll();
    void saveAll();

    // Управление городами
    void addCity(const std::string& name);
    void deleteCity(int cityId);

    // Управление водителями
    void addDriver(const std::string& fullName, const std::string& birthDate, int cityId);
    void deleteDriver(int driverId);

    // Управление штрафами
    void addFine(double amount, const std::string& type);
    void addViolation(int driverId, int fineId);
    void markFineAsPaid(int recordId);

    // Валидация
    bool isValidDriver(int driverId);
    bool isValidCity(int cityId);
    bool isValidFine(int fineId);

    // Геттеры
    CityTable& getCities() { return cities; }
    DriverTable& getDrivers() { return drivers; }
    FineTable& getFines() { return fines; }
    FineRegistry& getRegistry() { return registry; }
};

