// UserInterface.cpp
//#include "UserInterface.h"
//#include <iostream>
//#include <iomanip>
//#include <clocale>
//#include <limits>
//#include <algorithm>
//#include <regex>
//
//using namespace std;
//
//bool UserInterface::validateDate(const std::string& date) {
//    std::regex pattern(R"(^(0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.\d{4}$)");
//    return std::regex_match(date, pattern);
//}
//
//bool UserInterface::validateName(const std::string& name) {
//    return std::all_of(name.begin(), name.end(), [](char c) {
//        return std::isalpha(c) || c == ' ' || c == '-';
//        });
//}
//
//
//void UserInterface::run() {
//    setlocale(LC_ALL, "Russian");
//    db.loadAll();
//    showMainMenu();
//    db.saveAll();
//}
//
//void UserInterface::showMainMenu() {
//    int choice;
//    do {
//        cout << "\n========== ГЛАВНОЕ МЕНЮ ==========\n"
//            << "1. Управление городами\n"
//            << "2. Управление водителями\n"
//            << "3. Управление штрафами\n"
//            << "4. Управление нарушениями\n"
//            << "5. Статистика\n"
//            << "6. Выход\n"
//            << "Выберите опцию: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: showCityMenu(); break;
//        case 2: showDriverMenu(); break;
//        case 3: showFineMenu(); break;
//        case 4: showViolationMenu(); break;
//        case 5: showStatisticsMenu(); break;
//        case 6: cout << "Сохранение данных...\n"; break;
//        default:
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            cout << "Неверный ввод!\n";
//        }
//    } while (choice != 6);
//}
//
//void UserInterface::showCityMenu() {
//    int choice;
//    do {
//        cout << "\n========== УПРАВЛЕНИЕ ГОРОДАМИ ==========\n"
//            << "1. Список городов\n"
//            << "2. Добавить город\n"
//            << "3. Удалить город\n"
//            << "4. Назад\n"
//            << "Выберите опцию: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            cout << "\nСписок городов:\n";
//            db.getCities().cityIteratorReset();
//            string cityName;
//            while (db.getCities().cityIteratorHasNext()) {
//                cityName = db.getCities().cityIteratorNext();
//                cout << "• " << cityName << endl;
//            }
//            break;
//        }
//        case 2: {
//            string name;
//            cout << "Введите название города: ";
//            cin.ignore();
//            getline(cin, name);
//            db.addCity(name);
//            cout << "Город добавлен!\n";
//            break;
//        }
//        case 3: {
//            string name;
//            cout << "Введите название города: ";
//            cin.ignore();
//            getline(cin, name);
//            db.deleteCity(name);
//            break;
//        }
//        }
//    } while (choice != 4);
//}
//
//void UserInterface::showDriverMenu() {
//    int choice;
//    do {
//        cout << "\n========== УПРАВЛЕНИЕ ВОДИТЕЛЯМИ ==========\n"
//            << "1. Список водителей\n"
//            << "2. Добавить водителя\n"
//            << "3. Удалить водителя\n"
//            << "4. Назад\n"
//            << "Выберите опцию: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            DriverTable::DriverInfo info;
//            db.getDrivers().driverIteratorReset();
//            cout << "\nСписок водителей:\n";
//            while (db.getDrivers().driverIteratorHasNext()) {
//                info = db.getDrivers().driverIteratorNext(db.getCities());
//                cout << "ФИО: " << info.fullName << "\n"
//                    << "Дата рождения: " << info.birthDate << "\n"
//                    << "Город: " << info.cityName << "\n\n";
//            }
//            break;
//        }
//        case 2: {
//            string name, birthDate, cityName;
//            do {
//                cout << "Введите ФИО: ";
//                cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                getline(cin, name);
//            } while (!validateName(name));
//
//            do {
//                cout << "Введите дату рождения (ДД.ММ.ГГГГ): ";
//                getline(cin, birthDate);
//            } while (!validateDate(birthDate));
//
//            cout << "Доступные города:\n";
//            db.getCities().cityIteratorReset();
//            string city;
//            while (db.getCities().cityIteratorHasNext()) {
//                city = db.getCities().cityIteratorNext();
//                cout << "• " << city << endl;
//            }
//            cout << "Введите название города: ";
//            getline(cin, cityName);
//
//            try {
//                db.addDriver(name, birthDate, cityName);
//                cout << "Водитель добавлен!\n";
//            }
//            catch (const exception& e) {
//                cout << "Ошибка: " << e.what() << endl;
//            }
//            break;
//        }
//        case 3: {
//            string name;
//            cout << "Введите ФИО водителя: ";
//            cin.ignore();
//            getline(cin, name);
//            db.deleteDriver(name);
//            break;
//        }
//        }
//    } while (choice != 4);
//}
//
//void UserInterface::showFineMenu() {
//    int choice;
//    do {
//        cout << "\n========== УПРАВЛЕНИЕ ШТРАФАМИ ==========\n"
//            << "1. Список штрафов\n"
//            << "2. Добавить штраф\n"
//            << "3. Удалить штраф\n"
//            << "4. Назад\n"
//            << "Выберите опцию: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            FineTable::FineInfo info;
//            db.getFines().fineIteratorReset();
//            cout << "\nСписок штрафов:\n";
//            while (db.getFines().fineIteratorHasNext()) {
//                info = db.getFines().fineIteratorNext();
//                cout << "Тип: " << left << setw(25) << info.type
//                    << "Сумма: " << info.amount << " руб.\n";
//            }
//            break;
//        }
//        case 2: {
//            string type;
//            double amount;
//            cout << "Введите тип нарушения: ";
//            cin.ignore();
//            getline(cin, type);
//            cout << "Введите сумму штрафа: ";
//            cin >> amount;
//            db.addFine(type, amount);
//            cout << "Штраф добавлен!\n";
//            break;
//        }
//        case 3: {
//            string type;
//            cout << "Введите тип штрафа для удаления: ";
//            cin.ignore();
//            getline(cin, type);
//            db.getFines().deleteFine(type);
//            break;
//        }
//        }
//    } while (choice != 4);
//}
//
//void UserInterface::showViolationMenu() {
//    int choice;
//    do {
//        cout << "\n========== УПРАВЛЕНИЕ НАРУШЕНИЯМИ ==========\n"
//            << "1. Все нарушения\n"
//            << "2. Добавить нарушение\n"
//            << "3. Отметить как оплаченное\n"
//            << "4. Назад\n"
//            << "Выберите опцию: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            FineRegistry::ViolationInfo info;
//            db.getRegistry().violationIteratorReset();
//            cout << "\nСписок нарушений:\n";
//            while (db.getRegistry().violationIteratorHasNext()) {
//                info = db.getRegistry().violationIteratorNext(
//                    db.getDrivers(), db.getCities(), db.getFines()
//                );
//                cout << "ID: " << info.recordId << "\n"
//                    << "Водитель: " << info.driverName << "\n"
//                    << "Город: " << info.cityName << "\n"
//                    << "Тип: " << info.fineType << "\n"
//                    << "Дата: " << info.date << "\n"
//                    << "Статус: " << (info.paid ? "Оплачен" : "Не оплачен")
//                    << "\n\n";
//            }
//            break;
//        }
//        case 2: {
//            string driverName, fineType, date;
//
//            cout << "\nСписок водителей:\n";
//            DriverTable::DriverInfo driverInfo;
//            db.getDrivers().driverIteratorReset();
//            while (db.getDrivers().driverIteratorHasNext()) {
//                driverInfo = db.getDrivers().driverIteratorNext(db.getCities());
//                cout << "• " << driverInfo.fullName << endl;
//            }
//            cout << "Введите ФИО водителя: ";
//            cin.ignore();
//            getline(cin, driverName);
//
//            cout << "\nСписок штрафов:\n";
//            FineTable::FineInfo fineInfo;
//            db.getFines().fineIteratorReset();
//            while (db.getFines().fineIteratorHasNext()) {
//                fineInfo = db.getFines().fineIteratorNext();
//                cout << "• " << fineInfo.type << " (" << fineInfo.amount << " руб.)\n";
//            }
//            cout << "Введите тип штрафа: ";
//            getline(cin, fineType);
//
//            do {
//                cout << "Введите дату нарушения (ДД.ММ.ГГГГ): ";
//                getline(cin, date);
//            } while (!validateDate(date));
//
//            try {
//                db.addViolation(driverName, fineType, date);
//                cout << "Нарушение добавлено!\n";
//            }
//            catch (const exception& e) {
//                cout << "Ошибка: " << e.what() << endl;
//            }
//            break;
//        }
//        case 3: {
//            int recordId;
//            cout << "Введите ID нарушения: ";
//            cin >> recordId;
//            db.markFineAsPaid(recordId);
//            break;
//        }
//        }
//    } while (choice != 4);
//}
//
//void UserInterface::showStatisticsMenu() {
//    int choice;
//    do {
//        cout << "\n========== СТАТИСТИКА ==========\n"
//            << "1. Нарушения по городам\n"
//            << "2. Топ нарушителей\n"
//            << "3. Назад\n"
//            << "Выберите опцию: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            map<string, int> cityViolations;
//            db.getCities().cityIteratorReset();
//            string city;
//            while (db.getCities().cityIteratorHasNext()) {
//                city = db.getCities().cityIteratorNext();
//                cityViolations[city] = 0;
//            }
//
//            FineRegistry::ViolationInfo info;
//            db.getRegistry().violationIteratorReset();
//            while (db.getRegistry().violationIteratorHasNext()) {
//                info = db.getRegistry().violationIteratorNext(
//                    db.getDrivers(), db.getCities(), db.getFines()
//                );
//                cityViolations[info.cityName]++;
//            }
//
//            cout << "\nКоличество нарушений по городам:\n";
//            for (const auto& entry : cityViolations) {
//                cout << "• " << entry.first << ": " << entry.second << endl;
//            }
//            break;
//        }
//        case 2: {
//            map<string, int> driverViolations;
//            DriverTable::DriverInfo driverInfo;
//            db.getDrivers().driverIteratorReset();
//            while (db.getDrivers().driverIteratorHasNext()) {
//                driverInfo = db.getDrivers().driverIteratorNext(db.getCities());
//                driverViolations[driverInfo.fullName] = 0;
//            }
//
//            FineRegistry::ViolationInfo info;
//            db.getRegistry().violationIteratorReset();
//            while (db.getRegistry().violationIteratorHasNext()) {
//                info = db.getRegistry().violationIteratorNext(
//                    db.getDrivers(), db.getCities(), db.getFines()
//                );
//                driverViolations[info.driverName]++;
//            }
//
//            vector<pair<string, int>> sortedViolations(
//                driverViolations.begin(), driverViolations.end()
//            );
//            sort(sortedViolations.begin(), sortedViolations.end(),
//                [](auto& a, auto& b) { return a.second > b.second; });
//
//            cout << "\nТоп-5 нарушителей:\n";
//            for (size_t i = 0; i < min(5, (int)sortedViolations.size()); i++) {
//                cout << i + 1 << ". " << sortedViolations[i].first
//                    << " (" << sortedViolations[i].second << " нарушений)\n";
//            }
//            break;
//        }
//        }
//    } while (choice != 3);
//}



