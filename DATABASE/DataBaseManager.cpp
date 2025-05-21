//#include "DataBaseManager.h"
//
//void DatabaseManager::loadAll() {
//    cities.load();
//    drivers.load();
//    fines.load();
//    registry.load();
//}
//
//void DatabaseManager::saveAll() {
//    cities.save();
//    drivers.save();
//    fines.save();
//    registry.save();
//}
//
//void DatabaseManager::addCity(const std::string& name) {
//    cities.addCity(name);
//}
//
//void DatabaseManager::deleteCity(int cityId) {
//    cities.deleteRecord(cityId);
//    drivers.updateCityReferences(cityId);
//    registry.updateCityReferences(cityId);
//    saveAll();
//}
//
//void DatabaseManager::addDriver(const std::string& fullName, const std::string& birthDate, int cityId) {
//    if (isValidCity(cityId)) {
//        drivers.addDriver(fullName, birthDate, cityId);
//    }
//    else {
//        throw std::invalid_argument("Неверный ID города");
//    }
//}
//
//void DatabaseManager::deleteDriver(int driverId) {
//    drivers.deleteRecord(driverId);
//    registry.updateDriverReferences(driverId);
//    saveAll();
//}
//
//void DatabaseManager::addFine(double amount, const std::string& type) {
//    fines.addFine(amount, type);
//}
//
//void DatabaseManager::addViolation(int driverId, int fineId, const std::string& violationDate) {
//    if (!isValidDriver(driverId) || !isValidFine(fineId)) {
//        throw std::invalid_argument("Неверные данные");
//    }
//
//
//    DriverTable::Driver* driver = drivers.getAllDrivers();
//    int cityId = 0;
//    while (driver) {
//        if (driver->id == driverId) {
//            cityId = driver->cityId;
//            break;
//        }
//        driver = driver->next;
//    }
//
//    registry.addRecord(driverId, cityId, fineId, violationDate, false);
//}
//
//void DatabaseManager::markFineAsPaid(int recordId) {
//    registry.markAsPaid(recordId);
//}
//
//bool DatabaseManager::isValidDriver(int driverId) {
//    return !drivers.getDriverInfo(driverId).empty();
//}
//
//bool DatabaseManager::isValidCity(int cityId) {
//    return cities.getCityName(cityId) != "Неизвестный_город";
//}
//
//bool DatabaseManager::isValidFine(int fineId) {
//    return fines.getFineById(fineId) != nullptr;
//}


