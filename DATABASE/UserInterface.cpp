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



//#include "UserInterface.h"
//#include <iostream>
//#include <iomanip>
//#include <clocale>
//#include <limits>
//#include <algorithm>
//#include <regex>
//#include <Windows.h>
//
//using namespace std;
//
//bool UserInterface::validateDate(const string& date) {
//    regex pattern(R"(^(0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.\d{4}$)");
//    return regex_match(date, pattern);
//}
//
//bool UserInterface::validateName(const string& name) {
//    return all_of(name.begin(), name.end(), [](char c) {
//        return isalpha(c) || c == ' ' || c == '-';
//        });
//}
//
//void UserInterface::printTableHeader(const vector<string>& headers) {
//    const int COLUMN_WIDTH = 25;
//    cout << "\n";
//    for (const auto& header : headers) {
//        cout << "| " << left << setw(COLUMN_WIDTH - 2) << header << " ";
//    }
//    cout << "|\n" << string(headers.size() * COLUMN_WIDTH, '-') << "\n";
//}
//
//void UserInterface::printTableRow(const vector<string>& cells, size_t columnWidth) {
//    for (const auto& cell : cells) {
//        cout << "| " << left << setw(columnWidth - 2) << cell.substr(0, columnWidth - 3) << " ";
//    }
//    cout << "|\n";
//}
//
//void UserInterface::run() {
//    setlocale(LC_ALL, "Russian");
//    SetConsoleOutputCP(CP_UTF8);
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
//            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
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
//            vector<string> headers = { "Название", "Население", "Тип", "Градация" };
//            printTableHeader(headers);
//
//            db.getCities().cityIteratorReset();
//            while (db.getCities().cityIteratorHasNext()) {
//                auto city = db.getCities().cityIteratorNext();
//                vector<string> cells = {
//                    city.name,
//                    to_string(city.population) + " чел.",
//                    CityTable::settlementTypeToString(city.type),
//                    CityTable::populationGradeToString(city.grade)
//                };
//                printTableRow(cells, 25);
//            }
//            break;
//        }
//        case 2: {
//            string name;
//            int population;
//            int gradeChoice, typeChoice;
//
//            cout << "Введите название города: ";
//            cin.ignore();
//            getline(cin, name);
//
//            cout << "Введите население: ";
//            cin >> population;
//
//            cout << "Выберите градацию (1-Малый, 2-Средний, 3-Крупный): ";
//            cin >> gradeChoice;
//
//            cout << "Выберите тип (1-Город, 2-Посёлок, 3-Деревня): ";
//            cin >> typeChoice;
//
//            try {
//                db.addCity(name,
//                    population,
//                    static_cast<CityTable::PopulationGrade>(gradeChoice - 1),
//                    static_cast<CityTable::SettlementType>(typeChoice - 1));
//                cout << "Город добавлен!\n";
//            }
//            catch (const exception& e) {
//                cout << "Ошибка: " << e.what() << endl;
//            }
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
//            vector<string> headers = { "ФИО", "Дата рождения", "Город проживания" };
//            printTableHeader(headers);
//
//            db.getDrivers().driverIteratorReset();
//            while (db.getDrivers().driverIteratorHasNext()) {
//                auto driver = db.getDrivers().driverIteratorNext();
//                vector<string> cells = {
//                    driver.fullName,
//                    driver.birthDate,
//                    db.getCities().getCityNameById(driver.cityId)
//                };
//                printTableRow(cells, 25);
//            }
//            break;
//        }
//        case 2: {
//            string name, birthDate, cityName;
//            bool valid = false;
//
//            do {
//                cout << "Введите ФИО: ";
//                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//                getline(cin, name);
//                valid = validateName(name);
//                if (!valid) cout << "Некорректное имя!\n";
//            } while (!valid);
//
//            do {
//                cout << "Введите дату рождения (ДД.ММ.ГГГГ): ";
//                getline(cin, birthDate);
//                valid = validateDate(birthDate);
//                if (!valid) cout << "Некорректная дата!\n";
//            } while (!valid);
//
//            cout << "Доступные города:\n";
//            db.getCities().cityIteratorReset();
//            while (db.getCities().cityIteratorHasNext()) {
//                auto city = db.getCities().cityIteratorNext();
//                cout << "• " << city.name << endl;
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
//            vector<string> headers = { "Тип нарушения", "Сумма", "Тяжесть" };
//            printTableHeader(headers);
//
//            db.getFines().fineIteratorReset();
//            while (db.getFines().fineIteratorHasNext()) {
//                auto fine = db.getFines().fineIteratorNext();
//                vector<string> cells = {
//                    fine.type,
//                    to_string(fine.amount) + " руб.",
//                    FineTable::severityToString(fine.severity)
//                };
//                printTableRow(cells, 25);
//            }
//            break;
//        }
//        case 2: {
//            string type;
//            double amount;
//            int severity;
//
//            cout << "Введите тип нарушения: ";
//            cin.ignore();
//            getline(cin, type);
//
//            cout << "Введите сумму штрафа: ";
//            cin >> amount;
//
//            cout << "Выберите тяжесть (1-Легкое, 2-Среднее, 3-Тяжелое): ";
//            cin >> severity;
//
//            try {
//                db.addFine(type, amount, static_cast<FineTable::Severity>(severity - 1));
//                cout << "Штраф добавлен!\n";
//            }
//            catch (const exception& e) {
//                cout << "Ошибка: " << e.what() << endl;
//            }
//            break;
//        }
//        case 3: {
//            string type;
//            cout << "Введите тип штрафа: ";
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
//            vector<string> headers = { "Водитель", "Город", "Штраф", "Дата", "Сумма", "Статус" };
//            printTableHeader(headers);
//
//            db.getRegistry().violationIteratorReset();
//            while (db.getRegistry().violationIteratorHasNext()) {
//                auto violation = db.getRegistry().violationIteratorNext(
//                    db.getDrivers(), db.getCities(), db.getFines()
//                );
//                vector<string> cells = {
//                    violation.driverName,
//                    violation.cityName,
//                    violation.fineType,
//                    violation.date,
//                    to_string(violation.amount) + " руб.",
//                    violation.paid ? "Оплачено" : "Не оплачено"
//                };
//                printTableRow(cells, 25);
//            }
//            break;
//        }
//        case 2: {
//            string driverName, fineType, date;
//
//            cout << "\nСписок водителей:\n";
//            db.getDrivers().driverIteratorReset();
//            while (db.getDrivers().driverIteratorHasNext()) {
//                auto driver = db.getDrivers().driverIteratorNext();
//                cout << "• " << driver.fullName << endl;
//            }
//            cout << "Введите ФИО водителя: ";
//            cin.ignore();
//            getline(cin, driverName);
//
//            cout << "\nСписок штрафов:\n";
//            db.getFines().fineIteratorReset();
//            while (db.getFines().fineIteratorHasNext()) {
//                auto fine = db.getFines().fineIteratorNext();
//                cout << "• " << fine.type << " (" << fine.amount << " руб.)\n";
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
//            while (db.getCities().cityIteratorHasNext()) {
//                auto city = db.getCities().cityIteratorNext();
//                cityViolations[city.name] = 0;
//            }
//
//            db.getRegistry().violationIteratorReset();
//            while (db.getRegistry().violationIteratorHasNext()) {
//                auto violation = db.getRegistry().violationIteratorNext(
//                    db.getDrivers(), db.getCities(), db.getFines()
//                );
//                cityViolations[violation.cityName]++;
//            }
//
//            vector<string> headers = { "Город", "Количество нарушений" };
//            printTableHeader(headers);
//            for (const auto& entry : cityViolations) {
//                vector<string> cells = {
//                    entry.first,
//                    to_string(entry.second)
//                };
//                printTableRow(cells, 25);
//            }
//            break;
//        }
//        case 2: {
//            map<string, int> driverViolations;
//            db.getDrivers().driverIteratorReset();
//            while (db.getDrivers().driverIteratorHasNext()) {
//                auto driver = db.getDrivers().driverIteratorNext();
//                driverViolations[driver.fullName] = 0;
//            }
//
//            db.getRegistry().violationIteratorReset();
//            while (db.getRegistry().violationIteratorHasNext()) {
//                auto violation = db.getRegistry().violationIteratorNext(
//                    db.getDrivers(), db.getCities(), db.getFines()
//                );
//                driverViolations[violation.driverName]++;
//            }
//
//            vector<pair<string, int>> sortedViolations(
//                driverViolations.begin(), driverViolations.end()
//            );
//            sort(sortedViolations.begin(), sortedViolations.end(),
//                [](auto& a, auto& b) { return a.second > b.second; });
//
//            vector<string> headers = { "Место", "Водитель", "Нарушений" };
//            printTableHeader(headers);
//            for (size_t i = 0; i < min(5, (int)sortedViolations.size()); i++) {
//                vector<string> cells = {
//                    to_string(i + 1),
//                    sortedViolations[i].first,
//                    to_string(sortedViolations[i].second)
//                };
//                printTableRow(cells, 25);
//            }
//            break;
//        }
//        }
//    } while (choice != 3);
//}