#include "UserInterface.h"
#include <iostream>
#include <iomanip>
#include <clocale>
#include <limits>
#include <algorithm>
#include <regex>
#include <Windows.h>

using namespace std;

bool UserInterface::validateDate(const string& date) {
    regex pattern(R"(^(0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.\d{4}$)");
    return regex_match(date, pattern);
}

bool UserInterface::validateName(const string& name) {
    return all_of(name.begin(), name.end(), [](char c) {
        return isalpha(c) || c == ' ' || c == '-';
        });
}

void UserInterface::printTableHeader(const vector<string>& headers) {
    const int COLUMN_WIDTH = 25;
    cout << "\n";
    for (const auto& header : headers) {
        cout << "| " << left << setw(COLUMN_WIDTH - 2) << header << " ";
    }
    cout << "|\n" << string(headers.size() * COLUMN_WIDTH, '-') << "\n";
}

void UserInterface::printTableRow(const vector<string>& cells, size_t columnWidth) {
    for (const auto& cell : cells) {
        cout << "| " << left << setw(columnWidth - 2) << cell.substr(0, columnWidth - 3) << " ";
    }
    cout << "|\n";
}

void UserInterface::run() {
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(CP_UTF8);
    db.loadAll();
    showMainMenu();
    db.saveAll();
}

