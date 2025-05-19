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
#include <vector>

class UserInterface {
    DatabaseManager db;

    void showMainMenu();
    void showCityMenu();
    void showDriverMenu();
    void showFineMenu();
    void showViolationMenu();
    void showStatisticsMenu();

    static bool validateDate(const std::string& date);
    static bool validateName(const std::string& name);

    void printTableHeader(const std::vector<std::string>& headers);
    void printTableRow(const std::vector<std::string>& cells, size_t columnWidth = 20);

public:
    UserInterface() = default;
    void run();
};