//#include "UserInterface.h"
//#include <sstream>
//#include <iostream>
//#include <iomanip>
//#include <clocale>
//#include <limits>
//#include <algorithm>
//#include <regex>
//#include <Windows.h>
//#include <ctime>
//#define NOMINMAX
//
//using namespace std;
//
//// ==================== ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ====================
//
//bool UserInterface::validateDate(const string& date) {
//    regex pattern(R"(^(0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.\d{4}$)");
//    return regex_match(date, pattern);
//}
//
//bool UserInterface::validateName(const std::string& name) const {
//    return std::all_of(name.begin(), name.end(), [](char c) {
//        return std::isalpha(c) || c == ' ' || c == '-';
//        });
//}
//
//tm UserInterface::parseDate(const string& dateStr) {
//    tm date = {};
//    istringstream ss(dateStr);
//    ss >> get_time(&date, "%d.%m.%Y");
//    return date;
//}
//
//// ==================== ФОРМАТИРОВАНИЕ ТАБЛИЦ ====================
//
//vector<vector<string>> UserInterface::prepareViolationData() {
//    vector<vector<string>> data;
//    db.getRegistry().violationIteratorReset();
//    while (db.getRegistry().violationIteratorHasNext()) {
//        auto violation = db.getRegistry().violationIteratorNext(
//            db.getDrivers(), db.getCities(), db.getFines()
//        );
//        data.push_back({
//            violation.driverName,
//            violation.cityName,
//            violation.fineType,
//            violation.date,
//            to_string(violation.amount) + " руб.",
//            violation.paid ? "Оплачено" : "Не оплачено"
//            });
//    }
//    return data;
//}
//
//void UserInterface::printDynamicTable(
//    const vector<string>& headers,
//    const vector<vector<string>>& data
//) {
//    vector<int> widths = TableFormatter::calculateColumnWidths(headers, data);
//
//    // Шапка таблицы
//    cout << "\n";
//    for (size_t i = 0; i < headers.size(); ++i) {
//        cout << "| " << left << setw(widths[i]) << headers[i] << " ";
//    }
//    cout << "|\n" << string(accumulate(widths.begin(), widths.end(), 0) + headers.size() * 3, '-') << "\n";
//
//    // Данные
//    for (const auto& row : data) {
//        for (size_t i = 0; i < row.size(); ++i) {
//            cout << "| " << left << setw(widths[i]) << row[i] << " ";
//        }
//        cout << "|\n";
//    }
//}
//
//// ==================== ФИЛЬТРАЦИЯ ====================
//
//bool UserInterface::matchesFilters(const FineRegistry::ViolationInfo& violation) {
//    for (const auto& filter : active_filters) {
//        if (filter.field == "city" && violation.cityName != filter.value)
//            return false;
//
//        if (filter.field == "дата") {
//            tm violDate = parseDate(violation.date);
//            if (filter.is_range) {
//                tm from = parseDate(filter.range_from);
//                tm to = parseDate(filter.range_to);
//                if (difftime(mktime(&violDate), mktime(&from)) < 0 ||
//                    difftime(mktime(&violDate), mktime(&to)) > 0) return false;
//            }
//            else if (violation.date != filter.value) {
//                return false;
//            }
//        }
//
//        if (filter.field == "сумма") {
//            double amount = violation.amount;
//            if (filter.is_range) {
//                double from = stod(filter.range_from);
//                double to = stod(filter.range_to);
//                if (amount < from || amount > to) return false;
//            }
//            else if (amount != stod(filter.value)) {
//                return false;
//            }
//        }
//    }
//    return true;
//}
//
//void UserInterface::applyFilters() {
//    vector<vector<string>> filteredData;
//    auto violations = db.getAllViolations();
//
//    for (const auto& violation : violations) {
//        if (matchesFilters(violation)) {
//            filteredData.push_back({
//                violation.driverName,
//                violation.cityName,
//                violation.fineType,
//                violation.date,
//                to_string(violation.amount) + " руб.",
//                violation.paid ? "Оплачено" : "Не оплачено"
//                });
//        }
//    }
//
//    printDynamicTable({ "Водитель", "Город", "Штраф", "Дата", "Сумма", "Статус" }, filteredData);
//}
//
//void UserInterface::filterMenu() {
//    int choice;
//    do {
//        cout << "\n=== УПРАВЛЕНИЕ ФИЛЬТРАМИ ==="
//            << "\n1. Добавить фильтр"
//            << "\n2. Сбросить фильтры"
//            << "\n3. Назад"
//            << "\nВыберите: ";
//        cin >> choice;
//        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//
//        switch (choice) {
//        case 1:
//            addFilterCondition();
//            break;
//        case 2:
//            resetFilters();
//            applyFilters();
//            break;
//        case 3:
//            return;
//        default:
//            cout << "Неверный выбор!\n";
//        }
//    } while (true);
//}
//
//void UserInterface::addFilterCondition() {
//    FilterCondition cond;
//
//    cout << "\nДоступные поля: город, дата, штраф, сумма, статус: ";
//    getline(cin, cond.field);
//
//    if (cond.field != "city" && cond.field != "data" &&
//        cond.field != "fine" && cond.field != "sum" && cond.field != "state") {
//        cout << "Некорректное поле!\n";
//        return;
//    }
//
//    cout << "Тип фильтра (1-точное значение, 2-диапазон): ";
//    int type;
//    cin >> type;
//    cin.ignore();
//
//    if (type == 2 && (cond.field == "дата" || cond.field == "сумма")) {
//        cond.is_range = true;
//        cout << "Начало диапазона: ";
//        getline(cin, cond.range_from);
//        cout << "Конец диапазона: ";
//        getline(cin, cond.range_to);
//    }
//    else if (type == 1) {
//        cout << "Значение: ";
//        getline(cin, cond.value);
//    }
//    else {
//        cout << "Недопустимый тип фильтра!\n";
//        return;
//    }
//
//    active_filters.push_back(cond);
//    applyFilters();
//
//    cout << "Добавить ещё условие? (1-да/0-нет): ";
//    cin >> type;
//    if (type == 1)
//        addFilterCondition();
//}
//
//void UserInterface::resetFilters() {
//    active_filters.clear();
//    cout << "Фильтры сброшены!\n";
//}
//
//// ==================== ОСНОВНЫЕ МЕНЮ ====================
//
//void UserInterface::run() {
//    setlocale(LC_ALL, "Russian");
//    SetConsoleOutputCP(CP_UTF8);
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
//            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//            cout << "Неверный ввод!\n";
//        }
//    } while (choice != 6);
//}
//
//// ----------- Управление городами -----------
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
//            vector<vector<string>> cityData;
//            db.getCities().cityIteratorReset();
//            while (db.getCities().cityIteratorHasNext()) {
//                auto city = db.getCities().cityIteratorNext();
//                cityData.push_back({
//                    city.name,
//                    to_string(city.population) + " чел.",
//                    CityTable::settlementTypeToString(city.type),
//                    CityTable::populationGradeToString(city.grade)
//                    });
//            }
//            printDynamicTable({ "Название", "Население", "Тип", "Градация" }, cityData);
//            break;
//        }
//        case 2: {
//            string name;
//            int population, gradeChoice, typeChoice;
//
//            cout << "Введите название города: ";
//            cin.ignore();
//            getline(cin, name);
//
//            cout << "Введите население: ";
//            while (!(cin >> population) || population < 0) {
//                cin.clear();
//                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//                cout << "Ошибка! Введите положительное число: ";
//            }
//
//            cout << "Градация населения (1-Малый, 2-Средний, 3-Крупный): ";
//            while (!(cin >> gradeChoice) || gradeChoice < 1 || gradeChoice > 3) {
//                cin.clear();
//                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//                cout << "Ошибка! Введите 1-3: ";
//            }
//
//            cout << "Тип поселения (1-Город, 2-Посёлок, 3-Деревня): ";
//            while (!(cin >> typeChoice) || typeChoice < 1 || typeChoice > 3) {
//                cin.clear();
//                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//                cout << "Ошибка! Введите 1-3: ";
//            }
//
//            try {
//                db.addCity(
//                    name,
//                    population,
//                    static_cast<CityTable::PopulationGrade>(gradeChoice - 1),
//                    static_cast<CityTable::SettlementType>(typeChoice - 1)
//                );
//                cout << "Город добавлен!\n";
//            }
//            catch (const exception& e) {
//                cout << "Ошибка: " << e.what() << endl;
//            }
//            break;
//        }
//        case 3: {
//            string name;
//            cout << "Введите название города: ";
//            cin.ignore();
//            getline(cin, name);
//            try {
//                db.deleteCity(name);
//                cout << "Город удален!\n";
//            }
//            catch (const exception& e) {
//                cout << "Ошибка: " << e.what() << endl;
//            }
//            break;
//        }
//        case 4: return;
//        default:
//            cin.clear();
//            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//            cout << "Неверный выбор!\n";
//        }
//    } while (true);
//}
//
//// ----------- Управление водителями -----------
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
//            vector<vector<string>> driverData;
//            db.getDrivers().driverIteratorReset();
//            while (db.getDrivers().driverIteratorHasNext()) {
//                auto driver = db.getDrivers().driverIteratorNext();
//                driverData.push_back({
//                    driver.fullName,
//                    driver.birthDate,
//                    db.getCities().getCityNameById(driver.cityId)
//                    });
//            }
//            printDynamicTable({ "ФИО", "Дата рождения", "Город" }, driverData);
//            break;
//        }
//        case 2: {
//            string name, birthDate, cityName;
//            bool isValid = false;
//
//            do {
//                cout << "Введите ФИО: ";
//                cin.ignore();
//                getline(cin, name);
//                isValid = validateName(name);
//                if (!isValid) cout << "Некорректное имя! Только буквы, пробелы и дефисы.\n";
//            } while (!isValid);
//
//            do {
//                cout << "Введите дату рождения (ДД.ММ.ГГГГ): ";
//                getline(cin, birthDate);
//                isValid = validateDate(birthDate);
//                if (!isValid) cout << "Некорректный формат даты!\n";
//            } while (!isValid);
//
//            cout << "Доступные города:\n";
//            db.getCities().cityIteratorReset();
//            while (db.getCities().cityIteratorHasNext()) {
//                auto city = db.getCities().cityIteratorNext();
//                cout << "• " << city.name << endl;
//            }
//
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
//            try {
//                db.deleteDriver(name);
//                cout << "Водитель удален!\n";
//            }
//            catch (const exception& e) {
//                cout << "Ошибка: " << e.what() << endl;
//            }
//            break;
//        }
//        case 4: return;
//        default:
//            cin.clear();
//            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//            cout << "Неверный выбор!\n";
//        }
//    } while (true);
//}
//
//// ----------- Управление штрафами -----------
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
//            vector<vector<string>> fineData;
//            db.getFines().fineIteratorReset();
//            while (db.getFines().fineIteratorHasNext()) {
//                auto fine = db.getFines().fineIteratorNext();
//                fineData.push_back({
//                    fine.type,
//                    to_string(fine.amount) + " руб.",
//                    FineTable::severityToString(fine.severity)
//                    });
//            }
//            printDynamicTable({ "Тип", "Сумма", "Тяжесть" }, fineData);
//            break;
//        }
//        case 2: {
//            string type;
//            double amount;
//            int severity;
//
//            cout << "Введите тип нарушения: ";
//            cin.ignore();
//            getline(cin, type);
//
//            cout << "Введите сумму штрафа: ";
//            while (!(cin >> amount) || amount < 0) {
//                cin.clear();
//                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//                cout << "Ошибка! Введите положительное число: ";
//            }
//
//            cout << "Выберите тяжесть (1-Легкое, 2-Среднее, 3-Тяжелое): ";
//            while (!(cin >> severity) || severity < 1 || severity > 3) {
//                cin.clear();
//                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//                cout << "Ошибка! Введите 1-3: ";
//            }
//
//            try {
//                db.addFine(type, amount, static_cast<FineTable::Severity>(severity - 1));
//                cout << "Штраф добавлен!\n";
//            }
//            catch (const exception& e) {
//                cout << "Ошибка: " << e.what() << endl;
//            }
//            break;
//        }
//        case 3: {
//            string type;
//            cout << "Введите тип штрафа: ";
//            cin.ignore();
//            getline(cin, type);
//            try {
//                db.getFines().deleteFine(type);
//                cout << "Штраф удален!\n";
//            }
//            catch (const exception& e) {
//                cout << "Ошибка: " << e.what() << endl;
//            }
//            break;
//        }
//        case 4: return;
//        default:
//            cin.clear();
//            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//            cout << "Неверный выбор!\n";
//        }
//    } while (true);
//}
//
//// ----------- Управление нарушениями -----------
//void UserInterface::showViolationMenu() {
//    int choice;
//    do {
//        cout << "\n========== УПРАВЛЕНИЕ НАРУШЕНИЯМИ ==========\n"
//            << "1. Все нарушения\n"
//            << "2. Добавить нарушение\n"
//            << "3. Отметить как оплаченное\n"
//            << "4. Фильтровать нарушения\n"
//            << "5. Назад\n"
//            << "Выберите опцию: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            auto data = prepareViolationData();
//            printDynamicTable({ "Водитель", "Город", "Штраф", "Дата", "Сумма", "Статус" }, data);
//            break;
//        }
//        case 2: {
//            string driverName, fineType, date;
//            bool isValid = false;
//
//            cout << "\nСписок водителей:\n";
//            db.getDrivers().driverIteratorReset();
//            while (db.getDrivers().driverIteratorHasNext()) {
//                auto driver = db.getDrivers().driverIteratorNext();
//                cout << "• " << driver.fullName << endl;
//            }
//
//            do {
//                cout << "Введите ФИО водителя: ";
//                cin.ignore();
//                getline(cin, driverName);
//                isValid = db.getDrivers().getDriverId(driverName) != -1;
//                if (!isValid) cout << "Водитель не найден!\n";
//            } while (!isValid);
//
//            cout << "\nСписок штрафов:\n";
//            db.getFines().fineIteratorReset();
//            while (db.getFines().fineIteratorHasNext()) {
//                auto fine = db.getFines().fineIteratorNext();
//                cout << "• " << fine.type << " (" << fine.amount << " руб.)\n";
//            }
//
//            do {
//                cout << "Введите тип штрафа: ";
//                getline(cin, fineType);
//                isValid = db.getFines().getFineIdByType(fineType) != -1;
//                if (!isValid) cout << "Штраф не найден!\n";
//            } while (!isValid);
//
//            do {
//                cout << "Введите дату нарушения (ДД.ММ.ГГГГ): ";
//                getline(cin, date);
//                isValid = validateDate(date);
//                if (!isValid) cout << "Некорректная дата!\n";
//            } while (!isValid);
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
//            while (!(cin >> recordId) || recordId < 1) {
//                cin.clear();
//                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//                cout << "Ошибка! Введите положительное число: ";
//            }
//            try {
//                db.markFineAsPaid(recordId);
//                cout << "Статус обновлен!\n";
//            }
//            catch (const exception& e) {
//                cout << "Ошибка: " << e.what() << endl;
//            }
//            break;
//        }
//        case 4:
//            filterMenu();
//            break;
//        case 5:
//            return;
//        default:
//            cin.clear();
//            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//            cout << "Неверный выбор!\n";
//        }
//    } while (true);
//}
//
//// ----------- Статистика -----------
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
//            map<string, int> cityStats;
//            db.getCities().cityIteratorReset();
//            while (db.getCities().cityIteratorHasNext()) {
//                auto city = db.getCities().cityIteratorNext();
//                cityStats[city.name] = 0;
//            }
//
//            db.getRegistry().violationIteratorReset();
//            while (db.getRegistry().violationIteratorHasNext()) {
//                auto violation = db.getRegistry().violationIteratorNext(
//                    db.getDrivers(), db.getCities(), db.getFines()
//                );
//                cityStats[violation.cityName]++;
//            }
//
//            vector<vector<string>> statsData;
//            for (const auto& entry : cityStats) { // Используем entry вместо [city, count]
//                statsData.push_back({
//                    entry.first,                // Город (ключ)
//                    std::to_string(entry.second) // Количество нарушений (значение)
//                    });
//            }
//            printDynamicTable({ "Город", "Нарушений" }, statsData);
//            break;
//        }
//        case 2: {
//            map<string, int> driverStats;
//            db.getDrivers().driverIteratorReset();
//            while (db.getDrivers().driverIteratorHasNext()) {
//                auto driver = db.getDrivers().driverIteratorNext();
//                driverStats[driver.fullName] = 0;
//            }
//
//            db.getRegistry().violationIteratorReset();
//            while (db.getRegistry().violationIteratorHasNext()) {
//                auto violation = db.getRegistry().violationIteratorNext(
//                    db.getDrivers(), db.getCities(), db.getFines()
//                );
//                driverStats[violation.driverName]++;
//            }
//
//            vector<pair<string, int>> sortedStats(
//                driverStats.begin(), driverStats.end()
//            );
//            sort(sortedStats.begin(), sortedStats.end(),
//                [](auto& a, auto& b) { return a.second > b.second; });
//
//            vector<vector<string>> topData;
//            for (size_t i = 0; i < min(5, (int)sortedStats.size()); ++i) {
//                topData.push_back({
//                    to_string(i + 1),
//                    sortedStats[i].first,
//                    to_string(sortedStats[i].second)
//                    });
//            }
//            printDynamicTable({ "Место", "Водитель", "Нарушений" }, topData);
//            break;
//        }
//        case 3:
//            return;
//        default:
//            cin.clear();
//            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//            cout << "Неверный выбор!\n";
//        }
//    } while (true);
//}