void UserInterface::showMainMenu() {
    int choice;
    do {
        cout << "\n========== ГЛАВНОЕ МЕНЮ ==========\n"
            << "1. Управление городами\n"
            << "2. Управление водителями\n"
            << "3. Управление штрафами\n"
            << "4. Управление нарушениями\n"
            << "5. Статистика\n"
            << "6. Выход\n"
            << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1: showCityMenu(); break;
        case 2: showDriverMenu(); break;
        case 3: showFineMenu(); break;
        case 4: showViolationMenu(); break;
        case 5: showStatisticsMenu(); break;
        case 6: cout << "Сохранение данных...\n"; break;
        default:
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "Неверный ввод!\n";
        }
    } while (choice != 6);
}

void UserInterface::showCityMenu() {
    int choice;
    do {
        cout << "\n========== УПРАВЛЕНИЕ ГОРОДАМИ ==========\n"
            << "1. Список городов\n"
            << "2. Добавить город\n"
            << "3. Удалить город\n"
            << "4. Назад\n"
            << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            vector<string> headers = { "Название", "Население", "Тип", "Градация" };
            printTableHeader(headers);

            db.getCities().cityIteratorReset();
            while (db.getCities().cityIteratorHasNext()) {
                auto city = db.getCities().cityIteratorNext();
                vector<string> cells = {
                    city.name,
                    to_string(city.population) + " чел.",
                    CityTable::settlementTypeToString(city.type),
                    CityTable::populationGradeToString(city.grade)
                };
                printTableRow(cells, 25);
            }
            break;
        }
        case 2: {
            string name;
            int population;
            int gradeChoice, typeChoice;

            cout << "Введите название города: ";
            cin.ignore();
            getline(cin, name);

            cout << "Введите население: ";
            cin >> population;

            cout << "Выберите градацию (1-Малый, 2-Средний, 3-Крупный): ";
            cin >> gradeChoice;

            cout << "Выберите тип (1-Город, 2-Посёлок, 3-Деревня): ";
            cin >> typeChoice;

            try {
                db.addCity(name,
                    population,
                    static_cast<CityTable::PopulationGrade>(gradeChoice - 1),
                    static_cast<CityTable::SettlementType>(typeChoice - 1));
                cout << "Город добавлен!\n";
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            string name;
            cout << "Введите название города: ";
            cin.ignore();
            getline(cin, name);
            db.deleteCity(name);
            break;
        }
        }
    } while (choice != 4);
}

