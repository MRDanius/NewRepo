#include "DataBaseManager.h"

void DatabaseManager::loadAll() {
    cities.load();
    drivers.load();
    fines.load();
    registry.load();
}

void DatabaseManager::saveAll() {
    cities.save();
    drivers.save();
    fines.save();
    registry.save();
}

void DatabaseManager::addCity(const std::string& name) {
    cities.addCity(name);
}

void DatabaseManager::deleteCity(int cityId) {
    cities.deleteRecord(cityId);
    drivers.updateCityReferences(cityId);
    registry.updateCityReferences(cityId);
    saveAll();
}

void DatabaseManager::addDriver(const std::string& fullName, const std::string& birthDate, int cityId) {
    if (isValidCity(cityId)) {
        drivers.addDriver(fullName, birthDate, cityId);
    }
    else {
        throw std::invalid_argument("Неверный ID города");
    }
}

void DatabaseManager::deleteDriver(int driverId) {
    drivers.deleteRecord(driverId);
    registry.updateDriverReferences(driverId);
    saveAll();
}

void DatabaseManager::addFine(double amount, const std::string& type) {
    fines.addFine(amount, type);
}

void DatabaseManager::addViolation(int driverId, int fineId) {
    if (!isValidDriver(driverId) || !isValidFine(fineId)) {
        throw std::invalid_argument("Неверные данные");
    }


    DriverTable::Driver* driver = drivers.getAllDrivers();
    int cityId = 0;
    while (driver) {
        if (driver->id == driverId) {
            cityId = driver->cityId;
            break;
        }
        driver = driver->next;
    }

    registry.addRecord(driverId, cityId, fineId, false);
}

void DatabaseManager::markFineAsPaid(int recordId) {
    registry.markAsPaid(recordId);
}

bool DatabaseManager::isValidDriver(int driverId) {
    return !drivers.getDriverInfo(driverId).empty();
}

bool DatabaseManager::isValidCity(int cityId) {
    return cities.getCityName(cityId) != "Неизвестный_город";
}

bool DatabaseManager::isValidFine(int fineId) {
    return fines.getFineById(fineId) != nullptr;
}