// UserInterface.cpp

#include "UserInterface.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <clocale>
#include <iomanip>
using namespace std;

// Ширины колонок (без ID)
static constexpr int NAME_WIDTH = 20;
static constexpr int POPULATION_WIDTH = 12;
static constexpr int TYPE_WIDTH = 10;
static constexpr int DRIVER_NAME_WIDTH = 25;
static constexpr int BIRTH_WIDTH = 12;
static constexpr int FINE_TYPE_WIDTH = 20;
static constexpr int AMOUNT_WIDTH = 10;
static constexpr int SEVERITY_WIDTH = 10;
static constexpr int DATE_WIDTH = 12;
static constexpr int PAID_WIDTH = 6;

// Печать разделительной строки для таблицы городов
static void printCitiesBorder() {
    cout << '+'
        << string(NAME_WIDTH + 2, '-') << '+'
        << string(POPULATION_WIDTH + 2, '-') << '+'
        << string(TYPE_WIDTH + 2, '-') << '+'
        << "\n";
}

// Печать заголовка таблицы городов
static void printCitiesHeader() {
    printCitiesBorder();
    cout << "| " << left << setw(NAME_WIDTH) << "Название" << " | "
        << left << setw(POPULATION_WIDTH) << "Население" << " | "
        << left << setw(TYPE_WIDTH) << "Тип" << " |\n";
    printCitiesBorder();
}