void UserInterface::showDriverMenu() {
    int choice;
    do {
        cout << "\n========== УПРАВЛЕНИЕ ВОДИТЕЛЯМИ ==========\n"
            << "1. Список водителей\n"
            << "2. Добавить водителя\n"
            << "3. Удалить водителя\n"
            << "4. Назад\n"
            << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            vector<string> headers = { "ФИО", "Дата рождения", "Город проживания" };
            printTableHeader(headers);

            db.getDrivers().driverIteratorReset();
            while (db.getDrivers().driverIteratorHasNext()) {
                auto driver = db.getDrivers().driverIteratorNext();
                vector<string> cells = {
                    driver.fullName,
                    driver.birthDate,
                    db.getCities().getCityNameById(driver.cityId)
                };
                printTableRow(cells, 25);
            }
            break;
        }
        case 2: {
            string name, birthDate, cityName;
            bool valid = false;

            do {
                cout << "Введите ФИО: ";
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                getline(cin, name);
                valid = validateName(name);
                if (!valid) cout << "Некорректное имя!\n";
            } while (!valid);

            do {
                cout << "Введите дату рождения (ДД.ММ.ГГГГ): ";
                getline(cin, birthDate);
                valid = validateDate(birthDate);
                if (!valid) cout << "Некорректная дата!\n";
            } while (!valid);

            cout << "Доступные города:\n";
            db.getCities().cityIteratorReset();
            while (db.getCities().cityIteratorHasNext()) {
                auto city = db.getCities().cityIteratorNext();
                cout << "• " << city.name << endl;
            }
            cout << "Введите название города: ";
            getline(cin, cityName);

            try {
                db.addDriver(name, birthDate, cityName);
                cout << "Водитель добавлен!\n";
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            string name;
            cout << "Введите ФИО водителя: ";
            cin.ignore();
            getline(cin, name);
            db.deleteDriver(name);
            break;
        }
        }
    } while (choice != 4);
}

