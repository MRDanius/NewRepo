//#pragma once
//#include "DatabaseManager.h"
//
//class UserInterface {
//    DatabaseManager db;
//
//    void showMainMenu();
//    void showCityMenu();
//    void showDriverMenu();
//    void showFineMenu();
//    void showViolationMenu();
//    void showStatisticsMenu();
//
//public:
//    void run();
//};

//#pragma once
//#include "DataBaseManager.h"
//
//class UserInterface {
//    DatabaseManager db;
//
//    // Основные меню
//    void showMainMenu();
//    void showCityMenu();
//    void showDriverMenu();
//    void showFineMenu();
//    void showViolationMenu();
//    void showStatisticsMenu();
//
//    // Вспомогательные методы валидации
//    static bool validateDate(const std::string& date);
//    static bool validateName(const std::string& name);
//
//public:
//    UserInterface() = default;
//
//    // Точка входа в приложение
//    void run();
//};

#pragma once
#include "DatabaseManager.h"
#include "TableFormatter.h"
#include <vector>
#include <string>

class UserInterface {
    DatabaseManager db;

    // Структура для хранения условий фильтрации
    struct FilterCondition {
        std::string field;
        std::string value;
        bool is_range = false;
        std::string range_from;
        std::string range_to;
    };

    std::vector<FilterCondition> active_filters;

    bool validateDate(const std::string& date);
    bool validateName(const std::string& name) const;
    tm parseDate(const std::string& dateStr);
    // Методы фильтрации
    void filterMenu();
    void addFilterCondition();
    void applyFilters();
    void resetFilters();
    bool matchesFilters(const FineRegistry::ViolationInfo& violation);

    // Вспомогательные методы
    std::vector<std::vector<std::string>> prepareViolationData();
    void printDynamicTable(const std::vector<std::string>& headers,
        const std::vector<std::vector<std::string>>& data);

public:
    void run();
    void showMainMenu();
    void showCityMenu();
    void showDriverMenu();
    void showFineMenu();
    void showViolationMenu();
    void showStatisticsMenu();
};