// Печать строки с данными о городе
static void printCityRow(const string& name, int population, const string& type) {
    cout << "| " << left << setw(NAME_WIDTH) << name << " | "
        << right << setw(POPULATION_WIDTH) << population << " | "
        << left << setw(TYPE_WIDTH) << type << " |\n";
}

// Печать разделительной строки для таблицы водителей
static void printDriversBorder() {
    cout << '+'
        << string(DRIVER_NAME_WIDTH + 2, '-') << '+'
        << string(BIRTH_WIDTH + 2, '-') << '+'
        << string(NAME_WIDTH + 2, '-') << '+'
        << "\n";
}

// Печать заголовка таблицы водителей
static void printDriversHeader() {
    printDriversBorder();
    cout << "| " << left << setw(DRIVER_NAME_WIDTH) << "ФИО" << " | "
        << left << setw(BIRTH_WIDTH) << "Дата рождения" << " | "
        << left << setw(NAME_WIDTH) << "Город" << " |\n";
    printDriversBorder();
}

// Печать строки с данными о водителе
static void printDriverRow(const string& fullName, const string& birthDate, const string& cityName) {
    cout << "| " << left << setw(DRIVER_NAME_WIDTH) << fullName << " | "
        << left << setw(BIRTH_WIDTH) << birthDate << " | "
        << left << setw(NAME_WIDTH) << cityName << " |\n";
}