void UserInterface::showFineMenu() {
    int choice;
    do {
        cout << "\n========== УПРАВЛЕНИЕ ШТРАФАМИ ==========\n"
            << "1. Список штрафов\n"
            << "2. Добавить штраф\n"
            << "3. Удалить штраф\n"
            << "4. Назад\n"
            << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            vector<string> headers = { "Тип нарушения", "Сумма", "Тяжесть" };
            printTableHeader(headers);

            db.getFines().fineIteratorReset();
            while (db.getFines().fineIteratorHasNext()) {
                auto fine = db.getFines().fineIteratorNext();
                vector<string> cells = {
                    fine.type,
                    to_string(fine.amount) + " руб.",
                    FineTable::severityToString(fine.severity)
                };
                printTableRow(cells, 25);
            }
            break;
        }
        case 2: {
            string type;
            double amount;
            int severity;

            cout << "Введите тип нарушения: ";
            cin.ignore();
            getline(cin, type);

            cout << "Введите сумму штрафа: ";
            cin >> amount;

            cout << "Выберите тяжесть (1-Легкое, 2-Среднее, 3-Тяжелое): ";
            cin >> severity;

            try {
                db.addFine(type, amount, static_cast<FineTable::Severity>(severity - 1));
                cout << "Штраф добавлен!\n";
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            string type;
            cout << "Введите тип штрафа: ";
            cin.ignore();
            getline(cin, type);
            db.getFines().deleteFine(type);
            break;
        }
        }
    } while (choice != 4);
}

