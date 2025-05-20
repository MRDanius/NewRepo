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
//        cout << "\n========== ������� ���� ==========\n"
//            << "1. ���������� ��������\n"
//            << "2. ���������� ����������\n"
//            << "3. ���������� ��������\n"
//            << "4. ���������� �����������\n"
//            << "5. ����������\n"
//            << "6. �����\n"
//            << "�������� �����: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: showCityMenu(); break;
//        case 2: showDriverMenu(); break;
//        case 3: showFineMenu(); break;
//        case 4: showViolationMenu(); break;
//        case 5: showStatisticsMenu(); break;
//        case 6: cout << "���������� ������...\n"; break;
//        default:
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            cout << "�������� ����!\n";
//        }
//    } while (choice != 6);
//}
//
//void UserInterface::showCityMenu() {
//    int choice;
//    do {
//        cout << "\n========== ���������� �������� ==========\n"
//            << "1. ������ �������\n"
//            << "2. �������� �����\n"
//            << "3. ������� �����\n"
//            << "4. �����\n"
//            << "�������� �����: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            cout << "\n������ �������:\n";
//            db.getCities().cityIteratorReset();
//            string cityName;
//            while (db.getCities().cityIteratorHasNext()) {
//                cityName = db.getCities().cityIteratorNext();
//                cout << "� " << cityName << endl;
//            }
//            break;
//        }
//        case 2: {
//            string name;
//            cout << "������� �������� ������: ";
//            cin.ignore();
//            getline(cin, name);
//            db.addCity(name);
//            cout << "����� ��������!\n";
//            break;
//        }
//        case 3: {
//            string name;
//            cout << "������� �������� ������: ";
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
//        cout << "\n========== ���������� ���������� ==========\n"
//            << "1. ������ ���������\n"
//            << "2. �������� ��������\n"
//            << "3. ������� ��������\n"
//            << "4. �����\n"
//            << "�������� �����: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            DriverTable::DriverInfo info;
//            db.getDrivers().driverIteratorReset();
//            cout << "\n������ ���������:\n";
//            while (db.getDrivers().driverIteratorHasNext()) {
//                info = db.getDrivers().driverIteratorNext(db.getCities());
//                cout << "���: " << info.fullName << "\n"
//                    << "���� ��������: " << info.birthDate << "\n"
//                    << "�����: " << info.cityName << "\n\n";
//            }
//            break;
//        }
//        case 2: {
//            string name, birthDate, cityName;
//            do {
//                cout << "������� ���: ";
//                cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                getline(cin, name);
//            } while (!validateName(name));
//
//            do {
//                cout << "������� ���� �������� (��.��.����): ";
//                getline(cin, birthDate);
//            } while (!validateDate(birthDate));
//
//            cout << "��������� ������:\n";
//            db.getCities().cityIteratorReset();
//            string city;
//            while (db.getCities().cityIteratorHasNext()) {
//                city = db.getCities().cityIteratorNext();
//                cout << "� " << city << endl;
//            }
//            cout << "������� �������� ������: ";
//            getline(cin, cityName);
//
//            try {
//                db.addDriver(name, birthDate, cityName);
//                cout << "�������� ��������!\n";
//            }
//            catch (const exception& e) {
//                cout << "������: " << e.what() << endl;
//            }
//            break;
//        }
//        case 3: {
//            string name;
//            cout << "������� ��� ��������: ";
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
//        cout << "\n========== ���������� �������� ==========\n"
//            << "1. ������ �������\n"
//            << "2. �������� �����\n"
//            << "3. ������� �����\n"
//            << "4. �����\n"
//            << "�������� �����: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            FineTable::FineInfo info;
//            db.getFines().fineIteratorReset();
//            cout << "\n������ �������:\n";
//            while (db.getFines().fineIteratorHasNext()) {
//                info = db.getFines().fineIteratorNext();
//                cout << "���: " << left << setw(25) << info.type
//                    << "�����: " << info.amount << " ���.\n";
//            }
//            break;
//        }
//        case 2: {
//            string type;
//            double amount;
//            cout << "������� ��� ���������: ";
//            cin.ignore();
//            getline(cin, type);
//            cout << "������� ����� ������: ";
//            cin >> amount;
//            db.addFine(type, amount);
//            cout << "����� ��������!\n";
//            break;
//        }
//        case 3: {
//            string type;
//            cout << "������� ��� ������ ��� ��������: ";
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
//        cout << "\n========== ���������� ����������� ==========\n"
//            << "1. ��� ���������\n"
//            << "2. �������� ���������\n"
//            << "3. �������� ��� ����������\n"
//            << "4. �����\n"
//            << "�������� �����: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            FineRegistry::ViolationInfo info;
//            db.getRegistry().violationIteratorReset();
//            cout << "\n������ ���������:\n";
//            while (db.getRegistry().violationIteratorHasNext()) {
//                info = db.getRegistry().violationIteratorNext(
//                    db.getDrivers(), db.getCities(), db.getFines()
//                );
//                cout << "ID: " << info.recordId << "\n"
//                    << "��������: " << info.driverName << "\n"
//                    << "�����: " << info.cityName << "\n"
//                    << "���: " << info.fineType << "\n"
//                    << "����: " << info.date << "\n"
//                    << "������: " << (info.paid ? "�������" : "�� �������")
//                    << "\n\n";
//            }
//            break;
//        }
//        case 2: {
//            string driverName, fineType, date;
//
//            cout << "\n������ ���������:\n";
//            DriverTable::DriverInfo driverInfo;
//            db.getDrivers().driverIteratorReset();
//            while (db.getDrivers().driverIteratorHasNext()) {
//                driverInfo = db.getDrivers().driverIteratorNext(db.getCities());
//                cout << "� " << driverInfo.fullName << endl;
//            }
//            cout << "������� ��� ��������: ";
//            cin.ignore();
//            getline(cin, driverName);
//
//            cout << "\n������ �������:\n";
//            FineTable::FineInfo fineInfo;
//            db.getFines().fineIteratorReset();
//            while (db.getFines().fineIteratorHasNext()) {
//                fineInfo = db.getFines().fineIteratorNext();
//                cout << "� " << fineInfo.type << " (" << fineInfo.amount << " ���.)\n";
//            }
//            cout << "������� ��� ������: ";
//            getline(cin, fineType);
//
//            do {
//                cout << "������� ���� ��������� (��.��.����): ";
//                getline(cin, date);
//            } while (!validateDate(date));
//
//            try {
//                db.addViolation(driverName, fineType, date);
//                cout << "��������� ���������!\n";
//            }
//            catch (const exception& e) {
//                cout << "������: " << e.what() << endl;
//            }
//            break;
//        }
//        case 3: {
//            int recordId;
//            cout << "������� ID ���������: ";
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
//        cout << "\n========== ���������� ==========\n"
//            << "1. ��������� �� �������\n"
//            << "2. ��� �����������\n"
//            << "3. �����\n"
//            << "�������� �����: ";
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
//            cout << "\n���������� ��������� �� �������:\n";
//            for (const auto& entry : cityViolations) {
//                cout << "� " << entry.first << ": " << entry.second << endl;
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
//            cout << "\n���-5 �����������:\n";
//            for (size_t i = 0; i < min(5, (int)sortedViolations.size()); i++) {
//                cout << i + 1 << ". " << sortedViolations[i].first
//                    << " (" << sortedViolations[i].second << " ���������)\n";
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
//        cout << "\n========== ������� ���� ==========\n"
//            << "1. ���������� ��������\n"
//            << "2. ���������� ����������\n"
//            << "3. ���������� ��������\n"
//            << "4. ���������� �����������\n"
//            << "5. ����������\n"
//            << "6. �����\n"
//            << "�������� �����: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: showCityMenu(); break;
//        case 2: showDriverMenu(); break;
//        case 3: showFineMenu(); break;
//        case 4: showViolationMenu(); break;
//        case 5: showStatisticsMenu(); break;
//        case 6: cout << "���������� ������...\n"; break;
//        default:
//            cin.clear();
//            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//            cout << "�������� ����!\n";
//        }
//    } while (choice != 6);
//}
//
//void UserInterface::showCityMenu() {
//    int choice;
//    do {
//        cout << "\n========== ���������� �������� ==========\n"
//            << "1. ������ �������\n"
//            << "2. �������� �����\n"
//            << "3. ������� �����\n"
//            << "4. �����\n"
//            << "�������� �����: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            vector<string> headers = { "��������", "���������", "���", "��������" };
//            printTableHeader(headers);
//
//            db.getCities().cityIteratorReset();
//            while (db.getCities().cityIteratorHasNext()) {
//                auto city = db.getCities().cityIteratorNext();
//                vector<string> cells = {
//                    city.name,
//                    to_string(city.population) + " ���.",
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
//            cout << "������� �������� ������: ";
//            cin.ignore();
//            getline(cin, name);
//
//            cout << "������� ���������: ";
//            cin >> population;
//
//            cout << "�������� �������� (1-�����, 2-�������, 3-�������): ";
//            cin >> gradeChoice;
//
//            cout << "�������� ��� (1-�����, 2-������, 3-�������): ";
//            cin >> typeChoice;
//
//            try {
//                db.addCity(name,
//                    population,
//                    static_cast<CityTable::PopulationGrade>(gradeChoice - 1),
//                    static_cast<CityTable::SettlementType>(typeChoice - 1));
//                cout << "����� ��������!\n";
//            }
//            catch (const exception& e) {
//                cout << "������: " << e.what() << endl;
//            }
//            break;
//        }
//        case 3: {
//            string name;
//            cout << "������� �������� ������: ";
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
//        cout << "\n========== ���������� ���������� ==========\n"
//            << "1. ������ ���������\n"
//            << "2. �������� ��������\n"
//            << "3. ������� ��������\n"
//            << "4. �����\n"
//            << "�������� �����: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            vector<string> headers = { "���", "���� ��������", "����� ����������" };
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
//                cout << "������� ���: ";
//                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//                getline(cin, name);
//                valid = validateName(name);
//                if (!valid) cout << "������������ ���!\n";
//            } while (!valid);
//
//            do {
//                cout << "������� ���� �������� (��.��.����): ";
//                getline(cin, birthDate);
//                valid = validateDate(birthDate);
//                if (!valid) cout << "������������ ����!\n";
//            } while (!valid);
//
//            cout << "��������� ������:\n";
//            db.getCities().cityIteratorReset();
//            while (db.getCities().cityIteratorHasNext()) {
//                auto city = db.getCities().cityIteratorNext();
//                cout << "� " << city.name << endl;
//            }
//            cout << "������� �������� ������: ";
//            getline(cin, cityName);
//
//            try {
//                db.addDriver(name, birthDate, cityName);
//                cout << "�������� ��������!\n";
//            }
//            catch (const exception& e) {
//                cout << "������: " << e.what() << endl;
//            }
//            break;
//        }
//        case 3: {
//            string name;
//            cout << "������� ��� ��������: ";
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
//        cout << "\n========== ���������� �������� ==========\n"
//            << "1. ������ �������\n"
//            << "2. �������� �����\n"
//            << "3. ������� �����\n"
//            << "4. �����\n"
//            << "�������� �����: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            vector<string> headers = { "��� ���������", "�����", "�������" };
//            printTableHeader(headers);
//
//            db.getFines().fineIteratorReset();
//            while (db.getFines().fineIteratorHasNext()) {
//                auto fine = db.getFines().fineIteratorNext();
//                vector<string> cells = {
//                    fine.type,
//                    to_string(fine.amount) + " ���.",
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
//            cout << "������� ��� ���������: ";
//            cin.ignore();
//            getline(cin, type);
//
//            cout << "������� ����� ������: ";
//            cin >> amount;
//
//            cout << "�������� ������� (1-������, 2-�������, 3-�������): ";
//            cin >> severity;
//
//            try {
//                db.addFine(type, amount, static_cast<FineTable::Severity>(severity - 1));
//                cout << "����� ��������!\n";
//            }
//            catch (const exception& e) {
//                cout << "������: " << e.what() << endl;
//            }
//            break;
//        }
//        case 3: {
//            string type;
//            cout << "������� ��� ������: ";
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
//        cout << "\n========== ���������� ����������� ==========\n"
//            << "1. ��� ���������\n"
//            << "2. �������� ���������\n"
//            << "3. �������� ��� ����������\n"
//            << "4. �����\n"
//            << "�������� �����: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            vector<string> headers = { "��������", "�����", "�����", "����", "�����", "������" };
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
//                    to_string(violation.amount) + " ���.",
//                    violation.paid ? "��������" : "�� ��������"
//                };
//                printTableRow(cells, 25);
//            }
//            break;
//        }
//        case 2: {
//            string driverName, fineType, date;
//
//            cout << "\n������ ���������:\n";
//            db.getDrivers().driverIteratorReset();
//            while (db.getDrivers().driverIteratorHasNext()) {
//                auto driver = db.getDrivers().driverIteratorNext();
//                cout << "� " << driver.fullName << endl;
//            }
//            cout << "������� ��� ��������: ";
//            cin.ignore();
//            getline(cin, driverName);
//
//            cout << "\n������ �������:\n";
//            db.getFines().fineIteratorReset();
//            while (db.getFines().fineIteratorHasNext()) {
//                auto fine = db.getFines().fineIteratorNext();
//                cout << "� " << fine.type << " (" << fine.amount << " ���.)\n";
//            }
//            cout << "������� ��� ������: ";
//            getline(cin, fineType);
//
//            do {
//                cout << "������� ���� ��������� (��.��.����): ";
//                getline(cin, date);
//            } while (!validateDate(date));
//
//            try {
//                db.addViolation(driverName, fineType, date);
//                cout << "��������� ���������!\n";
//            }
//            catch (const exception& e) {
//                cout << "������: " << e.what() << endl;
//            }
//            break;
//        }
//        case 3: {
//            int recordId;
//            cout << "������� ID ���������: ";
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
//        cout << "\n========== ���������� ==========\n"
//            << "1. ��������� �� �������\n"
//            << "2. ��� �����������\n"
//            << "3. �����\n"
//            << "�������� �����: ";
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
//            vector<string> headers = { "�����", "���������� ���������" };
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
//            vector<string> headers = { "�����", "��������", "���������" };
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
//// ==================== ��������������� ������ ====================
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
//// ==================== �������������� ������ ====================
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
//            to_string(violation.amount) + " ���.",
//            violation.paid ? "��������" : "�� ��������"
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
//    // ����� �������
//    cout << "\n";
//    for (size_t i = 0; i < headers.size(); ++i) {
//        cout << "| " << left << setw(widths[i]) << headers[i] << " ";
//    }
//    cout << "|\n" << string(accumulate(widths.begin(), widths.end(), 0) + headers.size() * 3, '-') << "\n";
//
//    // ������
//    for (const auto& row : data) {
//        for (size_t i = 0; i < row.size(); ++i) {
//            cout << "| " << left << setw(widths[i]) << row[i] << " ";
//        }
//        cout << "|\n";
//    }
//}
//
//// ==================== ���������� ====================
//
//bool UserInterface::matchesFilters(const FineRegistry::ViolationInfo& violation) {
//    for (const auto& filter : active_filters) {
//        if (filter.field == "city" && violation.cityName != filter.value)
//            return false;
//
//        if (filter.field == "����") {
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
//        if (filter.field == "�����") {
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
//                to_string(violation.amount) + " ���.",
//                violation.paid ? "��������" : "�� ��������"
//                });
//        }
//    }
//
//    printDynamicTable({ "��������", "�����", "�����", "����", "�����", "������" }, filteredData);
//}
//
//void UserInterface::filterMenu() {
//    int choice;
//    do {
//        cout << "\n=== ���������� ��������� ==="
//            << "\n1. �������� ������"
//            << "\n2. �������� �������"
//            << "\n3. �����"
//            << "\n��������: ";
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
//            cout << "�������� �����!\n";
//        }
//    } while (true);
//}
//
//void UserInterface::addFilterCondition() {
//    FilterCondition cond;
//
//    cout << "\n��������� ����: �����, ����, �����, �����, ������: ";
//    getline(cin, cond.field);
//
//    if (cond.field != "city" && cond.field != "data" &&
//        cond.field != "fine" && cond.field != "sum" && cond.field != "state") {
//        cout << "������������ ����!\n";
//        return;
//    }
//
//    cout << "��� ������� (1-������ ��������, 2-��������): ";
//    int type;
//    cin >> type;
//    cin.ignore();
//
//    if (type == 2 && (cond.field == "����" || cond.field == "�����")) {
//        cond.is_range = true;
//        cout << "������ ���������: ";
//        getline(cin, cond.range_from);
//        cout << "����� ���������: ";
//        getline(cin, cond.range_to);
//    }
//    else if (type == 1) {
//        cout << "��������: ";
//        getline(cin, cond.value);
//    }
//    else {
//        cout << "������������ ��� �������!\n";
//        return;
//    }
//
//    active_filters.push_back(cond);
//    applyFilters();
//
//    cout << "�������� ��� �������? (1-��/0-���): ";
//    cin >> type;
//    if (type == 1)
//        addFilterCondition();
//}
//
//void UserInterface::resetFilters() {
//    active_filters.clear();
//    cout << "������� ��������!\n";
//}
//
//// ==================== �������� ���� ====================
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
//        cout << "\n========== ������� ���� ==========\n"
//            << "1. ���������� ��������\n"
//            << "2. ���������� ����������\n"
//            << "3. ���������� ��������\n"
//            << "4. ���������� �����������\n"
//            << "5. ����������\n"
//            << "6. �����\n"
//            << "�������� �����: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: showCityMenu(); break;
//        case 2: showDriverMenu(); break;
//        case 3: showFineMenu(); break;
//        case 4: showViolationMenu(); break;
//        case 5: showStatisticsMenu(); break;
//        case 6: cout << "���������� ������...\n"; break;
//        default:
//            cin.clear();
//            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//            cout << "�������� ����!\n";
//        }
//    } while (choice != 6);
//}
//
//// ----------- ���������� �������� -----------
//void UserInterface::showCityMenu() {
//    int choice;
//    do {
//        cout << "\n========== ���������� �������� ==========\n"
//            << "1. ������ �������\n"
//            << "2. �������� �����\n"
//            << "3. ������� �����\n"
//            << "4. �����\n"
//            << "�������� �����: ";
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
//                    to_string(city.population) + " ���.",
//                    CityTable::settlementTypeToString(city.type),
//                    CityTable::populationGradeToString(city.grade)
//                    });
//            }
//            printDynamicTable({ "��������", "���������", "���", "��������" }, cityData);
//            break;
//        }
//        case 2: {
//            string name;
//            int population, gradeChoice, typeChoice;
//
//            cout << "������� �������� ������: ";
//            cin.ignore();
//            getline(cin, name);
//
//            cout << "������� ���������: ";
//            while (!(cin >> population) || population < 0) {
//                cin.clear();
//                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//                cout << "������! ������� ������������� �����: ";
//            }
//
//            cout << "�������� ��������� (1-�����, 2-�������, 3-�������): ";
//            while (!(cin >> gradeChoice) || gradeChoice < 1 || gradeChoice > 3) {
//                cin.clear();
//                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//                cout << "������! ������� 1-3: ";
//            }
//
//            cout << "��� ��������� (1-�����, 2-������, 3-�������): ";
//            while (!(cin >> typeChoice) || typeChoice < 1 || typeChoice > 3) {
//                cin.clear();
//                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//                cout << "������! ������� 1-3: ";
//            }
//
//            try {
//                db.addCity(
//                    name,
//                    population,
//                    static_cast<CityTable::PopulationGrade>(gradeChoice - 1),
//                    static_cast<CityTable::SettlementType>(typeChoice - 1)
//                );
//                cout << "����� ��������!\n";
//            }
//            catch (const exception& e) {
//                cout << "������: " << e.what() << endl;
//            }
//            break;
//        }
//        case 3: {
//            string name;
//            cout << "������� �������� ������: ";
//            cin.ignore();
//            getline(cin, name);
//            try {
//                db.deleteCity(name);
//                cout << "����� ������!\n";
//            }
//            catch (const exception& e) {
//                cout << "������: " << e.what() << endl;
//            }
//            break;
//        }
//        case 4: return;
//        default:
//            cin.clear();
//            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//            cout << "�������� �����!\n";
//        }
//    } while (true);
//}
//
//// ----------- ���������� ���������� -----------
//void UserInterface::showDriverMenu() {
//    int choice;
//    do {
//        cout << "\n========== ���������� ���������� ==========\n"
//            << "1. ������ ���������\n"
//            << "2. �������� ��������\n"
//            << "3. ������� ��������\n"
//            << "4. �����\n"
//            << "�������� �����: ";
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
//            printDynamicTable({ "���", "���� ��������", "�����" }, driverData);
//            break;
//        }
//        case 2: {
//            string name, birthDate, cityName;
//            bool isValid = false;
//
//            do {
//                cout << "������� ���: ";
//                cin.ignore();
//                getline(cin, name);
//                isValid = validateName(name);
//                if (!isValid) cout << "������������ ���! ������ �����, ������� � ������.\n";
//            } while (!isValid);
//
//            do {
//                cout << "������� ���� �������� (��.��.����): ";
//                getline(cin, birthDate);
//                isValid = validateDate(birthDate);
//                if (!isValid) cout << "������������ ������ ����!\n";
//            } while (!isValid);
//
//            cout << "��������� ������:\n";
//            db.getCities().cityIteratorReset();
//            while (db.getCities().cityIteratorHasNext()) {
//                auto city = db.getCities().cityIteratorNext();
//                cout << "� " << city.name << endl;
//            }
//
//            cout << "������� �������� ������: ";
//            getline(cin, cityName);
//
//            try {
//                db.addDriver(name, birthDate, cityName);
//                cout << "�������� ��������!\n";
//            }
//            catch (const exception& e) {
//                cout << "������: " << e.what() << endl;
//            }
//            break;
//        }
//        case 3: {
//            string name;
//            cout << "������� ��� ��������: ";
//            cin.ignore();
//            getline(cin, name);
//            try {
//                db.deleteDriver(name);
//                cout << "�������� ������!\n";
//            }
//            catch (const exception& e) {
//                cout << "������: " << e.what() << endl;
//            }
//            break;
//        }
//        case 4: return;
//        default:
//            cin.clear();
//            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//            cout << "�������� �����!\n";
//        }
//    } while (true);
//}
//
//// ----------- ���������� �������� -----------
//void UserInterface::showFineMenu() {
//    int choice;
//    do {
//        cout << "\n========== ���������� �������� ==========\n"
//            << "1. ������ �������\n"
//            << "2. �������� �����\n"
//            << "3. ������� �����\n"
//            << "4. �����\n"
//            << "�������� �����: ";
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
//                    to_string(fine.amount) + " ���.",
//                    FineTable::severityToString(fine.severity)
//                    });
//            }
//            printDynamicTable({ "���", "�����", "�������" }, fineData);
//            break;
//        }
//        case 2: {
//            string type;
//            double amount;
//            int severity;
//
//            cout << "������� ��� ���������: ";
//            cin.ignore();
//            getline(cin, type);
//
//            cout << "������� ����� ������: ";
//            while (!(cin >> amount) || amount < 0) {
//                cin.clear();
//                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//                cout << "������! ������� ������������� �����: ";
//            }
//
//            cout << "�������� ������� (1-������, 2-�������, 3-�������): ";
//            while (!(cin >> severity) || severity < 1 || severity > 3) {
//                cin.clear();
//                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//                cout << "������! ������� 1-3: ";
//            }
//
//            try {
//                db.addFine(type, amount, static_cast<FineTable::Severity>(severity - 1));
//                cout << "����� ��������!\n";
//            }
//            catch (const exception& e) {
//                cout << "������: " << e.what() << endl;
//            }
//            break;
//        }
//        case 3: {
//            string type;
//            cout << "������� ��� ������: ";
//            cin.ignore();
//            getline(cin, type);
//            try {
//                db.getFines().deleteFine(type);
//                cout << "����� ������!\n";
//            }
//            catch (const exception& e) {
//                cout << "������: " << e.what() << endl;
//            }
//            break;
//        }
//        case 4: return;
//        default:
//            cin.clear();
//            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//            cout << "�������� �����!\n";
//        }
//    } while (true);
//}
//
//// ----------- ���������� ����������� -----------
//void UserInterface::showViolationMenu() {
//    int choice;
//    do {
//        cout << "\n========== ���������� ����������� ==========\n"
//            << "1. ��� ���������\n"
//            << "2. �������� ���������\n"
//            << "3. �������� ��� ����������\n"
//            << "4. ����������� ���������\n"
//            << "5. �����\n"
//            << "�������� �����: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            auto data = prepareViolationData();
//            printDynamicTable({ "��������", "�����", "�����", "����", "�����", "������" }, data);
//            break;
//        }
//        case 2: {
//            string driverName, fineType, date;
//            bool isValid = false;
//
//            cout << "\n������ ���������:\n";
//            db.getDrivers().driverIteratorReset();
//            while (db.getDrivers().driverIteratorHasNext()) {
//                auto driver = db.getDrivers().driverIteratorNext();
//                cout << "� " << driver.fullName << endl;
//            }
//
//            do {
//                cout << "������� ��� ��������: ";
//                cin.ignore();
//                getline(cin, driverName);
//                isValid = db.getDrivers().getDriverId(driverName) != -1;
//                if (!isValid) cout << "�������� �� ������!\n";
//            } while (!isValid);
//
//            cout << "\n������ �������:\n";
//            db.getFines().fineIteratorReset();
//            while (db.getFines().fineIteratorHasNext()) {
//                auto fine = db.getFines().fineIteratorNext();
//                cout << "� " << fine.type << " (" << fine.amount << " ���.)\n";
//            }
//
//            do {
//                cout << "������� ��� ������: ";
//                getline(cin, fineType);
//                isValid = db.getFines().getFineIdByType(fineType) != -1;
//                if (!isValid) cout << "����� �� ������!\n";
//            } while (!isValid);
//
//            do {
//                cout << "������� ���� ��������� (��.��.����): ";
//                getline(cin, date);
//                isValid = validateDate(date);
//                if (!isValid) cout << "������������ ����!\n";
//            } while (!isValid);
//
//            try {
//                db.addViolation(driverName, fineType, date);
//                cout << "��������� ���������!\n";
//            }
//            catch (const exception& e) {
//                cout << "������: " << e.what() << endl;
//            }
//            break;
//        }
//        case 3: {
//            int recordId;
//            cout << "������� ID ���������: ";
//            while (!(cin >> recordId) || recordId < 1) {
//                cin.clear();
//                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//                cout << "������! ������� ������������� �����: ";
//            }
//            try {
//                db.markFineAsPaid(recordId);
//                cout << "������ ��������!\n";
//            }
//            catch (const exception& e) {
//                cout << "������: " << e.what() << endl;
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
//            cout << "�������� �����!\n";
//        }
//    } while (true);
//}
//
//// ----------- ���������� -----------
//void UserInterface::showStatisticsMenu() {
//    int choice;
//    do {
//        cout << "\n========== ���������� ==========\n"
//            << "1. ��������� �� �������\n"
//            << "2. ��� �����������\n"
//            << "3. �����\n"
//            << "�������� �����: ";
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
//            for (const auto& entry : cityStats) { // ���������� entry ������ [city, count]
//                statsData.push_back({
//                    entry.first,                // ����� (����)
//                    std::to_string(entry.second) // ���������� ��������� (��������)
//                    });
//            }
//            printDynamicTable({ "�����", "���������" }, statsData);
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
//            printDynamicTable({ "�����", "��������", "���������" }, topData);
//            break;
//        }
//        case 3:
//            return;
//        default:
//            cin.clear();
//            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
//            cout << "�������� �����!\n";
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