// Печать разделительной строки для таблицы штрафов
static void printFinesBorder() {
    cout << '+'
        << string(FINE_TYPE_WIDTH + 2, '-') << '+'
        << string(AMOUNT_WIDTH + 2, '-') << '+'
        << string(SEVERITY_WIDTH + 2, '-') << '+'
        << "\n";
}

// Печать заголовка таблицы штрафов
static void printFinesHeader() {
    printFinesBorder();
    cout << "| " << left << setw(FINE_TYPE_WIDTH) << "Тип" << " | "
        << right << setw(AMOUNT_WIDTH) << "Сумма" << " | "
        << left << setw(SEVERITY_WIDTH) << "Уровень" << " |\n";
    printFinesBorder();
}

// Печать строки с данными о штрафе
static void printFineRow(const string& type, double amount, const string& severity) {
    cout << "| " << left << setw(FINE_TYPE_WIDTH) << type << " | "
        << right << setw(AMOUNT_WIDTH) << amount << " | "
        << left << setw(SEVERITY_WIDTH) << severity << " |\n";
}

// Печать разделительной строки для таблицы нарушений
static void printViolationsBorder() {
    cout << '+'
        << string(DRIVER_NAME_WIDTH + 2, '-') << '+'
        << string(NAME_WIDTH + 2, '-') << '+'
        << string(FINE_TYPE_WIDTH + 2, '-') << '+'
        << string(AMOUNT_WIDTH + 2, '-') << '+'
        << string(DATE_WIDTH + 2, '-') << '+'
        << string(PAID_WIDTH + 2, '-') << '+'
        << "\n";
}