void UserInterface::showViolationMenu() {
    int choice;
    do {
        cout << "\n========== УПРАВЛЕНИЕ НАРУШЕНИЯМИ ==========\n"
            << "1. Все нарушения\n"
            << "2. Добавить нарушение\n"
            << "3. Отметить как оплаченное\n"
            << "4. Назад\n"
            << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            vector<string> headers = { "Водитель", "Город", "Штраф", "Дата", "Сумма", "Статус" };
            printTableHeader(headers);

            db.getRegistry().violationIteratorReset();
            while (db.getRegistry().violationIteratorHasNext()) {
                auto violation = db.getRegistry().violationIteratorNext(
                    db.getDrivers(), db.getCities(), db.getFines()
                );
                vector<string> cells = {
                    violation.driverName,
                    violation.cityName,
                    violation.fineType,
                    violation.date,
                    to_string(violation.amount) + " руб.",
                    violation.paid ? "Оплачено" : "Не оплачено"
                };
                printTableRow(cells, 25);
            }
            break;
        }
        case 2: {
            string driverName, fineType, date;

            cout << "\nСписок водителей:\n";
            db.getDrivers().driverIteratorReset();
            while (db.getDrivers().driverIteratorHasNext()) {
                auto driver = db.getDrivers().driverIteratorNext();
                cout << "• " << driver.fullName << endl;
            }
            cout << "Введите ФИО водителя: ";
            cin.ignore();
            getline(cin, driverName);

            cout << "\nСписок штрафов:\n";
            db.getFines().fineIteratorReset();
            while (db.getFines().fineIteratorHasNext()) {
                auto fine = db.getFines().fineIteratorNext();
                cout << "• " << fine.type << " (" << fine.amount << " руб.)\n";
            }
            cout << "Введите тип штрафа: ";
            getline(cin, fineType);

            do {
                cout << "Введите дату нарушения (ДД.ММ.ГГГГ): ";
                getline(cin, date);
            } while (!validateDate(date));

            try {
                db.addViolation(driverName, fineType, date);
                cout << "Нарушение добавлено!\n";
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            int recordId;
            cout << "Введите ID нарушения: ";
            cin >> recordId;
            db.markFineAsPaid(recordId);
            break;
        }
        }
    } while (choice != 4);
}

void UserInterface::showStatisticsMenu() {
    int choice;
    do {
        cout << "\n========== СТАТИСТИКА ==========\n"
            << "1. Нарушения по городам\n"
            << "2. Топ нарушителей\n"
            << "3. Назад\n"
            << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            map<string, int> cityViolations;
            db.getCities().cityIteratorReset();
            while (db.getCities().cityIteratorHasNext()) {
                auto city = db.getCities().cityIteratorNext();
                cityViolations[city.name] = 0;
            }

            db.getRegistry().violationIteratorReset();
            while (db.getRegistry().violationIteratorHasNext()) {
                auto violation = db.getRegistry().violationIteratorNext(
                    db.getDrivers(), db.getCities(), db.getFines()
                );
                cityViolations[violation.cityName]++;
            }

            vector<string> headers = { "Город", "Количество нарушений" };
            printTableHeader(headers);
            for (const auto& entry : cityViolations) {
                vector<string> cells = {
                    entry.first,
                    to_string(entry.second)
                };
                printTableRow(cells, 25);
            }
            break;
        }
        case 2: {
            map<string, int> driverViolations;
            db.getDrivers().driverIteratorReset();
            while (db.getDrivers().driverIteratorHasNext()) {
                auto driver = db.getDrivers().driverIteratorNext();
                driverViolations[driver.fullName] = 0;
            }

            db.getRegistry().violationIteratorReset();
            while (db.getRegistry().violationIteratorHasNext()) {
                auto violation = db.getRegistry().violationIteratorNext(
                    db.getDrivers(), db.getCities(), db.getFines()
                );
                driverViolations[violation.driverName]++;
            }

            vector<pair<string, int>> sortedViolations(
                driverViolations.begin(), driverViolations.end()
            );
            sort(sortedViolations.begin(), sortedViolations.end(),
                [](auto& a, auto& b) { return a.second > b.second; });

            vector<string> headers = { "Место", "Водитель", "Нарушений" };
            printTableHeader(headers);
            for (size_t i = 0; i < min(5, (int)sortedViolations.size()); i++) {
                vector<string> cells = {
                    to_string(i + 1),
                    sortedViolations[i].first,
                    to_string(sortedViolations[i].second)
                };
                printTableRow(cells, 25);
            }
            break;
        }
        }
    } while (choice != 3);
}