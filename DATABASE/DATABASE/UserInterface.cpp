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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            CityTable::City* city = db.getCities().getAllCities();
            cout << "\nСписок городов:\n";
            while (city) {
                cout << "ID: " << setw(5) << left << city->id
                    << " | Название: " << city->name << endl;
                city = city->next;
            }
            break;
        }
        case 2: {
            string name;
            cout << "Введите название города: ";
            cin.ignore();
            getline(cin, name);
            db.addCity(name);
            cout << "Город добавлен!\n";
            break;
        }
        case 3: {
            int cityId;
            cout << "Введите ID города: ";
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
        cout << "\n========== УПРАВЛЕНИЕ ВОДИТЕЛЯМИ ==========\n"
            << "1. Список водителей\n"
            << "2. Добавить водителя\n"
            << "3. Удалить водителя\n"
            << "4. Назад\n"
            << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            DriverTable::Driver* driver = db.getDrivers().getAllDrivers();
            cout << "\nСписок водителей:\n";
            while (driver) {
                cout << "ID: " << setw(5) << left << driver->id
                    << " | ФИО: " << driver->fullName
                    << " | Дата рождения: " << driver->birthDate
                    << " | Город: " << db.getCities().getCityName(driver->cityId) << endl;
                driver = driver->next;
            }
            break;
        }
        case 2: {
            string fullName, birthDate;
            int cityId;
            bool valid = false;

            do {
                cout << "Введите ФИО: ";
                cin.ignore();
                getline(cin, fullName);
                valid = validateName(fullName);
                if (!valid) cout << "Ошибка! Используйте только буквы и пробелы.\n";
            } while (!valid);


            do {
                cout << "Введите дату рождения (ДД.ММ.ГГГГ): ";
                getline(cin, birthDate);
                cin >> birthDate;
                valid = validateDate(birthDate);
                if (!valid) cout << "Неверный формат даты!\n";
            } while (!valid);

            cout << "\nДоступные города:\n";
            CityTable::City* city = db.getCities().getAllCities();
            while (city) {
                cout << "ID: " << city->id << " | " << city->name << endl;
                city = city->next;
            }
            cout << "Введите ID города: ";
            cin >> cityId;

            try {
                db.addDriver(fullName, birthDate, cityId);
                cout << "Водитель добавлен!\n";
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            int driverId;
            cout << "Введите ID водителя: ";
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
        cout << "\n========== УПРАВЛЕНИЕ ШТРАФАМИ ==========\n"
            << "1. Список штрафов\n"
            << "2. Добавить штраф\n"
            << "3. Удалить штраф\n"
            << "4. Назад\n"
            << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            FineTable::Fine* fine = db.getFines().getAllFines();
            cout << "\nСписок штрафов:\n";
            while (fine) {
                cout << "ID: " << setw(5) << left << fine->id
                    << " | Сумма: " << fine->amount
                    << " | Тип: " << fine->type << endl;
                fine = fine->next;
            }
            break;
        }
        case 2: {
            double amount;
            string type;
            cout << "Введите сумму штрафа: ";
            cin >> amount;
            cout << "Введите тип нарушения: ";
            cin.ignore();
            getline(cin, type);
            db.addFine(amount, type);
            cout << "Штраф добавлен!\n";
            break;
        }
        case 3: {
            int fineId;
            cout << "Введите ID штрафа: ";
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
        cout << "\n========== УПРАВЛЕНИЕ НАРУШЕНИЯМИ ==========\n"
            << "1. Все нарушения\n"
            << "2. Добавить нарушение\n"
            << "3. Отметить как оплаченное\n"
            << "4. Назад\n"
            << "Выберите опцию: ";
        cin >> choice;


        switch (choice) {
        case 1: {
            FineRegistry::FineRecord* record = db.getRegistry().getRecordsByDriver(0);
            cout << "\nСписок нарушений:\n";
            while (record) {
                cout << "ID: " << setw(5) << left << record->id
                    << " | Водитель: " << db.getDrivers().getDriverInfo(record->driverId)
                    << " | Город: " << db.getCities().getCityName(record->cityId)
                    << " | Статус: " << (record->isPaid ? "Оплачен" : "Не оплачен") << endl;
                record = record->next;
            }
            break;
        }
        case 2: {
            int driverId, fineId;
            bool driverExists = false, fineExists = false;

            // Выбор водителя с проверкой
            do {
                cout << "\nСписок водителей:\n";
                DriverTable::Driver* driver = db.getDrivers().getAllDrivers();
                while (driver) {
                    cout << "ID: " << driver->id << " | " << driver->fullName << endl;
                    driver = driver->next;
                }

                cout << "\nВведите ID водителя: ";
                cin >> driverId;

                // Проверяем, существует ли водитель с таким ID
                DriverTable::Driver* currentDriver = db.getDrivers().getAllDrivers();
                while (currentDriver) {
                    if (currentDriver->id == driverId) {
                        driverExists = true;
                        break;
                    }
                    currentDriver = currentDriver->next;
                }

                if (!driverExists) {
                    cout << "Ошибка: Водитель с ID " << driverId << " не найден!\n";
                    cout << "Попробуйте снова.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (!driverExists);

            // Выбор штрафа с проверкой
            do {
                cout << "\nСписок штрафов:\n";
                FineTable::Fine* fine = db.getFines().getAllFines();
                while (fine) {
                    cout << "ID: " << fine->id << " | " << fine->type << " | " << fine->amount << " руб." << endl;
                    fine = fine->next;
                }

                cout << "\nВведите ID штрафа: ";
                cin >> fineId;

                // Проверяем, существует ли штраф с таким ID
                FineTable::Fine* currentFine = db.getFines().getAllFines();
                while (currentFine) {
                    if (currentFine->id == fineId) {
                        fineExists = true;
                        break;
                    }
                    currentFine = currentFine->next;
                }

                if (!fineExists) {
                    cout << "Ошибка: Штраф с ID " << fineId << " не найден!\n";
                    cout << "Попробуйте снова.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (!fineExists);

            // Если оба ID корректны — добавляем нарушение
            try {
                db.addViolation(driverId, fineId);
                cout << "Нарушение успешно добавлено!\n";
            }
            catch (const exception& e) {
                cout << "Ошибка при добавлении нарушения: " << e.what() << endl;
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
                CityTable::City* city = db.getCities().getAllCities();
                while (city) {
                    int count = 0;
                    FineRegistry::FineRecord* record = db.getRegistry().getRecordsByCity(city->id);
                    while (record) {
                        count++;
                        record = record->next;
                    }
                    cout << city->name << ": " << count << " нарушений\n";
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

                cout << "\nТоп нарушителей:\n";
                for (size_t i = 0; i < min(5, (int)sorted.size()); i++) {
                    cout << i + 1 << ". " << db.getDrivers().getDriverInfo(sorted[i].first)
                        << " | Нарушений: " << sorted[i].second << endl;
                }
                break;
            }
            }
        } while (choice != 3);
}
