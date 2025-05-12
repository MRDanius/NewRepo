#include "UserInterface.h"
#include <iostream>
#include <iomanip>
#include <clocale>
#include <limits>
#include <algorithm>
#include <regex>

using namespace std;

bool validateDate(const string& date) {
    regex pattern(R"(^(0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.\d{4}$)");
    return regex_match(date, pattern);
}

bool validateName(const string& name) {
    return all_of(name.begin(), name.end(), [](char c) {
        return isalpha(c) || c == ' ' || c == '-' || c == '.';
        });
}

void UserInterface::run() {
    setlocale(LC_ALL, "Russian");
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            CityTable::City* city = db.getCities().getAllCities();
            cout << "\n������ �������:\n";
            while (city) {
                cout << "ID: " << setw(5) << left << city->id
                    << " | ��������: " << city->name << endl;
                city = city->next;
            }
            break;
        }
        case 2: {
            string name;
            cout << "������� �������� ������: ";
            cin.ignore();
            getline(cin, name);
            db.addCity(name);
            cout << "����� ��������!\n";
            break;
        }
        case 3: {
            int cityId;
            cout << "������� ID ������: ";
            cin >> cityId;
            db.deleteCity(cityId);
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
            DriverTable::Driver* driver = db.getDrivers().getAllDrivers();
            cout << "\n������ ���������:\n";
            while (driver) {
                cout << "ID: " << setw(5) << left << driver->id
                    << " | ���: " << driver->fullName
                    << " | ���� ��������: " << driver->birthDate
                    << " | �����: " << db.getCities().getCityName(driver->cityId) << endl;
                driver = driver->next;
            }
            break;
        }
        case 2: {
            string fullName, birthDate;
            int cityId;
            bool valid = false;

            do {
                cout << "������� ���: ";
                cin.ignore();
                getline(cin, fullName);
                valid = validateName(fullName);
                if (!valid) cout << "������! ����������� ������ ����� � �������.\n";
            } while (!valid);


            do {
                cout << "������� ���� �������� (��.��.����): ";
                getline(cin, birthDate);
                cin >> birthDate;
                valid = validateDate(birthDate);
                if (!valid) cout << "�������� ������ ����!\n";
            } while (!valid);

            cout << "\n��������� ������:\n";
            CityTable::City* city = db.getCities().getAllCities();
            while (city) {
                cout << "ID: " << city->id << " | " << city->name << endl;
                city = city->next;
            }
            cout << "������� ID ������: ";
            cin >> cityId;

            try {
                db.addDriver(fullName, birthDate, cityId);
                cout << "�������� ��������!\n";
            }
            catch (const exception& e) {
                cout << "������: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            int driverId;
            cout << "������� ID ��������: ";
            cin >> driverId;
            db.deleteDriver(driverId);
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
            FineTable::Fine* fine = db.getFines().getAllFines();
            cout << "\n������ �������:\n";
            while (fine) {
                cout << "ID: " << setw(5) << left << fine->id
                    << " | �����: " << fine->amount
                    << " | ���: " << fine->type << endl;
                fine = fine->next;
            }
            break;
        }
        case 2: {
            double amount;
            string type;
            cout << "������� ����� ������: ";
            cin >> amount;
            cout << "������� ��� ���������: ";
            cin.ignore();
            getline(cin, type);
            db.addFine(amount, type);
            cout << "����� ��������!\n";
            break;
        }
        case 3: {
            int fineId;
            cout << "������� ID ������: ";
            cin >> fineId;
            db.getFines().deleteRecord(fineId);
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
            FineRegistry::FineRecord* record = db.getRegistry().getRecordsByDriver(0);
            cout << "\n������ ���������:\n";
            while (record) {
                cout << "ID: " << setw(5) << left << record->id
                    << " | ��������: " << db.getDrivers().getDriverInfo(record->driverId)
                    << " | �����: " << db.getCities().getCityName(record->cityId)
                    << " | ������: " << (record->isPaid ? "�������" : "�� �������") << endl;
                record = record->next;
            }
            break;
        }
        case 2: {
            int driverId, fineId;
            bool driverExists = false, fineExists = false;

            // ����� �������� � ���������
            do {
                cout << "\n������ ���������:\n";
                DriverTable::Driver* driver = db.getDrivers().getAllDrivers();
                while (driver) {
                    cout << "ID: " << driver->id << " | " << driver->fullName << endl;
                    driver = driver->next;
                }

                cout << "\n������� ID ��������: ";
                cin >> driverId;

                // ���������, ���������� �� �������� � ����� ID
                DriverTable::Driver* currentDriver = db.getDrivers().getAllDrivers();
                while (currentDriver) {
                    if (currentDriver->id == driverId) {
                        driverExists = true;
                        break;
                    }
                    currentDriver = currentDriver->next;
                }

                if (!driverExists) {
                    cout << "������: �������� � ID " << driverId << " �� ������!\n";
                    cout << "���������� �����.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (!driverExists);

            // ����� ������ � ���������
            do {
                cout << "\n������ �������:\n";
                FineTable::Fine* fine = db.getFines().getAllFines();
                while (fine) {
                    cout << "ID: " << fine->id << " | " << fine->type << " | " << fine->amount << " ���." << endl;
                    fine = fine->next;
                }

                cout << "\n������� ID ������: ";
                cin >> fineId;

                // ���������, ���������� �� ����� � ����� ID
                FineTable::Fine* currentFine = db.getFines().getAllFines();
                while (currentFine) {
                    if (currentFine->id == fineId) {
                        fineExists = true;
                        break;
                    }
                    currentFine = currentFine->next;
                }

                if (!fineExists) {
                    cout << "������: ����� � ID " << fineId << " �� ������!\n";
                    cout << "���������� �����.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (!fineExists);

            // ���� ��� ID ��������� � ��������� ���������
            try {
                db.addViolation(driverId, fineId);
                cout << "��������� ������� ���������!\n";
            }
            catch (const exception& e) {
                cout << "������ ��� ���������� ���������: " << e.what() << endl;
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
                CityTable::City* city = db.getCities().getAllCities();
                while (city) {
                    int count = 0;
                    FineRegistry::FineRecord* record = db.getRegistry().getRecordsByCity(city->id);
                    while (record) {
                        count++;
                        record = record->next;
                    }
                    cout << city->name << ": " << count << " ���������\n";
                    city = city->next;
                }
                break;
            }
            case 2: {
                map<int, int> violations;
                FineRegistry::FineRecord* record = db.getRegistry().getRecordsByDriver(0);
                while (record) {
                    violations[record->driverId]++;
                    record = record->next;
                }

                vector<pair<int, int>> sorted(violations.begin(), violations.end());
                sort(sorted.begin(), sorted.end(), [](auto& a, auto& b) {
                    return a.second > b.second;
                    });

                cout << "\n��� �����������:\n";
                for (size_t i = 0; i < min(5, (int)sorted.size()); i++) {
                    cout << i + 1 << ". " << db.getDrivers().getDriverInfo(sorted[i].first)
                        << " | ���������: " << sorted[i].second << endl;
                }
                break;
            }
            }
        } while (choice != 3);
}
