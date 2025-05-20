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


#include <iostream>

#include "UserInterface.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <regex>
#include <Windows.h>

using namespace std;

// ==================== ВАЛИДАЦИЯ ДАННЫХ ====================
bool UserInterface::validateDate(const string& date) {
    regex pattern(R"(^(0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.\d{4}$)");
    return regex_match(date, pattern);
}

bool UserInterface::validateName(const string& name) const {
    return all_of(name.begin(), name.end(), [](char c) {
        return isalpha(c) || c == ' ' || c == '-';
        });
}

tm UserInterface::parseDate(const string& dateStr) {
    tm date = {};
    istringstream ss(dateStr);
    ss >> get_time(&date, "%d.%m.%Y");
    return date;
}

// ==================== ФОРМАТИРОВАНИЕ ТАБЛИЦ ====================
vector<vector<string>> UserInterface::prepareViolationData() {
    vector<vector<string>> data;
    db.getRegistry().violationIteratorReset();
    while (db.getRegistry().violationIteratorHasNext()) {
        auto violation = db.getRegistry().violationIteratorNext(
            db.getDrivers(),
            db.getCities(),
            db.getFines()
        );
        data.push_back({
            violation.driverName,
            violation.cityName,
            violation.fineType,
            violation.date,
            to_string(violation.amount) + " USD",
            violation.paid ? "Paid" : "Unpaid"
            });
    }
    return data;
}

void UserInterface::printDynamicTable(
    const vector<string>& headers,
    const vector<vector<string>>& data
) {
    vector<int> widths(headers.size(), 0);

    // Расчет ширины колонок
    for (size_t i = 0; i < headers.size(); ++i) {
        widths[i] = headers[i].length();
        for (const auto& row : data) {
            if (i < row.size() && row[i].length() > widths[i]) {
                widths[i] = row[i].length();
            }
        }
        widths[i] += 2; // Добавляем отступ
    }

    // Вывод шапки
    cout << "\n";
    for (size_t i = 0; i < headers.size(); ++i) {
        cout << "| " << left << setw(widths[i]) << headers[i] << " ";
    }
    cout << "|\n" << string(accumulate(widths.begin(), widths.end(), 0) + headers.size() * 3, '-') << "\n";

    // Вывод данных
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            cout << "| " << left << setw(widths[i]) << row[i] << " ";
        }
        cout << "|\n";
    }
}

// ==================== ОСНОВНЫЕ МЕТОДЫ ====================
void UserInterface::run() {
    SetConsoleOutputCP(CP_UTF8);
    db.loadAll();
    showMainMenu();
    db.saveAll();
}

void UserInterface::showMainMenu() {
    int choice;
    do {
        cout << "\n========== MAIN MENU ==========\n"
            << "1. Cities Management\n"
            << "2. Drivers Management\n"
            << "3. Fines Management\n"
            << "4. Violations Management\n"
            << "5. Statistics\n"
            << "6. Exit\n"
            << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            continue;
        }

        switch (choice) {
        case 1: showCityMenu(); break;
        case 2: showDriverMenu(); break;
        case 3: showFineMenu(); break;
        case 4: showViolationMenu(); break;
        case 5: showStatisticsMenu(); break;
        case 6: cout << "Saving data...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);
}

// ==================== МЕНЮ НАРУШЕНИЙ ====================
void UserInterface::showViolationMenu() {
    int choice;
    do {
        cout << "\n========== VIOLATIONS MANAGEMENT ==========\n"
            << "1. Show All Violations\n"
            << "2. Add Violation\n"
            << "3. Mark as Paid\n"
            << "4. Apply Filters\n"
            << "5. Clear Filters\n"
            << "6. Back\n"
            << "Enter choice: ";

        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            auto data = prepareViolationData();
            printDynamicTable(
                { "Driver", "City", "Fine Type", "Date", "Amount", "Status" },
                data
            );
            break;
        }
        case 4:
            handleFilterMenu();
            break;
        case 5:
            db.getRegistry().clearFilters();
            cout << "Filters cleared!\n";
            break;
            // Обработка других кейсов...
        }
    } while (choice != 6);
}