// Печать заголовка таблицы нарушений
static void printViolationsHeader() {
    printViolationsBorder();
    cout << "| " << left << setw(DRIVER_NAME_WIDTH) << "Водитель" << " | "
        << left << setw(NAME_WIDTH) << "Город" << " | "
        << left << setw(FINE_TYPE_WIDTH) << "Штраф" << " | "
        << right << setw(AMOUNT_WIDTH) << "Сумма" << " | "
        << left << setw(DATE_WIDTH) << "Дата" << " | "
        << left << setw(PAID_WIDTH) << "Оплачен" << " |\n";
    printViolationsBorder();
}

// Печать строки с данными о нарушении
static void printViolationRow(const string& driverName, const string& cityName,
    const string& fineType, double fineAmount,
    const string& date, bool paid) {
    cout << "| " << left << setw(DRIVER_NAME_WIDTH) << driverName << " | "
        << left << setw(NAME_WIDTH) << cityName << " | "
        << left << setw(FINE_TYPE_WIDTH) << fineType << " | "
        << right << setw(AMOUNT_WIDTH) << fineAmount << " | "
        << left << setw(DATE_WIDTH) << date << " | "
        << left << setw(PAID_WIDTH) << (paid ? "Да" : "Нет") << " |\n";
}

void UserInterface::run() {
    setlocale(LC_ALL, ""); // Для корректного вывода кириллицы
    dbManager.loadAll();
    while (true) {
        mainMenu();
    }
}

void UserInterface::mainMenu() {
    cout << "\n=== Главное меню ===\n";
    cout << "1. Управление городами\n";
    cout << "2. Управление водителями\n";
    cout << "3. Управление штрафами\n";
    cout << "4. Управление нарушениями\n";
    cout << "5. Статистика\n";
    cout << "6. Выход\n";
    int choice = readInt("Выберите пункт: ");
    switch (choice) {
    case 1: citiesMenu();   break;
    case 2: driversMenu();  break;
    case 3: finesMenu();    break;
    case 4: registryMenu(); break;
    case 5: statisticsMenu(); break;
    case 6: dbManager.saveAll(); exit(0);
    default: cout << "Неверный выбор. Попробуйте снова.\n";
    }
}

void UserInterface::citiesMenu() {
    cout << "\n--- Города ---\n";
    cout << "1. Список городов\n";
    cout << "2. Добавить город\n";
    cout << "3. Удалить город\n";
    cout << "4. Фильтрация городов\n";
    cout << "5. Сбросить фильтры\n";
    cout << "6. Назад\n";
    int choice = readInt("Выберите пункт: ");
    switch (choice) {
    case 1: listCities();       break;
    case 2: addCity();          break;
    case 3: deleteCity();       break;
    case 4: filterCities();     break;
    case 5: clearCityFilters(); break;
    case 6: return;
    default: cout << "Неверный выбор.\n";
    }
}

