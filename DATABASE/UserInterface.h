//#pragma once
//#include "DataBaseManager.h"
//#include <string>
//
//class UserInterface {
//public:
//    void run();
//
//private:
//    struct Date {
//        int day, month, year;
//    };
//
//    static bool parseDate(const std::string& dateStr, Date& date);
//    static bool isDateValid(const Date& date);
//    static int calculateAge(const Date& birthDate, const Date& violationDate);
//    static bool isDriverAdult(const std::string& birthDateStr,
//        const std::string& violationDateStr);
//
//    static const int MAX_CITIES = 100;
//    static const int MAX_VIOLATIONS_PER_CITY = 1000;
//
//    struct CityViolations {
//        std::string name;
//        int violationIds[MAX_VIOLATIONS_PER_CITY] = { 0 };
//        int count = 0;
//    };
//
//    void editDriverCity();
//
//    void collectCityStats(CityViolations* stats, int& cityCount);
//    void printCityViolations(CityViolations* stats, int cityCount);
//    static int compareCityStats(const void* a, const void* b);
//
//    DatabaseManager dbManager;
//
//    void mainMenu();
//    void citiesMenu();
//    void driversMenu();
//    void finesMenu();
//    void registryMenu();
//    void statisticsMenu();
//
//    // Ìåòîäû äëÿ êàæäîé îïöèè ìåíþ
//    void listCities();
//    void addCity();
//    void deleteCity();
//    void filterCities();
//    void clearCityFilters();
//
//    void listDrivers();
//    void addDriver();
//    void deleteDriver();
//
//    void listFines();
//    void addFine();
//    void deleteFine();
//
//    void listViolations();
//    void addViolation();
//    void markViolationPaid();
//
//    void showViolationsByCity();
//    void showTopDrivers();
//
//    // Óòèëèòû ââîäà/âûâîäà
//    int readInt(const std::string& prompt);
//    double readDouble(const std::string& prompt);
//    std::string readString(const std::string& prompt);
//};

//// UserInterface.h
//#pragma once
//#include "DataBaseManager.h"
//#include <string>
//
//class UserInterface {
//public:
//    void run();
//
//private:
//    struct Date {
//        int day, month, year;
//    };
//
//    static bool parseDate(const std::string& dateStr, Date& date);
//    static bool isDateValid(const Date& date);
//    static int calculateAge(const Date& birthDate, const Date& violationDate);
//    static bool isDriverAdult(const std::string& birthDateStr,
//        const std::string& violationDateStr);
//
//    static const int MAX_CITIES = 100;
//    static const int MAX_VIOLATIONS_PER_CITY = 1000;
//
//    struct CityViolations {
//        std::string name;
//        int violationIds[MAX_VIOLATIONS_PER_CITY] = { 0 };
//        int count = 0;
//    };
//
//    void collectCityStats(CityViolations* stats, int& cityCount);
//    void printCityViolations(CityViolations* stats, int cityCount);
//    static int compareCityStats(const void* a, const void* b);
//
//    DatabaseManager dbManager;
//
//    void mainMenu();
//    void citiesMenu();
//    void driversMenu();
//    void finesMenu();
//    void registryMenu();
//    void statisticsMenu();
//
//    void listCities();
//    void addCity();
//    void deleteCity();
//    void filterCities();
//    void clearCityFilters();
//    void editCity();
//
//    void listDrivers();
//    void addDriver();
//    void deleteDriver();
//    void editDriver();
//
//    void listFines();
//    void addFine();
//    void deleteFine();
//    void editFine();
//
//    void listViolations();
//    void addViolation();
//    void markViolationPaid();
//    void editViolation();
//
//    void showViolationsByCity();
//    void showTopDrivers();
//
//    int readInt(const std::string& prompt);
//    double readDouble(const std::string& prompt);
//    std::string readString(const std::string& prompt);
//};


#pragma once
#include "DataBaseManager.h"
#include <string>

class UserInterface {
public:
    void run();

private:
    struct Date {
        int day, month, year;
    };

    static bool parseDate(const std::string& dateStr, Date& date);
    static bool isDateValid(const Date& date);
    static int calculateAge(const Date& birthDate, const Date& violationDate);

    static const int MAX_CITIES = 100;
    static const int MAX_VIOLATIONS_PER_CITY = 1000;

    struct CityViolations {
        std::string name;
        int violationIds[MAX_VIOLATIONS_PER_CITY];
        int count;
    };

    DatabaseManager dbManager;

    // Меню
    void mainMenu();
    void citiesMenu();
    void driversMenu();
    void finesMenu();
    void registryMenu();
    void statisticsMenu();

    // Города
    void listCities();
    void addCity();
    void deleteCity();
    void filterCities();
    void removeCityFilters();
    void clearAllCityFilters();
    void editCity();

    // Водители
    void listDrivers();
    void addDriver();
    void deleteDriver();
    void filterDrivers();
    void removeDriverFilters();
    void clearAllDriverFilters();
    void editDriver();

    // Штрафы
    void listFines();
    void addFine();
    void deleteFine();
    void filterFines();
    void removeFineFilters();
    void clearAllFineFilters();
    void editFine();

    // Нарушения
    void listViolations();
    void addViolation();
    void markViolationPaid();
    void filterViolations();
    void removeViolationFilters();
    void clearAllViolationFilters();
    void editViolation();

    // Статистика
    void showViolationsByCity();
    void showTopDrivers();

    // Методы для сбора и печати статистики по городам
    void collectCityStats(CityViolations* stats, int& cityCount);
    void printCityViolations(CityViolations* stats, int cityCount);
    static int compareCityStats(const void* a, const void* b);

    // Утилиты ввода/вывода
    int readInt(const std::string& prompt);
    double readDouble(const std::string& prompt);
    std::string readString(const std::string& prompt);
};