//#include "DatabaseManager.h"
//
//void DatabaseManager::loadAll() {
//    cities.loadFromFile();
//    drivers.loadFromFile();
//    fines.loadFromFile();
//    registry.loadFromFile();
//}
//
//void DatabaseManager::saveAll() {
//    cities.saveToFile();
//    drivers.saveToFile();
//    fines.saveToFile();
//    registry.saveToFile();
//}
//
//void DatabaseManager::addCity(coщасnst std::string& name) {
//    cities.addCity(name);
//}
//
//void DatabaseManager::deleteCity(const std::string& name) {
//    const int& cityId = cities.getCityIdByName(name);
//    if (cityId == -1) return;
//
//    cities.deleteCity(name);
//    drivers.updateCityReferences(cityId);
//    registry.updateCityReferences(cityId);
//    saveAll();
//}
//
//void DatabaseManager::addDriver(const std::string& fullName,
//    const std::string& birthDate,
//    const std::string& cityName) {
//    const int& cityId = cities.getCityIdByName(cityName);
//    if (cityId == -1)
//        throw std::invalid_argument("Неверный город");
//
//    drivers.addDriver(fullName, birthDate, cityId);
//}
//
//void DatabaseManager::deleteDriver(const std::string& name) {
//    const int& driverId = drivers.getDriverId(name);
//    if (driverId == -1) return;
//
//    drivers.deleteDriver(name);
//    registry.updateDriverReferences(driverId);
//    saveAll();
//}
//
//void DatabaseManager::addFine(const std::string& type, double amount) {
//    fines.addFine(type, amount);
//}
//
//void DatabaseManager::addViolation(const std::string& driverName,
//    const std::string& fineType,
//    const std::string& date) {
//    const int& driverId = drivers.getDriverId(driverName);
//    const int& cityId = drivers.getCityIdForDriver(driverName);
//    const int& fineId = fines.getFineIdByType(fineType);
//
//    if (driverId == -1 || cityId == -1 || fineId == -1)
//        throw std::invalid_argument("Неверные данные");
//
//    registry.addViolation(driverId, cityId, fineId, date);
//}
//
//void DatabaseManager::markFineAsPaid(int recordId) {
//    registry.markAsPaid(recordId);
//}
//
//bool DatabaseManager::isValidDriver(const std::string& name) const {
//    return drivers.getDriverId(name) != -1;
//}
//
//bool DatabaseManager::isValidCity(const std::string& name) const {
//    return cities.getCityIdByName(name) != -1;
//}
//
//bool DatabaseManager::isValidFine(const std::string& type) const {
//    return fines.getFineIdByType(type) != -1;
//}
//
//void DriverTable::updateCityReferences(const int& cityId) {
//    for (DriverNode* curr = head->next; curr; curr = curr->next) {
//        if (curr->cityId == cityId) {
//            curr->cityId = -1; // Устанавливаем недействительный ID города
//        }
//    }
//    saveToFile(); // Сохраняем изменения в файл
//}

// DataBaseManager.cpp

#include "DataBaseManager.h"
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

void DatabaseManager::addCity(const std::string& name,
    int population,
    CityTable::PopulationGrade grade,
    CityTable::SettlementType type)
{
    cities.addCity(name, population, grade, type);
}

void DatabaseManager::deleteCity(const std::string& name) {
    int cityId = cities.getCityIdByName(name);
    if (cityId == -1) return;

    cities.deleteCity(name);
    drivers.updateCityReferences(cityId);
    registry.updateCityReferences(cityId);
    saveAll();
}

void DatabaseManager::addDriver(const std::string& fullName,
    const std::string& birthDate,
    const std::string& cityName)
{
    int cityId = cities.getCityIdByName(cityName);
    if (cityId == -1) {
        // Если город не найден, выбрасываем исключение — UI возьмет на себя ввод данных о городе
        throw std::invalid_argument("Город отсутствует");
    }

    drivers.addDriver(fullName, birthDate, cityId);
    saveAll();
}

void DatabaseManager::deleteDriver(const std::string& name) {
    int driverId = drivers.getDriverId(name);
    if (driverId == -1) return;

    drivers.deleteDriver(name);
    registry.updateDriverReferences(driverId);
    saveAll();
}

void DatabaseManager::addFine(const std::string& type,
    double amount,
    FineTable::Severity severity)
{
    fines.addFine(type, amount, severity);
}

void DatabaseManager::addViolation(const std::string& driverName,
    const std::string& fineType,
    const std::string& date)
{
    int driverId = drivers.getDriverId(driverName);
    int cityId = drivers.getCityIdForDriver(driverName);
    int fineId = fines.getFineIdByType(fineType);

    if (driverId == -1 || cityId == -1 || fineId == -1)
        throw std::invalid_argument("Неверные данные для нарушения");

    registry.addViolation(driverId, cityId, fineId, date);
}

void DatabaseManager::markFineAsPaid(int recordId) {
    registry.markAsPaid(recordId);
}

std::vector<FineRegistry::ViolationInfo> DatabaseManager::getAllViolations() {
    std::vector<FineRegistry::ViolationInfo> violations;
    registry.violationIteratorReset();
    while (registry.violationIteratorHasNext()) {
        violations.push_back(
            registry.violationIteratorNext(drivers, cities, fines)
        );
    }
    return violations;
}