void UserInterface::listCities() {
    printCitiesHeader();
    CityTable& cities = dbManager.getCities();
    CityTable::CityNode* filteredHead = cities.applyFilters();
    cities.cityIteratorReset(filteredHead);
    while (cities.cityIteratorHasNext()) {
        auto ci = cities.cityIteratorNext();
        printCityRow(ci.name, ci.population,
            CityTable::settlementTypeToString(ci.type));
    }
    printCitiesBorder();

    CityTable::CityNode* tmp = filteredHead;
    while (tmp) {
        CityTable::CityNode* next = tmp->next;
        delete tmp;
        tmp = next;
    }
}

void UserInterface::addCity() {
    string name = readString("Название города: ");
    int population = readInt("Население: ");
    cout << "Градация населения (0 - Small, 1 - Medium, 2 - Large): ";
    int gradeInput = readInt("");
    auto grade = static_cast<CityTable::PopulationGrade>(gradeInput);

    cout << "Тип поселения (0 - City, 1 - Town, 2 - Village): ";
    int typeInput = readInt("");
    auto type = static_cast<CityTable::SettlementType>(typeInput);

    dbManager.addCity(name, population, grade, type);
    dbManager.getCities().saveToFile();
    cout << "Город добавлен.\n";
}

void UserInterface::deleteCity() {
    string name = readString("Название города для удаления: ");
    dbManager.deleteCity(name);
    cout << "Город удалён (если существовал).\n";
}

void UserInterface::filterCities() {
    CityTable& cities = dbManager.getCities();
    string field = readString("Введите поле (name, population, type): ");
    string pattern = readString("Введите шаблон (regex для name/type или условие для population, например \">100000\"): ");
    cities.addFilter(field, pattern);
    cout << "Фильтр добавлен.\n";
}

void UserInterface::clearCityFilters() {
    CityTable& cities = dbManager.getCities();
    cities.clearFilters();
    cout << "Все фильтры очищены.\n";
}

void UserInterface::driversMenu() {
    cout << "\n--- Водители ---\n";
    cout << "1. Список водителей\n";
    cout << "2. Добавить водителя\n";
    cout << "3. Удалить водителя\n";
    cout << "4. Назад\n";
    int choice = readInt("Выберите пункт: ");
    switch (choice) {
    case 1: listDrivers(); break;
    case 2: addDriver();   break;
    case 3: deleteDriver(); break;
    case 4: return;
    default: cout << "Неверный выбор.\n";
    }
}

void UserInterface::listDrivers() {
    printDriversHeader();
    auto& drivers = dbManager.getDrivers();
    auto& cities = dbManager.getCities();
    drivers.driverIteratorReset();
    while (drivers.driverIteratorHasNext()) {
        auto di = drivers.driverIteratorNext();
        string cityName = cities.getCityNameById(di.cityId);
        printDriverRow(di.fullName, di.birthDate, cityName);
    }
    printDriversBorder();
}

void UserInterface::addDriver() {
    string fullName = readString("ФИО водителя: ");
    string birthDate = readString("Дата рождения (ДД.MM.ГГГГ): ");
    string cityName = readString("Город регистрации: ");

    int cityId = dbManager.getCities().getCityIdByName(cityName);
    if (cityId == -1) {
        cout << "Город \"" << cityName << "\" не найден. Введите данные для нового города.\n";
        int population = readInt("Население: ");
        cout << "Градация населения (0 - Small, 1 - Medium, 2 - Large): ";
        int gradeInput = readInt("");
        auto grade = static_cast<CityTable::PopulationGrade>(gradeInput);

        cout << "Тип поселения (0 - City, 1 - Town, 2 - Village): ";
        int typeInput = readInt("");
        auto type = static_cast<CityTable::SettlementType>(typeInput);

        dbManager.addCity(cityName, population, grade, type);
        dbManager.getCities().saveToFile();
        cout << "Город \"" << cityName << "\" успешно добавлен.\n";
    }

    try {
        dbManager.addDriver(fullName, birthDate, cityName);
        cout << "Водитель добавлен.\n";
    }
    catch (const exception& e) {
        cout << "Ошибка при добавлении водителя: " << e.what() << "\n";
    }
}

void UserInterface::deleteDriver() {
    string name = readString("ФИО водителя для удаления: ");
    dbManager.deleteDriver(name);
    cout << "Водитель удалён (если существовал).\n";
}

void UserInterface::finesMenu() {
    cout << "\n--- Штрафы ---\n";
    cout << "1. Список штрафов\n";
    cout << "2. Добавить штраф\n";
    cout << "3. Удалить штраф\n";
    cout << "4. Назад\n";
    int choice = readInt("Выберите пункт: ");
    switch (choice) {
    case 1: listFines(); break;
    case 2: addFine();   break;
    case 3: deleteFine(); break;
    case 4: return;
    default: cout << "Неверный выбор.\n";
    }
}

void UserInterface::listFines() {
    printFinesHeader();
    auto& fines = dbManager.getFines();
    fines.fineIteratorReset();
    while (fines.fineIteratorHasNext()) {
        auto fi = fines.fineIteratorNext();
        printFineRow(fi.type, fi.amount, FineTable::severityToString(fi.severity));
    }
    printFinesBorder();
}

void UserInterface::addFine() {
    string type = readString("Тип нарушения: ");
    double amount = readDouble("Сумма: ");
    cout << "Уровень тяжести (0 - Light, 1 - Medium, 2 - Heavy): ";
    int sev = readInt("");
    try {
        dbManager.addFine(type, amount,
            static_cast<FineTable::Severity>(sev));
        cout << "Штраф добавлен.\n";
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << "\n";
    }
}