// ==================== ФИЛЬТРАЦИЯ ====================
void UserInterface::handleFilterMenu() {
    int choice;
    do {
        cout << "\n=== FILTER CRITERIA ===\n"
            << "1. By Driver Name\n"
            << "2. By City\n"
            << "3. By Fine Type\n"
            << "4. By Date\n"
            << "5. By Amount\n"
            << "6. By Payment Status\n"
            << "7. Apply Filters\n"
            << "8. Back\n"
            << "Enter choice: ";

        cin >> choice;
        cin.ignore();

        string pattern;
        auto& registry = db.getRegistry();

        switch (choice) {
        case 1: {
            cout << "Enter driver name pattern (use * and ?): ";
            getline(cin, pattern);
            registry.addFilter("driver", pattern);
            break;
        }
        case 5: {
            cout << "Enter amount condition (>500, <1000, 200-500): ";
            getline(cin, pattern);
            registry.addFilter("amount", pattern);
            break;
        }
        case 7: {
            cout << "Applying filters...\n";
            break;
        }
        }
    } while (choice != 8);
}

// ==================== МЕНЮ ГОРОДОВ ====================
void UserInterface::showCityMenu() {
    int choice;
    do {
        cout << "\n========== CITIES MANAGEMENT ==========\n"
            << "1. List Cities\n"
            << "2. Add City\n"
            << "3. Delete City\n"
            << "4. Back\n"
            << "Enter choice: ";

        cin >> choice;
        cin.ignore();

        auto& cities = db.getCities();
        vector<vector<string>> cityData;

        switch (choice) {
        case 1: {
            cities.cityIteratorReset();
            while (cities.cityIteratorHasNext()) {
                auto city = cities.cityIteratorNext();
                cityData.push_back({
                    city.name,
                    to_string(city.population) + " people",
                    CityTable::settlementTypeToString(city.type),
                    CityTable::populationGradeToString(city.grade)
                    });
            }
            printDynamicTable(
                { "Name", "Population", "Type", "Grade" },
                cityData
            );
            break;
        }
        case 2: {
            string name;
            int population;
            int typeChoice, gradeChoice;

            do {
                cout << "Enter city name: ";
                getline(cin, name);
            } while (!validateName(name));

            cout << "Enter population: ";
            while (!(cin >> population) || population < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Enter positive number: ";
            }

            cout << "Select settlement type:\n"
                << "1. City\n2. Town\n3. Village\nChoice: ";
            cin >> typeChoice;
            auto type = static_cast<CityTable::SettlementType>(typeChoice - 1);

            cout << "Select population grade:\n"
                << "1. Small\n2. Medium\n3. Large\nChoice: ";
            cin >> gradeChoice;
            auto grade = static_cast<CityTable::PopulationGrade>(gradeChoice - 1);

            try {
                db.addCity(name, population, grade, type);
                cout << "City added successfully!\n";
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            string name;
            cout << "Enter city name to delete: ";
            getline(cin, name);
            try {
                db.deleteCity(name);
                cout << "City deleted!\n";
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
            break;
        }
        }
    } while (choice != 4);
}

// ==================== МЕНЮ ВОДИТЕЛЕЙ ====================
void UserInterface::showDriverMenu() {
    int choice;
    do {
        cout << "\n========== DRIVERS MANAGEMENT ==========\n"
            << "1. List Drivers\n"
            << "2. Add Driver\n"
            << "3. Delete Driver\n"
            << "4. Back\n"
            << "Enter choice: ";

        cin >> choice;
        cin.ignore();

        auto& drivers = db.getDrivers();
        vector<vector<string>> driverData;

        switch (choice) {
        case 1: {
            drivers.driverIteratorReset();
            while (drivers.driverIteratorHasNext()) {
                auto driver = drivers.driverIteratorNext();
                driverData.push_back({
                    driver.fullName,
                    driver.birthDate,
                    db.getCities().getCityNameById(driver.cityId)
                    });
            }
            printDynamicTable(
                { "Name", "Birth Date", "City" },
                driverData
            );
            break;
        }
        case 2: {
            string name, birthDate, cityName;

            do {
                cout << "Enter driver's full name: ";
                getline(cin, name);
            } while (!validateName(name));

            do {
                cout << "Enter birth date (DD.MM.YYYY): ";
                getline(cin, birthDate);
            } while (!validateDate(birthDate));

            cout << "Available cities:\n";
            db.getCities().cityIteratorReset();
            while (db.getCities().cityIteratorHasNext()) {
                auto city = db.getCities().cityIteratorNext();
                cout << " - " << city.name << "\n";
            }

            cout << "Enter city name: ";
            getline(cin, cityName);

            try {
                db.addDriver(name, birthDate, cityName);
                cout << "Driver added!\n";
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            string name;
            cout << "Enter driver's name to delete: ";
            getline(cin, name);
            try {
                db.deleteDriver(name);
                cout << "Driver deleted!\n";
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
            break;
        }
        }
    } while (choice != 4);
}

// ==================== МЕНЮ ШТРАФОВ ====================
void UserInterface::showFineMenu() {
    int choice;
    do {
        cout << "\n========== FINES MANAGEMENT ==========\n"
            << "1. List Fines\n"
            << "2. Add Fine\n"
            << "3. Delete Fine\n"
            << "4. Back\n"
            << "Enter choice: ";

        cin >> choice;
        cin.ignore();

        auto& fines = db.getFines();
        vector<vector<string>> fineData;

        switch (choice) {
        case 1: {
            fines.fineIteratorReset();
            while (fines.fineIteratorHasNext()) {
                auto fine = fines.fineIteratorNext();
                fineData.push_back({
                    fine.type,
                    to_string(fine.amount) + " USD",
                    FineTable::severityToString(fine.severity)
                    });
            }
            printDynamicTable(
                { "Type", "Amount", "Severity" },
                fineData
            );
            break;
        }
        case 2: {
            string type;
            double amount;
            int severity;

            cout << "Enter fine type: ";
            getline(cin, type);

            cout << "Enter amount: ";
            while (!(cin >> amount) || amount < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Enter positive number: ";
            }

            cout << "Select severity:\n"
                << "1. Light\n2. Medium\n3. Heavy\nChoice: ";
            cin >> severity;

            try {
                db.addFine(type, amount, static_cast<FineTable::Severity>(severity - 1));
                cout << "Fine added!\n";
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
            break;
        }
        }
    } while (choice != 4);
}

// ==================== МЕНЮ СТАТИСТИКИ ====================
void UserInterface::showStatisticsMenu() {
    int choice;
    do {
        cout << "\n========== STATISTICS ==========\n"
            << "1. Violations by City\n"
            << "2. Top Violators\n"
            << "3. Back\n"
            << "Enter choice: ";

        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            map<string, int> cityStats;
            db.getCities().cityIteratorReset();
            while (db.getCities().cityIteratorHasNext()) {
                auto city = db.getCities().cityIteratorNext();
                cityStats[city.name] = 0;
            }

            db.getRegistry().violationIteratorReset();
            while (db.getRegistry().violationIteratorHasNext()) {
                auto violation = db.getRegistry().violationIteratorNext(
                    db.getDrivers(),
                    db.getCities(),
                    db.getFines()
                );
                cityStats[violation.cityName]++;
            }

            vector<vector<string>> statsData;
            for (const auto& [city, count] : cityStats) {
                statsData.push_back({ city, to_string(count) });
            }
            printDynamicTable({ "City", "Violations" }, statsData);
            break;
        }
        case 2: {
            map<string, int> driverStats;
            db.getDrivers().driverIteratorReset();
            while (db.getDrivers().driverIteratorHasNext()) {
                auto driver = db.getDrivers().driverIteratorNext();
                driverStats[driver.fullName] = 0;
            }

            db.getRegistry().violationIteratorReset();
            while (db.getRegistry().violationIteratorHasNext()) {
                auto violation = db.getRegistry().violationIteratorNext(
                    db.getDrivers(),
                    db.getCities(),
                    db.getFines()
                );
                driverStats[violation.driverName]++;
            }

            vector<pair<string, int>> sorted(driverStats.begin(), driverStats.end());
            sort(sorted.begin(), sorted.end(),
                [](auto& a, auto& b) { return a.second > b.second; });

            vector<vector<string>> topData;
            for (size_t i = 0; i < min(5, (int)sorted.size()); ++i) {
                topData.push_back({
                    to_string(i + 1),
                    sorted[i].first,
                    to_string(sorted[i].second)
                    });
            }
            printDynamicTable({ "Rank", "Driver", "Violations" }, topData);
            break;
        }
        }
    } while (choice != 3);
}

// ==================== ОБРАБОТКА ОШИБОК ====================
void UserInterface::handleError(const exception& e) {
    cerr << "\nError: " << e.what() << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ==================== ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ ====================
void UserInterface::displayHelp() {
    cout << "\nHelp:\n"
        << " - Use '*' for any characters sequence\n"
        << " - Use '?' for any single character\n"
        << " - Date format: DD.MM.YYYY\n"
        << " - Amount examples: >500, <1000, 200-500\n";
}

// ==================== ЗАВЕРШЕНИЕ РАБОТЫ ====================
void UserInterface::cleanup() {
    db.saveAll();
    cout << "\nAll data saved successfully!\n";
}