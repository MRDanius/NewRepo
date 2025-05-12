#pragma once
#include "DatabaseManager.h"

class UserInterface {
    DatabaseManager db;

    void showMainMenu();
    void showCityMenu();
    void showDriverMenu();
    void showFineMenu();
    void showViolationMenu();
    void showStatisticsMenu();

public:
    void run();
};