void UserInterface::deleteFine() {
    string type = readString("Тип штрафа для удаления: ");
    dbManager.getFines().deleteFine(type);
    cout << "Штраф удалён (если существовал).\n";
}

void UserInterface::registryMenu() {
    cout << "\n--- Нарушения ---\n";
    cout << "1. Список нарушений\n";
    cout << "2. Добавить нарушение\n";
    cout << "3. Отметить оплату по ФИО, типу и дате\n";
    cout << "4. Назад\n";
    int choice = readInt("Выберите пункт: ");
    switch (choice) {
    case 1: listViolations(); break;
    case 2: addViolation();   break;
    case 3: markViolationPaid(); break;
    case 4: return;
    default: cout << "Неверный выбор.\n";
    }
}

void UserInterface::listViolations() {
    printViolationsHeader();
    auto violations = dbManager.getAllViolations();
    for (auto& vi : violations) {
        printViolationRow(
            vi.driverName,
            vi.cityName,
            vi.fineType,
            vi.fineAmount,
            vi.date,
            vi.paid
        );
    }
    printViolationsBorder();
}

void UserInterface::addViolation() {
    string driverName = readString("ФИО водителя: ");
    string fineType = readString("Тип штрафа: ");
    string date = readString("Дата (ДД.MM.ГГГГ): ");
    try {
        dbManager.addViolation(driverName, fineType, date);
        cout << "Нарушение добавлено.\n";
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << "\n";
    }
}

void UserInterface::markViolationPaid() {
    string driverName = readString("ФИО водителя: ");
    // Собираем все нарушения с таким ФИО
    auto allViolations = dbManager.getAllViolations();
    vector<FineRegistry::ViolationInfo> matchedByDriver;
    for (auto& vi : allViolations) {
        if (vi.driverName == driverName && !vi.paid) {
            matchedByDriver.push_back(vi);
        }
    }
    if (matchedByDriver.empty()) {
        cout << "Нарушений для водителя \"" << driverName << "\" нет или они уже оплачены.\n";
        return;
    }

    // Если больше одного — уточняем по типу штрафа
    vector<FineRegistry::ViolationInfo> matchedByType;
    if (matchedByDriver.size() > 1) {
        string fineType = readString("У водителя несколько нарушений. Введите тип штрафа: ");
        for (auto& vi : matchedByDriver) {
            if (vi.fineType == fineType) {
                matchedByType.push_back(vi);
            }
        }
        if (matchedByType.empty()) {
            cout << "Нарушений с таким типом не найдено.\n";
            return;
        }
    }
    else {
        matchedByType = matchedByDriver;
    }

    // Если всё ещё больше одного — уточняем по дате
    vector<FineRegistry::ViolationInfo> matchedByDate;
    if (matchedByType.size() > 1) {
        string date = readString("Нарушений несколько одного типа. Введите дату (ДД.MM.ГГГГ): ");
        for (auto& vi : matchedByType) {
            if (vi.date == date) {
                matchedByDate.push_back(vi);
            }
        }
        if (matchedByDate.empty()) {
            cout << "Нарушений с такой датой не найдено.\n";
            return;
        }
    }
    else {
        matchedByDate = matchedByType;
    }

    // Если всё ещё больше одного — уточняем по городу
    vector<FineRegistry::ViolationInfo> matchedByCity;
    if (matchedByDate.size() > 1) {
        string city = readString("Пользователь имеет несколько нарушений в одну дату. Введите город: ");
        for (auto& vi : matchedByDate) {
            if (vi.cityName == city) {
                matchedByCity.push_back(vi);
            }
        }
        if (matchedByCity.empty()) {
            cout << "Нарушений в этом городе не найдено.\n";
            return;
        }
    }
    else {
        matchedByCity = matchedByDate;
    }

    // Теперь точно один элемент matchedByCity[0]
    int recordId = matchedByCity[0].recordId;
    dbManager.markFineAsPaid(recordId);
    dbManager.saveAll();
    cout << "Нарушение отмечено как оплаченное.\n";
}

void UserInterface::statisticsMenu() {
    cout << "\n--- Статистика ---\n";
    cout << "1. Нарушения по городам\n";
    cout << "2. Топ-5 водителей\n";
    cout << "3. Назад\n";
    int choice = readInt("Выберите пункт: ");
    switch (choice) {
    case 1: showViolationsByCity(); break;
    case 2: showTopDrivers();       break;
    case 3: return;
    default: cout << "Неверный выбор.\n";
    }
}

void UserInterface::showViolationsByCity() {
    cout << "\nНарушения по городам:\n";
    listViolations();
}

void UserInterface::showTopDrivers() {
    cout << "\nТоп-5 водителей по количеству нарушений:\n";
    auto violations = dbManager.getAllViolations();
    map<std::string, int> countMap;
    for (auto& v : violations) {
        countMap[v.driverName]++;
    }
    vector<std::pair<std::string, int>> vec(countMap.begin(), countMap.end());
    sort(vec.begin(), vec.end(), [](auto& a, auto& b) { return a.second > b.second; });
    for (size_t i = 0; i < vec.size() && i < 5; ++i) {
        cout << vec[i].first << ": " << vec[i].second << "\n";
    }
}

int UserInterface::readInt(const std::string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        cout << "Неверный ввод. Пожалуйста, введите число.\n";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }
}

double UserInterface::readDouble(const std::string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        cout << "Неверный ввод. Пожалуйста, введите число.\n";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string UserInterface::readString(const std::string& prompt) {
    std::string value;
    cout << prompt;
    std::getline(cin, value);
    return value;
}
