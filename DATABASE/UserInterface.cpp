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
        cout << "\n========== ������� ���� ==========\n"
            << "1. ���������� ��������\n"
            << "2. ���������� ����������\n"
            << "3. ���������� ��������\n"
            << "4. ���������� �����������\n"
            << "5. ����������\n"
            << "6. �����\n"
            << "�������� �����: ";
        cin >> choice;

        switch (choice) {
        case 1: showCityMenu(); break;
        case 2: showDriverMenu(); break;
        case 3: showFineMenu(); break;
        case 4: showViolationMenu(); break;
        case 5: showStatisticsMenu(); break;
        case 6: cout << "���������� ������...\n"; break;
        default:
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "�������� ����!\n";
        }
    } while (choice != 6);
}

void UserInterface::showCityMenu() {
    int choice;
    do {
        cout << "\n========== ���������� �������� ==========\n"
            << "1. ������ �������\n"
            << "2. �������� �����\n"
            << "3. ������� �����\n"
            << "4. �����\n"
            << "�������� �����: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            vector<string> headers = { "��������", "���������", "���", "��������" };
            printTableHeader(headers);

            db.getCities().cityIteratorReset();
            while (db.getCities().cityIteratorHasNext()) {
                auto city = db.getCities().cityIteratorNext();
                vector<string> cells = {
                    city.name,
                    to_string(city.population) + " ���.",
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

            cout << "������� �������� ������: ";
            cin.ignore();
            getline(cin, name);

            cout << "������� ���������: ";
            cin >> population;

            cout << "�������� �������� (1-�����, 2-�������, 3-�������): ";
            cin >> gradeChoice;

            cout << "�������� ��� (1-�����, 2-������, 3-�������): ";
            cin >> typeChoice;

            try {
                db.addCity(name,
                    population,
                    static_cast<CityTable::PopulationGrade>(gradeChoice - 1),
                    static_cast<CityTable::SettlementType>(typeChoice - 1));
                cout << "����� ��������!\n";
            }
            catch (const exception& e) {
                cout << "������: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            string name;
            cout << "������� �������� ������: ";
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
        cout << "\n========== ���������� ���������� ==========\n"
            << "1. ������ ���������\n"
            << "2. �������� ��������\n"
            << "3. ������� ��������\n"
            << "4. �����\n"
            << "�������� �����: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            vector<string> headers = { "���", "���� ��������", "����� ����������" };
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
                cout << "������� ���: ";
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                getline(cin, name);
                valid = validateName(name);
                if (!valid) cout << "������������ ���!\n";
            } while (!valid);

            do {
                cout << "������� ���� �������� (��.��.����): ";
                getline(cin, birthDate);
                valid = validateDate(birthDate);
                if (!valid) cout << "������������ ����!\n";
            } while (!valid);

            cout << "��������� ������:\n";
            db.getCities().cityIteratorReset();
            while (db.getCities().cityIteratorHasNext()) {
                auto city = db.getCities().cityIteratorNext();
                cout << "� " << city.name << endl;
            }
            cout << "������� �������� ������: ";
            getline(cin, cityName);

            try {
                db.addDriver(name, birthDate, cityName);
                cout << "�������� ��������!\n";
            }
            catch (const exception& e) {
                cout << "������: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            string name;
            cout << "������� ��� ��������: ";
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
        cout << "\n========== ���������� �������� ==========\n"
            << "1. ������ �������\n"
            << "2. �������� �����\n"
            << "3. ������� �����\n"
            << "4. �����\n"
            << "�������� �����: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            vector<string> headers = { "��� ���������", "�����", "�������" };
            printTableHeader(headers);

            db.getFines().fineIteratorReset();
            while (db.getFines().fineIteratorHasNext()) {
                auto fine = db.getFines().fineIteratorNext();
                vector<string> cells = {
                    fine.type,
                    to_string(fine.amount) + " ���.",
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

            cout << "������� ��� ���������: ";
            cin.ignore();
            getline(cin, type);

            cout << "������� ����� ������: ";
            cin >> amount;

            cout << "�������� ������� (1-������, 2-�������, 3-�������): ";
            cin >> severity;

            try {
                db.addFine(type, amount, static_cast<FineTable::Severity>(severity - 1));
                cout << "����� ��������!\n";
            }
            catch (const exception& e) {
                cout << "������: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            string type;
            cout << "������� ��� ������: ";
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
        cout << "\n========== ���������� ����������� ==========\n"
            << "1. ��� ���������\n"
            << "2. �������� ���������\n"
            << "3. �������� ��� ����������\n"
            << "4. �����\n"
            << "�������� �����: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            vector<string> headers = { "��������", "�����", "�����", "����", "�����", "������" };
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
                    to_string(violation.amount) + " ���.",
                    violation.paid ? "��������" : "�� ��������"
                };
                printTableRow(cells, 25);
            }
            break;
        }
        case 2: {
            string driverName, fineType, date;

            cout << "\n������ ���������:\n";
            db.getDrivers().driverIteratorReset();
            while (db.getDrivers().driverIteratorHasNext()) {
                auto driver = db.getDrivers().driverIteratorNext();
                cout << "� " << driver.fullName << endl;
            }
            cout << "������� ��� ��������: ";
            cin.ignore();
            getline(cin, driverName);

            cout << "\n������ �������:\n";
            db.getFines().fineIteratorReset();
            while (db.getFines().fineIteratorHasNext()) {
                auto fine = db.getFines().fineIteratorNext();
                cout << "� " << fine.type << " (" << fine.amount << " ���.)\n";
            }
            cout << "������� ��� ������: ";
            getline(cin, fineType);

            do {
                cout << "������� ���� ��������� (��.��.����): ";
                getline(cin, date);
            } while (!validateDate(date));

            try {
                db.addViolation(driverName, fineType, date);
                cout << "��������� ���������!\n";
            }
            catch (const exception& e) {
                cout << "������: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            int recordId;
            cout << "������� ID ���������: ";
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
        cout << "\n========== ���������� ==========\n"
            << "1. ��������� �� �������\n"
            << "2. ��� �����������\n"
            << "3. �����\n"
            << "�������� �����: ";
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

            vector<string> headers = { "�����", "���������� ���������" };
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

            vector<string> headers = { "�����", "��������", "���������" };
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