// ==================== ��������� ������ ====================
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

// ==================== �������������� ������ ====================
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

    // ������ ������ �������
    for (size_t i = 0; i < headers.size(); ++i) {
        widths[i] = headers[i].length();
        for (const auto& row : data) {
            if (i < row.size() && row[i].length() > widths[i]) {
                widths[i] = row[i].length();
            }
        }
        widths[i] += 2; // ��������� ������
    }

    // ����� �����
    cout << "\n";
    for (size_t i = 0; i < headers.size(); ++i) {
        cout << "| " << left << setw(widths[i]) << headers[i] << " ";
    }
    cout << "|\n" << string(accumulate(widths.begin(), widths.end(), 0) + headers.size() * 3, '-') << "\n";

    // ����� ������
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            cout << "| " << left << setw(widths[i]) << row[i] << " ";
        }
        cout << "|\n";
    }
}

// ==================== �������� ������ ====================
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

// ==================== ���� ��������� ====================
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
            // ��������� ������ ������...
        }
    } while (choice != 6);
}

// ==================== ���������� ====================
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

// ==================== ���� ������� ====================
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

// ==================== ���� ��������� ====================
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

// ==================== ���� ������� ====================
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

// ==================== ���� ���������� ====================
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

// ==================== ��������� ������ ====================
void UserInterface::handleError(const exception& e) {
    cerr << "\nError: " << e.what() << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ==================== �������������� ������� ====================
void UserInterface::displayHelp() {
    cout << "\nHelp:\n"
        << " - Use '*' for any characters sequence\n"
        << " - Use '?' for any single character\n"
        << " - Date format: DD.MM.YYYY\n"
        << " - Amount examples: >500, <1000, 200-500\n";
}

// ==================== ���������� ������ ====================
void UserInterface::cleanup() {
    db.saveAll();
    cout << "\nAll data saved successfully!\n";
}