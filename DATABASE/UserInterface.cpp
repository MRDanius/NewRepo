//#include "UserInterface.h"
//#include <iostream>
//#include <limits>
//#include <algorithm>
//#include <clocale>
//#include <iomanip>
//using namespace std;
//
//// Ширины колонок (без ID)
//static constexpr int NAME_WIDTH = 20;
//static constexpr int POPULATION_WIDTH = 12;
//static constexpr int TYPE_WIDTH = 10;
//static constexpr int DRIVER_NAME_WIDTH = 40;
//static constexpr int BIRTH_WIDTH = 12;
//static constexpr int FINE_TYPE_WIDTH = 20;
//static constexpr int AMOUNT_WIDTH = 10;
//static constexpr int SEVERITY_WIDTH = 10;
//static constexpr int DATE_WIDTH = 12;
//static constexpr int PAID_WIDTH = 6;
//
//// Печать разделительной строки для таблицы городов
//static void printCitiesBorder() {
//    cout << '+'
//        << string(NAME_WIDTH + 2, '-') << '+'
//        << string(POPULATION_WIDTH + 2, '-') << '+'
//        << string(TYPE_WIDTH + 2, '-') << '+'
//        << "\n";
//}
//
//// Печать заголовка таблицы городов
//static void printCitiesHeader() {
//    printCitiesBorder();
//    cout << "| " << left << setw(NAME_WIDTH) << "Название" << " | "
//        << left << setw(POPULATION_WIDTH) << "Население" << " | "
//        << left << setw(TYPE_WIDTH) << "Тип" << " |\n";
//    printCitiesBorder();
//}
//
//// Печать строки с данными о городе
//static void printCityRow(const string& name, int population, const string& type) {
//    cout << "| " << left << setw(NAME_WIDTH) << name << " | "
//        << right << setw(POPULATION_WIDTH) << population << " | "
//        << left << setw(TYPE_WIDTH) << type << " |\n";
//}
//
//// Печать разделительной строки для таблицы водителей
//static void printDriversBorder() {
//    cout << '+'
//        << string(DRIVER_NAME_WIDTH + 2, '-') << '+'
//        << string(BIRTH_WIDTH + 3, '-') << '+'
//        << string(NAME_WIDTH + 2, '-') << '+'
//        << "\n";
//}
//
//// Печать заголовка таблицы водителей
//static void printDriversHeader() {
//    printDriversBorder();
//    cout << "| " << left << setw(DRIVER_NAME_WIDTH) << "ФИО" << " | "
//        << left << setw(BIRTH_WIDTH) << "Дата рождения" << " | "
//        << left << setw(NAME_WIDTH) << "Город" << " |\n";
//    printDriversBorder();
//}
//
//// Печать строки с данными о водителе
//static void printDriverRow(const string& fullName, const string& birthDate, const string& cityName) {
//    cout << "| " << left << setw(DRIVER_NAME_WIDTH) << fullName << " | "
//        << left << setw(BIRTH_WIDTH) << birthDate << "  | "
//        << left << setw(NAME_WIDTH) << cityName << " |\n";
//}
//
//// Печать разделительной строки для таблицы штрафов
//static void printFinesBorder() {
//    cout << '+'
//        << string(FINE_TYPE_WIDTH + 2, '-') << '+'
//        << string(AMOUNT_WIDTH + 2, '-') << '+'
//        << string(SEVERITY_WIDTH + 2, '-') << '+'
//        << "\n";
//}
//
//// Печать заголовка таблицы штрафов
//static void printFinesHeader() {
//    printFinesBorder();
//    cout << "| " << left << setw(FINE_TYPE_WIDTH) << "Тип" << " | "
//        << left << setw(AMOUNT_WIDTH) << "Сумма" << " | "
//        << left << setw(SEVERITY_WIDTH) << "Уровень" << " |\n";
//    printFinesBorder();
//}
//
//// Печать строки с данными о штрафе
//static void printFineRow(const string& type, double amount, const string& severity) {
//    cout << "| " << left << setw(FINE_TYPE_WIDTH) << type << " | "
//        << left << setw(AMOUNT_WIDTH) << amount << " | "
//        << left << setw(SEVERITY_WIDTH) << severity << " |\n";
//}
//
//// Печать разделительной строки для таблицы нарушений
//static void printViolationsBorder() {
//    cout << '+'
//        << string(DRIVER_NAME_WIDTH + 2, '-') << '+'
//        << string(NAME_WIDTH + 2, '-') << '+'
//        << string(FINE_TYPE_WIDTH + 2, '-') << '+'
//        << string(AMOUNT_WIDTH + 2, '-') << '+'
//        << string(DATE_WIDTH + 2, '-') << '+'
//        << string(PAID_WIDTH + 3, '-') << '+'
//        << "\n";
//}
//
//// Печать заголовка таблицы нарушений
//static void printViolationsHeader() {
//    printViolationsBorder();
//    cout << "| " << left << setw(DRIVER_NAME_WIDTH) << "Водитель" << " | "
//        << left << setw(NAME_WIDTH) << "Город" << " | "
//        << left << setw(FINE_TYPE_WIDTH) << "Штраф" << " | "
//        << left << setw(AMOUNT_WIDTH) << "Сумма" << " | "
//        << left << setw(DATE_WIDTH) << "Дата" << " | "
//        << left << setw(PAID_WIDTH) << "Оплачен" << " |\n";
//    printViolationsBorder();
//}
//
//// Печать строки с данными о нарушении
//static void printViolationRow(const string& driverName, const string& cityName,
//    const string& fineType, double fineAmount,
//    const string& date, bool paid) {
//    cout << "| " << left << setw(DRIVER_NAME_WIDTH) << driverName << " | "
//        << left << setw(NAME_WIDTH) << cityName << " | "
//        << left << setw(FINE_TYPE_WIDTH) << fineType << " | "
//        << left << setw(AMOUNT_WIDTH) << fineAmount << " | "
//        << left << setw(DATE_WIDTH) << date << " | "
//        << left << setw(PAID_WIDTH) << (paid ? "Да" : "Нет") << "  |\n";
//}
//
//void UserInterface::run() {
//    setlocale(LC_ALL, ""); // Для корректного вывода кириллицы
//    dbManager.loadAll();
//    while (true) {
//        mainMenu();
//    }
//}
//
//void UserInterface::mainMenu() {
//    while (true) {
//        cout << "\n=== Главное меню ===\n";
//        cout << "1. Управление городами\n";
//        cout << "2. Управление водителями\n";
//        cout << "3. Управление штрафами\n";
//        cout << "4. Управление нарушениями\n";
//        cout << "5. Статистика\n";
//        cout << "6. Выход\n";
//        int choice = readInt("Выберите пункт: ");
//        switch (choice) {
//        case 1: citiesMenu();   break;
//        case 2: driversMenu();  break;
//        case 3: finesMenu();    break;
//        case 4: registryMenu(); break;
//        case 5: statisticsMenu(); break;
//        case 6: dbManager.saveAll(); exit(0);
//        default: cout << "Неверный выбор. Попробуйте снова.\n";
//        }
//    }
//}
//
//void UserInterface::citiesMenu() {
//    while (true) {
//        cout << "\n--- Города ---\n";
//        cout << "1. Список городов\n";
//        cout << "2. Добавить город\n";
//        cout << "3. Удалить город\n";
//        cout << "4. Фильтрация городов\n";
//        cout << "5. Сбросить фильтры\n";
//        cout << "6. Назад\n";
//        int choice = readInt("Выберите пункт: ");
//        switch (choice) {
//        case 1: listCities();       break;
//        case 2: addCity();          break;
//        case 3: deleteCity();       break;
//        case 4: filterCities();     break;
//        case 5: clearCityFilters(); break;
//        case 6: return;
//        default: cout << "Неверный выбор.\n";
//        }
//    }
//}
//
//void UserInterface::listCities() {
//    printCitiesHeader();
//    CityTable& cities = dbManager.getCities();
//    CityTable::CityNode* filteredHead = cities.applyFilters();
//    cities.cityIteratorReset(filteredHead);
//    while (cities.cityIteratorHasNext()) {
//        auto ci = cities.cityIteratorNext();
//        printCityRow(ci.name, ci.population,
//            CityTable::settlementTypeToString(ci.type));
//    }
//    printCitiesBorder();
//
//    CityTable::CityNode* tmp = filteredHead;
//    while (tmp) {
//        CityTable::CityNode* next = tmp->next;
//        delete tmp;
//        tmp = next;
//    }
//}
//
//// UserInterface.cpp (замена существующего метода)
//void UserInterface::addCity() {
//    string name = readString("Название города: ");
//
//    // Проверка населения
//    int population;
//    do {
//        population = readInt("Население: ");
//        if (population < 1) cout << "Население не может быть меньше 1!\n";
//    } while (population < 1);
//
//    // Ввод градации
//    int gradeInput;
//    do {
//        cout << "Градация населения (0 - Small, 1 - Medium, 2 - Large): ";
//        gradeInput = readInt("");
//        if (gradeInput < 0 || gradeInput > 2) {
//            cout << "Некорректный ввод! Допустимые значения: 0, 1, 2\n";
//        }
//    } while (gradeInput < 0 || gradeInput > 2);
//
//    auto grade = static_cast<CityTable::PopulationGrade>(gradeInput);
//
//    // Ввод типа поселения
//    int typeInput;
//    do {
//        cout << "Тип поселения (0 - City, 1 - Town, 2 - Village): ";
//        typeInput = readInt("");
//        if (typeInput < 0 || typeInput > 2) {
//            cout << "Некорректный ввод! Допустимые значения: 0, 1, 2\n";
//        }
//    } while (typeInput < 0 || typeInput > 2);
//
//    auto type = static_cast<CityTable::SettlementType>(typeInput);
//
//    dbManager.addCity(name, population, grade, type);
//    dbManager.getCities().saveToFile();
//    cout << "Город добавлен\n";
//}
//
//void UserInterface::deleteCity() {
//    string name = readString("Название города для удаления: ");
//    dbManager.deleteCity(name);
//    cout << "Город удалён (если существовал).\n";
//}
//
//void UserInterface::filterCities() {
//    CityTable& cities = dbManager.getCities();
//    string field = readString("Введите поле (name, population, type): ");
//    string pattern = readString("Введите шаблон (regex для name/type или условие для population, например \">100000\"): ");
//    cities.addFilter(field, pattern);
//    cout << "Фильтр добавлен.\n";
//}
//
//void UserInterface::clearCityFilters() {
//    CityTable& cities = dbManager.getCities();
//    cities.clearFilters();
//    cout << "Все фильтры очищены.\n";
//}
//
//void UserInterface::driversMenu() {
//    while (true) {
//        cout << "\n--- Водители ---\n";
//        cout << "1. Список водителей\n";
//        cout << "2. Добавить водителя\n";
//        cout << "3. Удалить водителя\n";
//        cout << "4. Изменить город регистрации\n"; // НОВЫЙ ПУНКТ
//        cout << "5. Назад\n";
//
//        int choice = readInt("Выберите пункт: ");
//        switch (choice) {
//        case 1: listDrivers(); break;
//        case 2: addDriver(); break;
//        case 3: deleteDriver(); break;
//        case 4: editDriverCity(); break; // НОВЫЙ КЕЙС
//        case 5: return;
//        default: cout << "Неверный выбор.\n";
//        }
//    }
//}
//
//void UserInterface::listDrivers() {
//    printDriversHeader();
//    auto& drivers = dbManager.getDrivers();
//    auto& cities = dbManager.getCities();
//    drivers.driverIteratorReset();
//    while (drivers.driverIteratorHasNext()) {
//        auto di = drivers.driverIteratorNext();
//        string cityName = cities.getCityNameById(di.cityId);
//        printDriverRow(di.fullName, di.birthDate, cityName);
//    }
//    printDriversBorder();
//}
//
//void UserInterface::addDriver() {
//    string fullName = readString("ФИО водителя: ");
//    string birthDate = readString("Дата рождения (ДД.MM.ГГГГ): ");
//    string cityName = readString("Город регистрации: ");
//
//    int cityId = dbManager.getCities().getCityIdByName(cityName);
//    if (cityId == -1) {
//        cout << "Город \"" << cityName << "\" не найден. Введите данные для нового города.\n";
//        int population = readInt("Население: ");
//        cout << "Градация населения (0 - Small, 1 - Medium, 2 - Large): ";
//        int gradeInput = readInt("");
//        auto grade = static_cast<CityTable::PopulationGrade>(gradeInput);
//
//        cout << "Тип поселения (0 - City, 1 - Town, 2 - Village): ";
//        int typeInput = readInt("");
//        auto type = static_cast<CityTable::SettlementType>(typeInput);
//
//        dbManager.addCity(cityName, population, grade, type);
//        dbManager.getCities().saveToFile();
//        cout << "Город \"" << cityName << "\" успешно добавлен.\n";
//    }
//
//    try {
//        dbManager.addDriver(fullName, birthDate, cityName);
//        cout << "Водитель добавлен.\n";
//    }
//    catch (const exception& e) {
//        cout << "Ошибка при добавлении водителя: " << e.what() << "\n";
//    }
//}
//
//void UserInterface::deleteDriver() {
//    string name = readString("ФИО водителя для удаления: ");
//    // Собираем все водители с таким ФИО
//    auto& drivers = dbManager.getDrivers();
//    auto& cities = dbManager.getCities();
//    drivers.driverIteratorReset();
//    vector<DriverTable::DriverInfo> matchedByName;
//    while (drivers.driverIteratorHasNext()) {
//        auto di = drivers.driverIteratorNext();
//        if (di.fullName == name) {
//            matchedByName.push_back(di);
//        }
//    }
//    if (matchedByName.empty()) {
//        cout << "Водителей с таким ФИО не найдено.\n";
//        return;
//    }
//
//    // Если только один, удаляем сразу
//    if (matchedByName.size() == 1) {
//        dbManager.deleteDriverById(matchedByName[0].id);
//        cout << "Водитель удалён.\n";
//        return;
//    }
//
//    // Несколько совпадений: уточняем по дате рождения
//    vector<DriverTable::DriverInfo> matchedByDate;
//    string birthDate = readString("Несколько водителей с таким ФИО. Введите дату рождения (ДД.MM.ГГГГ): ");
//    for (auto& di : matchedByName) {
//        if (di.birthDate == birthDate) {
//            matchedByDate.push_back(di);
//        }
//    }
//    if (matchedByDate.empty()) {
//        cout << "Водителей с таким ФИО и датой рождения не найдено.\n";
//        return;
//    }
//
//    // Если после даты один, удаляем
//    if (matchedByDate.size() == 1) {
//        dbManager.deleteDriverById(matchedByDate[0].id);
//        cout << "Водитель удалён.\n";
//        return;
//    }
//
//    // Несколько совпадений по дате: уточняем по городу
//    vector<DriverTable::DriverInfo> matchedByCity;
//    string cityName = readString("Несколько водителей с таким ФИО и датой. Введите город: ");
//    for (auto& di : matchedByDate) {
//        string dCity = cities.getCityNameById(di.cityId);
//        if (dCity == cityName) {
//            matchedByCity.push_back(di);
//        }
//    }
//    if (matchedByCity.empty()) {
//        cout << "Водителей с такими ФИО, датой и городом не найдено.\n";
//        return;
//    }
//
//    // Если после всех фильтров несколько — удаляем их все
//    for (auto& di : matchedByCity) {
//        dbManager.deleteDriverById(di.id);
//    }
//    cout << "Удалено водителей с указанными данными: " << matchedByCity.size() << "\n";
//}
//
//void UserInterface::finesMenu() {
//    while (true) {
//        cout << "\n--- Штрафы ---\n";
//        cout << "1. Список штрафов\n";
//        cout << "2. Добавить штраф\n";
//        cout << "3. Удалить штраф\n";
//        cout << "4. Назад\n";
//        int choice = readInt("Выберите пункт: ");
//        switch (choice) {
//        case 1: listFines(); break;
//        case 2: addFine();   break;
//        case 3: deleteFine(); break;
//        case 4: return;
//        default: cout << "Неверный выбор.\n";
//        }
//    }
//}
//
//void UserInterface::listFines() {
//    printFinesHeader();
//    auto& fines = dbManager.getFines();
//    fines.fineIteratorReset();
//    while (fines.fineIteratorHasNext()) {
//        auto fi = fines.fineIteratorNext();
//        printFineRow(fi.type, fi.amount, FineTable::severityToString(fi.severity));
//    }
//    printFinesBorder();
//}
//
//// UserInterface.cpp (замена существующего метода)
//void UserInterface::addFine() {
//    string type = readString("Тип нарушения: ");
//    double amount = readDouble("Сумма: ");
//
//    // Ввод уровня тяжести
//    int sev;
//    do {
//        cout << "Уровень тяжести (0 - Light, 1 - Medium, 2 - Heavy): ";
//        sev = readInt("");
//        if (sev < 0 || sev > 2) {
//            cout << "Некорректный ввод! Допустимые значения: 0, 1, 2\n";
//        }
//    } while (sev < 0 || sev > 2);
//
//    try {
//        dbManager.addFine(type, amount,
//            static_cast<FineTable::Severity>(sev));
//        cout << "Штраф добавлен\n";
//    }
//    catch (const exception& e) {
//        cout << "Ошибка: " << e.what() << "\n";
//    }
//}
//
//void UserInterface::deleteFine() {
//    string type = readString("Тип штрафа для удаления: ");
//    dbManager.getFines().deleteFine(type);
//    cout << "Штраф удалён (если существовал).\n";
//}
//
//void UserInterface::registryMenu() {
//    while (true) {
//        cout << "\n--- Нарушения ---\n";
//        cout << "1. Список нарушений\n";
//        cout << "2. Добавить нарушение\n";
//        cout << "3. Отметить оплату\n";
//        cout << "5. Назад\n";
//
//        int choice = readInt("Выберите пункт: ");
//        switch (choice) {
//        case 1: listViolations(); break;
//        case 2: addViolation();   break;
//        case 3: markViolationPaid(); break;
//        case 5: return;
//        default: cout << "Неверный выбор.\n";
//        }
//    }
//}
//
//void UserInterface::listViolations() {
//    printViolationsHeader();
//    auto violations = dbManager.getAllViolations();
//    for (auto& vi : violations) {
//        printViolationRow(
//            vi.driverName,
//            vi.cityName,
//            vi.fineType,
//            vi.fineAmount,
//            vi.date,
//            vi.paid
//        );
//    }
//    printViolationsBorder();
//}
//
//// UserInterface.cpp (перед методом addViolation)
//bool UserInterface::parseDate(const std::string& dateStr, Date& date) {
//    if (dateStr.length() != 10 || dateStr[2] != '.' || dateStr[5] != '.')
//        return false;
//
//    try {
//        date.day = std::stoi(dateStr.substr(0, 2));
//        date.month = std::stoi(dateStr.substr(3, 2));
//        date.year = std::stoi(dateStr.substr(6, 4));
//        return isDateValid(date);
//    }
//    catch (const std::invalid_argument&) {
//        return false;
//    }
//    catch (const std::out_of_range&) {
//        return false;
//    }
//}
//
//bool UserInterface::isDateValid(const Date& date) {
//    if (date.year < 1900 || date.year > 2100) return false;
//    if (date.month < 1 || date.month > 12) return false;
//    if (date.day < 1 || date.day > 31) return false;
//
//    // Проверка количества дней в месяце
//    const int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
//    int maxDay = daysInMonth[date.month - 1];
//    if (date.month == 2 && ((date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0)))
//        maxDay = 29;
//    return date.day <= maxDay;
//}
//
//int UserInterface::calculateAge(const Date& birthDate, const Date& violationDate) {
//    int age = violationDate.year - birthDate.year;
//    if (violationDate.month < birthDate.month ||
//        (violationDate.month == birthDate.month && violationDate.day < birthDate.day)) {
//        age--;
//    }
//    return age;
//}
//
//bool UserInterface::isDriverAdult(const std::string& birthDateStr, const std::string& violationDateStr) {
//    Date birthDate, violationDate;
//    if (!parseDate(birthDateStr, birthDate)) return false;
//    if (!parseDate(violationDateStr, violationDate)) return false;
//
//    return calculateAge(birthDate, violationDate) >= 18;
//}
//
//// UserInterface.cpp (замена существующего метода)
//void UserInterface::addViolation() {
//    string driverName = readString("ФИО водителя: ");
//    string fineType = readString("Тип штрафа: ");
//    string date = readString("Дата нарушения (ДД.ММ.ГГГГ): ");
//
//    // Получаем дату рождения водителя
//    int driverId = dbManager.getDrivers().getDriverId(driverName);
//    if (driverId == -1) {
//        cout << "Водитель не найден!\n";
//        return;
//    }
//
//    string birthDate;
//    DriverTable& drivers = dbManager.getDrivers();
//    drivers.driverIteratorReset();
//    while (drivers.driverIteratorHasNext()) {
//        auto di = drivers.driverIteratorNext();
//        if (di.id == driverId) {
//            birthDate = di.birthDate;
//            break;
//        }
//    }
//
//    // Проверка возраста
//    if (!isDriverAdult(birthDate, date)) {
//        cout << "Водитель младше 18 лет на момент нарушения!\n";
//        return;
//    }
//
//    try {
//        dbManager.addViolation(driverName, fineType, date);
//        cout << "Нарушение добавлено\n";
//    }
//    catch (const exception& e) {
//        cout << "Ошибка: " << e.what() << "\n";
//    }
//}
//
//// UserInterface.cpp
//void UserInterface::editDriverCity() {
//    string fullName = readString("Введите ФИО водителя: ");
//    string newCityName = readString("Введите новый город регистрации: ");
//
//    int newCityId = dbManager.getCities().getCityIdByName(newCityName);
//    if (newCityId == -1) {
//        cout << "Город не найден!\n";
//        return;
//    }
//
//    if (dbManager.getDrivers().updateDriverCity(fullName, newCityId)) {
//        int driverId = dbManager.getDrivers().getDriverId(fullName);
//        dbManager.getRegistry().updateViolationsCity(driverId, newCityId);
//        dbManager.saveAll();
//        cout << "Данные обновлены\n";
//    }
//    else {
//        cout << "Водитель не найден\n";
//    }
//}
//
//void UserInterface::markViolationPaid() {
//    string driverName = readString("ФИО водителя: ");
//    string fineType = readString("Тип нарушения: ");
//    string date = readString("Дата (ДД.MM.ГГГГ): ");
//
//    auto violations = dbManager.getAllViolations();
//    int count = 0;
//    for (auto& vi : violations) {
//        if (vi.driverName == driverName && vi.fineType == fineType && vi.date == date && !vi.paid) {
//            dbManager.markFineAsPaid(vi.recordId);
//            ++count;
//        }
//    }
//    if (count > 0) {
//        dbManager.saveAll();
//        cout << "Отмечено оплаченных нарушений: " << count << "\n";
//    }
//    else {
//        cout << "Нарушений с такими данными не найдено или они уже оплачены.\n";
//    }
//}
//
//void UserInterface::statisticsMenu() {
//    while (true) {
//        cout << "\n--- Статистика ---\n";
//        cout << "1. Нарушения по городам\n";
//        cout << "2. Топ-5 водителей\n";
//        cout << "3. Назад\n";
//        int choice = readInt("Выберите пункт: ");
//        switch (choice) {
//        case 1: showViolationsByCity(); break;
//        case 2: showTopDrivers();       break;
//        case 3: return;
//        default: cout << "Неверный выбор.\n";
//        }
//    }
//}
//
//void UserInterface::showViolationsByCity() {
//    CityViolations stats[MAX_CITIES] = {};
//    int cityCount = 0;
//
//    collectCityStats(stats, cityCount);
//    qsort(stats, cityCount, sizeof(CityViolations), compareCityStats);
//    printCityViolations(stats, cityCount);
//}
//
//void UserInterface::collectCityStats(CityViolations* stats, int& cityCount) {
//    auto& registry = dbManager.getRegistry();
//    registry.violationIteratorReset();
//
//    while (registry.violationIteratorHasNext()) {
//        auto vi = registry.violationIteratorNext(
//            dbManager.getDrivers(),
//            dbManager.getCities(),
//            dbManager.getFines()
//        );
//
//        // Поиск города
//        int foundIdx = -1;
//        for (int i = 0; i < cityCount; ++i) {
//            if (stats[i].name == vi.cityName) {
//                foundIdx = i;
//                break;
//            }
//        }
//
//        // Добавление нового города
//        if (foundIdx == -1 && cityCount < MAX_CITIES) {
//            stats[cityCount].name = vi.cityName;
//            foundIdx = cityCount++;
//        }
//
//        // Добавление нарушения
//        if (foundIdx != -1 && stats[foundIdx].count < MAX_VIOLATIONS_PER_CITY) {
//            stats[foundIdx].violationIds[stats[foundIdx].count] = vi.recordId;
//            stats[foundIdx].count++;
//        }
//    }
//}
//
//// UserInterface.cpp
//int UserInterface::compareCityStats(const void* a, const void* b) {
//    const CityViolations* ca = static_cast<const CityViolations*>(a);
//    const CityViolations* cb = static_cast<const CityViolations*>(b);
//    return cb->count - ca->count; // Сортировка по убыванию
//}
//
//void UserInterface::printCityViolations(CityViolations* stats, int cityCount) {
//    printViolationsHeader();
//
//    for (int i = 0; i < cityCount; ++i) {
//        for (int j = 0; j < stats[i].count; ++j) {
//            auto vi = dbManager.getRegistry().getViolationById(
//                stats[i].violationIds[j],
//                dbManager.getDrivers(),
//                dbManager.getCities(),
//                dbManager.getFines()
//            );
//
//            printViolationRow(
//                vi.driverName,
//                vi.cityName,
//                vi.fineType,
//                vi.fineAmount,
//                vi.date,
//                vi.paid
//            );
//        }
//    }
//
//    printViolationsBorder();
//}
//
//void UserInterface::showTopDrivers() {
//    cout << "\nТоп-5 водителей по количеству нарушений:\n";
//    auto violations = dbManager.getAllViolations();
//    map<std::string, int> countMap;
//    for (auto& v : violations) {
//        countMap[v.driverName]++;
//    }
//    vector<std::pair<std::string, int>> vec(countMap.begin(), countMap.end());
//    sort(vec.begin(), vec.end(), [](auto& a, auto& b) { return a.second > b.second; });
//    for (size_t i = 0; i < vec.size() && i < 5; ++i) {
//        cout << vec[i].first << ": " << vec[i].second << "\n";
//    }
//}
//
//int UserInterface::readInt(const std::string& prompt) {
//    int value;
//    while (true) {
//        cout << prompt;
//        if (cin >> value) {
//            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
//            return value;
//        }
//        cout << "Неверный ввод. Пожалуйста, введите число.\n";
//        cin.clear();
//        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
//    }
//}
//
//double UserInterface::readDouble(const std::string& prompt) {
//    double value;
//    while (true) {
//        cout << prompt;
//        if (cin >> value) {
//            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
//            return value;
//        }
//        cout << "Неверный ввод. Пожалуйста, введите число.\n";
//        cin.clear();
//        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
//    }
//}
//
//std::string UserInterface::readString(const std::string& prompt) {
//    std::string value;
//    cout << prompt;
//    std::getline(cin, value);
//    return value;
//}


//// UserInterface.cpp
//#include "UserInterface.h"
//#include <iostream>
//#include <limits>
//#include <sstream>
//#include <algorithm>
//#include <clocale>
//#include <iomanip>
//using namespace std;
//
//// ======= Вспомогательные методы для работы с датами =======
//bool UserInterface::parseDate(const std::string& dateStr, Date& date) {
//    if (dateStr.size() != 10 || dateStr[2] != '.' || dateStr[5] != '.') return false;
//    try {
//        date.day = stoi(dateStr.substr(0, 2));
//        date.month = stoi(dateStr.substr(3, 2));
//        date.year = stoi(dateStr.substr(6, 4));
//    }
//    catch (...) {
//        return false;
//    }
//    return true;
//}
//
//bool UserInterface::isDateValid(const Date& date) {
//    if (date.year < 1900 || date.year > 2100) return false;
//    if (date.month < 1 || date.month > 12) return false;
//    if (date.day < 1 || date.day > 31) return false;
//    static const int mdays[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
//    int maxDay = mdays[date.month];
//    if (date.month == 2) { // високосный
//        if ((date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0)) {
//            maxDay = 29;
//        }
//    }
//    return date.day <= maxDay;
//}
//
//int UserInterface::calculateAge(const Date& birthDate, const Date& violationDate) {
//    int age = violationDate.year - birthDate.year;
//    if (violationDate.month < birthDate.month ||
//        (violationDate.month == birthDate.month && violationDate.day < birthDate.day)) {
//        age--;
//    }
//    return age;
//}
//
//bool UserInterface::isDriverAdult(const std::string& birthDateStr,
//    const std::string& violationDateStr)
//{
//    Date bDate, vDate;
//    if (!parseDate(birthDateStr, bDate) || !parseDate(violationDateStr, vDate)) return false;
//    if (!isDateValid(bDate) || !isDateValid(vDate)) return false;
//    int age = calculateAge(bDate, vDate);
//    return (age >= 18 && age <= 100);
//}
//
//// ======= Сортировка статистики по городам =======
//int UserInterface::compareCityStats(const void* a, const void* b) {
//    const CityViolations* ca = static_cast<const CityViolations*>(a);
//    const CityViolations* cb = static_cast<const CityViolations*>(b);
//    return cb->count - ca->count;
//}
//
//void UserInterface::printCityViolations(CityViolations* stats, int cityCount) {
//    cout << "+----------------------+------------+------+--------+\n";
//    cout << "| City                 | Count      | Date | Paid   |\n";
//    cout << "+----------------------+------------+------+--------+\n";
//    for (int i = 0; i < cityCount; ++i) {
//        for (int j = 0; j < stats[i].count; ++j) {
//            auto vi = dbManager.getRegistry().getViolationById(
//                stats[i].violationIds[j],
//                dbManager.getDrivers(),
//                dbManager.getCities(),
//                dbManager.getFines()
//            );
//            ostringstream oss;
//            oss << "| " << left << setw(20) << stats[i].name << " | "
//                << right << setw(10) << stats[i].count << " | "
//                << left << setw(4) << vi.date << " | "
//                << left << setw(6) << (vi.paid ? "Yes" : "No") << " |";
//            cout << oss.str() << "\n";
//        }
//    }
//    cout << "+----------------------+------------+------+--------+\n";
//}
//
//void UserInterface::showTopDrivers() {
//    cout << "\nTop-5 drivers by violation count:\n";
//    auto violations = dbManager.getAllViolations();
//    map<std::string, int> countMap;
//    for (auto& v : violations) {
//        countMap[v.driverName]++;
//    }
//    vector<pair<std::string, int>> vec(countMap.begin(), countMap.end());
//    sort(vec.begin(), vec.end(), [](auto& a, auto& b) { return a.second > b.second; });
//    for (size_t i = 0; i < vec.size() && i < 5; ++i) {
//        cout << vec[i].first << ": " << vec[i].second << "\n";
//    }
//}
//
//// ======= Меню и операции =======
//void UserInterface::run() {
//    setlocale(LC_ALL, "");
//    dbManager.loadAll();
//    while (true) {
//        mainMenu();
//    }
//}
//
//void UserInterface::mainMenu() {
//    cout << "\n=== Main Menu ===\n";
//    cout << "1. Manage Cities\n";
//    cout << "2. Manage Drivers\n";
//    cout << "3. Manage Fines\n";
//    cout << "4. Manage Violations\n";
//    cout << "5. Statistics\n";
//    cout << "6. Exit\n";
//    int choice = readInt("Choose option: ");
//    switch (choice) {
//    case 1: citiesMenu();   break;
//    case 2: driversMenu();  break;
//    case 3: finesMenu();    break;
//    case 4: registryMenu(); break;
//    case 5: statisticsMenu(); break;
//    case 6: dbManager.saveAll(); exit(0);
//    default: cout << "Invalid choice. Try again.\n";
//    }
//}
//
//// ==================== Cities ====================
//void UserInterface::citiesMenu() {
//    cout << "\n--- Cities ---\n";
//    cout << "1. List Cities\n";
//    cout << "2. Add City\n";
//    cout << "3. Delete City\n";
//    cout << "4. Filter Cities\n";
//    cout << "5. Clear City Filters\n";
//    cout << "6. Edit City\n";
//    cout << "7. Back\n";
//    int choice = readInt("Choose option: ");
//    switch (choice) {
//    case 1: listCities();       break;
//    case 2: addCity();          break;
//    case 3: deleteCity();       break;
//    case 4: filterCities();     break;
//    case 5: clearCityFilters(); break;
//    case 6: editCity();         break;
//    case 7: return;
//    default: cout << "Invalid choice.\n";
//    }
//}
//
//void UserInterface::listCities() {
//    CityTable& cities = dbManager.getCities();
//    CityTable::CityNode* filteredHead = cities.applyFilters();
//    cities.cityIteratorReset(filteredHead);
//
//    cout << "+----------------------+------------+------------+\n";
//    cout << "| Name                 | Population | Type       |\n";
//    cout << "+----------------------+------------+------------+\n";
//    while (cities.cityIteratorHasNext()) {
//        auto ci = cities.cityIteratorNext();
//        ostringstream oss;
//        oss << "| " << left << setw(20) << ci.name << " | "
//            << right << setw(10) << ci.population << " | "
//            << left << setw(10) << CityTable::settlementTypeToString(ci.type) << " |";
//        cout << oss.str() << "\n";
//    }
//    cout << "+----------------------+------------+------------+\n";
//
//    CityTable::CityNode* tmp = filteredHead;
//    while (tmp) {
//        CityTable::CityNode* nxt = tmp->next;
//        delete tmp;
//        tmp = nxt;
//    }
//}
//
//void UserInterface::addCity() {
//    string name = readString("City name: ");
//    int population = readInt("Population: ");
//    cout << "Population grade (0-Small, 1-Medium, 2-Large): ";
//    int gradeInput = readInt("");
//    auto grade = static_cast<CityTable::PopulationGrade>(gradeInput);
//
//    cout << "Settlement type (0-City, 1-Town, 2-Village): ";
//    int typeInput = readInt("");
//    auto type = static_cast<CityTable::SettlementType>(typeInput);
//
//    dbManager.addCity(name, population, grade, type);
//    cout << "City added.\n";
//}
//
//void UserInterface::deleteCity() {
//    string name = readString("City name to delete: ");
//    dbManager.deleteCity(name);
//    cout << "City deleted (if it existed).\n";
//}
//
//void UserInterface::filterCities() {
//    CityTable& cities = dbManager.getCities();
//    cout << "\nFilter by:\n";
//    cout << "1. Name contains\n";
//    cout << "2. Name equals\n";
//    cout << "3. Population <\n";
//    cout << "4. Population >\n";
//    cout << "5. Population equals\n";
//    cout << "6. Type equals\n";
//    cout << "7. Cancel\n";
//    int choice = readInt("Choose filter type: ");
//    if (choice == 7) return;
//    if (choice == 1) {
//        string val = readString("Enter substring: ");
//        cities.addFilter("name", 1, val);
//    }
//    else if (choice == 2) {
//        string val = readString("Enter full name: ");
//        cities.addFilter("name", 2, val);
//    }
//    else if (choice == 3) {
//        string val = readString("Enter threshold: ");
//        cities.addFilter("population", 3, val);
//    }
//    else if (choice == 4) {
//        string val = readString("Enter threshold: ");
//        cities.addFilter("population", 4, val);
//    }
//    else if (choice == 5) {
//        string val = readString("Enter exact value: ");
//        cities.addFilter("population", 2, val);
//    }
//    else if (choice == 6) {
//        cout << "Type options: City, Town, Village\n";
//        string val = readString("Enter type: ");
//        cities.addFilter("type", 2, val);
//    }
//    else {
//        cout << "Invalid option.\n";
//        return;
//    }
//    cout << "Filter added.\n";
//}
//
//void UserInterface::clearCityFilters() {
//    dbManager.getCities().clearFilters();
//    cout << "All city filters cleared.\n";
//}
//
//void UserInterface::editCity() {
//    listCities();
//    string name = readString("Enter City name to edit: ");
//    CityTable& cities = dbManager.getCities();
//    int id = cities.getCityIdByName(name);
//    if (id == -1) {
//        cout << "City not found.\n";
//        return;
//    }
//    cout << "\nEdit field:\n";
//    cout << "1. Name\n";
//    cout << "2. Population\n";
//    cout << "3. Grade\n";
//    cout << "4. Type\n";
//    cout << "5. Cancel\n";
//    int choice = readInt("Choose field: ");
//    if (choice == 1) {
//        string newName = readString("Enter new name: ");
//        if (cities.updateCityName(id, newName))
//            cout << "Name updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else if (choice == 2) {
//        int newPop = readInt("Enter new population: ");
//        if (cities.updateCityPopulation(id, newPop))
//            cout << "Population updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else if (choice == 3) {
//        cout << "Grades: 0-Small, 1-Medium, 2-Large\n";
//        int g = readInt("Choose grade: ");
//        if (cities.updateCityGrade(id, static_cast<CityTable::PopulationGrade>(g)))
//            cout << "Grade updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else if (choice == 4) {
//        cout << "Types: 0-City, 1-Town, 2-Village\n";
//        int t = readInt("Choose type: ");
//        if (cities.updateCityType(id, static_cast<CityTable::SettlementType>(t)))
//            cout << "Type updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else {
//        cout << "Cancel.\n";
//    }
//}
//
//// ==================== Drivers ====================
//void UserInterface::driversMenu() {
//    cout << "\n--- Drivers ---\n";
//    cout << "1. List Drivers\n";
//    cout << "2. Add Driver\n";
//    cout << "3. Delete Driver\n";
//    cout << "4. Edit Driver\n";
//    cout << "5. Back\n";
//    int choice = readInt("Choose option: ");
//    switch (choice) {
//    case 1: listDrivers(); break;
//    case 2: addDriver();   break;
//    case 3: deleteDriver(); break;
//    case 4: editDriver();  break;
//    case 5: return;
//    default: cout << "Invalid choice.\n";
//    }
//}
//
//void UserInterface::listDrivers() {
//    auto& drivers = dbManager.getDrivers();
//    drivers.driverIteratorReset();
//    cout << "+------------------------------+------------+----------------------+\n";
//    cout << "| Full Name                    | Birth Date | City                 |\n";
//    cout << "+------------------------------+------------+----------------------+\n";
//    while (drivers.driverIteratorHasNext()) {
//        auto di = drivers.driverIteratorNext();
//        string cityName = dbManager.getCities().getCityNameById(di.cityId);
//        ostringstream oss;
//        oss << "| " << left << setw(28) << di.fullName << " | "
//            << left << setw(10) << di.birthDate << " | "
//            << left << setw(20) << cityName << " |";
//        cout << oss.str() << "\n";
//    }
//    cout << "+------------------------------+------------+----------------------+\n";
//}
//
//void UserInterface::addDriver() {
//    string fullName = readString("Full name: ");
//    string birthDate = readString("Birth date (DD.MM.YYYY): ");
//    string cityName = readString("City: ");
//    try {
//        dbManager.addDriver(fullName, birthDate, cityName);
//        cout << "Driver added.\n";
//    }
//    catch (const exception& e) {
//        cout << "Error: " << e.what() << "\n";
//    }
//}
//
//void UserInterface::deleteDriver() {
//    string name = readString("Full name to delete: ");
//    dbManager.deleteDriver(name);
//    cout << "Driver deleted (if existed).\n";
//}
//
//void UserInterface::editDriver() {
//    listDrivers();
//    string name = readString("Enter Driver full name to edit: ");
//    auto& drivers = dbManager.getDrivers();
//    int id = drivers.getDriverId(name);
//    if (id == -1) {
//        cout << "Driver not found.\n";
//        return;
//    }
//    cout << "\nEdit field:\n";
//    cout << "1. Full Name\n";
//    cout << "2. Birth Date\n";
//    cout << "3. City\n";
//    cout << "4. Cancel\n";
//    int choice = readInt("Choose field: ");
//    if (choice == 1) {
//        string newName = readString("Enter new name: ");
//        if (drivers.updateDriverName(id, newName))
//            cout << "Name updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else if (choice == 2) {
//        string newDate = readString("Enter new birth date (DD.MM.YYYY): ");
//        if (drivers.updateDriverBirthDate(id, newDate))
//            cout << "Birth date updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else if (choice == 3) {
//        string newCity = readString("Enter new city: ");
//        int newCityId = dbManager.getCities().getCityIdByName(newCity);
//        if (newCityId == -1) {
//            cout << "City not found.\n";
//        }
//        else if (drivers.updateDriverCity(id, newCityId))
//            cout << "City updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else {
//        cout << "Cancel.\n";
//    }
//}
//
//// ==================== Fines ====================
//void UserInterface::finesMenu() {
//    cout << "\n--- Fines ---\n";
//    cout << "1. List Fines\n";
//    cout << "2. Add Fine\n";
//    cout << "3. Delete Fine\n";
//    cout << "4. Edit Fine\n";
//    cout << "5. Back\n";
//    int choice = readInt("Choose option: ");
//    switch (choice) {
//    case 1: listFines(); break;
//    case 2: addFine();   break;
//    case 3: deleteFine(); break;
//    case 4: editFine();  break;
//    case 5: return;
//    default: cout << "Invalid choice.\n";
//    }
//}
//
//void UserInterface::listFines() {
//    auto& fines = dbManager.getFines();
//    fines.fineIteratorReset();
//    cout << "+------------+------------------------------+----------+\n";
//    cout << "| Amount     | Type                         | Severity |\n";
//    cout << "+------------+------------------------------+----------+\n";
//    while (fines.fineIteratorHasNext()) {
//        auto fi = fines.fineIteratorNext();
//        ostringstream oss;
//        oss << "| " << right << setw(10) << fi.amount << " | "
//            << left << setw(28) << fi.type << " | "
//            << left << setw(8) << FineTable::severityToString(fi.severity) << " |";
//        cout << oss.str() << "\n";
//    }
//    cout << "+------------+------------------------------+----------+\n";
//}
//
//void UserInterface::addFine() {
//    string type = readString("Fine type: ");
//    double amount = readDouble("Amount: ");
//    cout << "Severity (0-Light, 1-Medium, 2-Heavy): ";
//    int s = readInt("");
//    try {
//        dbManager.addFine(type, amount, static_cast<FineTable::Severity>(s));
//        cout << "Fine added.\n";
//    }
//    catch (const exception& e) {
//        cout << "Error: " << e.what() << "\n";
//    }
//}
//
//void UserInterface::deleteFine() {
//    string type = readString("Fine type to delete: ");
//    dbManager.getFines().deleteFine(type);
//    cout << "Fine deleted (if existed).\n";
//}
//
//void UserInterface::editFine() {
//    listFines();
//    string type = readString("Enter Fine type to edit: ");
//    auto& fines = dbManager.getFines();
//    int id = fines.getFineIdByType(type);
//    if (id == -1) {
//        cout << "Fine not found.\n";
//        return;
//    }
//    cout << "\nEdit field:\n";
//    cout << "1. Type\n";
//    cout << "2. Amount\n";
//    cout << "3. Severity\n";
//    cout << "4. Cancel\n";
//    int choice = readInt("Choose field: ");
//    if (choice == 1) {
//        string newType = readString("Enter new type: ");
//        if (fines.updateFineType(id, newType))
//            cout << "Type updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else if (choice == 2) {
//        double newAmt = readDouble("Enter new amount: ");
//        if (fines.updateFineAmount(id, newAmt))
//            cout << "Amount updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else if (choice == 3) {
//        cout << "Severity (0-Light, 1-Medium, 2-Heavy): ";
//        int snew = readInt("");
//        if (fines.updateFineSeverity(id, static_cast<FineTable::Severity>(snew)))
//            cout << "Severity updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else {
//        cout << "Cancel.\n";
//    }
//}
//
//// ==================== Violations ====================
//void UserInterface::registryMenu() {
//    cout << "\n--- Violations ---\n";
//    cout << "1. List Violations\n";
//    cout << "2. Add Violation\n";
//    cout << "3. Mark Paid\n";
//    cout << "4. Edit Violation\n";
//    cout << "5. Back\n";
//    int choice = readInt("Choose option: ");
//    switch (choice) {
//    case 1: listViolations(); break;
//    case 2: addViolation();   break;
//    case 3: markViolationPaid(); break;
//    case 4: editViolation();  break;
//    case 5: return;
//    default: cout << "Invalid choice.\n";
//    }
//}
//
//void UserInterface::listViolations() {
//    auto violations = dbManager.getAllViolations();
//    cout << "+------------------------------+----------------+----------------+------------+------+----------+\n";
//    cout << "| Driver                       | City           | Fine           | Date       | Paid | Amount   |\n";
//    cout << "+------------------------------+----------------+----------------+------------+------+----------+\n";
//    for (auto& v : violations) {
//        ostringstream oss;
//        oss << "| " << left << setw(28) << v.driverName << " | "
//            << left << setw(14) << v.cityName << " | "
//            << left << setw(14) << v.fineType << " | "
//            << left << setw(10) << v.date << " | "
//            << left << setw(4) << (v.paid ? "Yes" : "No") << " | "
//            << right << setw(6) << v.fineAmount << " |";
//        cout << oss.str() << "\n";
//    }
//    cout << "+------------------------------+----------------+----------------+------------+------+----------+\n";
//}
//
//void UserInterface::addViolation() {
//    listDrivers();
//    string driverName = readString("Driver full name: ");
//    listFines();
//    string fineType = readString("Fine type: ");
//    string date = readString("Date (DD.MM.YYYY): ");
//    try {
//        dbManager.addViolation(driverName, fineType, date);
//        cout << "Violation added.\n";
//    }
//    catch (const exception& e) {
//        cout << "Error: " << e.what() << "\n";
//    }
//}
//
//void UserInterface::markViolationPaid() {
//    string date = readString("Enter violation date to mark paid: ");
//    string driverName = readString("Enter driver full name: ");
//    string fineType = readString("Enter fine type: ");
//    auto violations = dbManager.getAllViolations();
//    bool found = false;
//    for (auto& v : violations) {
//        if (v.driverName == driverName && v.fineType == fineType && v.date == date && !v.paid) {
//            dbManager.markFineAsPaid(v.recordId);
//            found = true;
//        }
//    }
//    if (found) {
//        cout << "Violation(s) marked paid.\n";
//    }
//    else {
//        cout << "No unpaid violation found matching criteria.\n";
//    }
//}
//
//void UserInterface::editViolation() {
//    listViolations();
//    cout << "Enter existing violation details to edit.\n";
//    string driverName = readString("Current driver full name: ");
//    string cityName = readString("Current city name: ");
//    string fineType = readString("Current fine type: ");
//    string date = readString("Current date (DD.MM.YYYY): ");
//
//    auto violations = dbManager.getAllViolations();
//    FineRegistry::ViolationInfo target{};
//    bool found = false;
//    for (auto& v : violations) {
//        if (v.driverName == driverName && v.cityName == cityName && v.fineType == fineType && v.date == date) {
//            target = v;
//            found = true;
//            break;
//        }
//    }
//    if (!found) {
//        cout << "Violation not found.\n";
//        return;
//    }
//
//    cout << "\nEdit field:\n";
//    cout << "1. Driver\n";
//    cout << "2. City\n";
//    cout << "3. Fine\n";
//    cout << "4. Date\n";
//    cout << "5. Paid/Unpaid\n";
//    cout << "6. Cancel\n";
//    int choice = readInt("Choose field: ");
//    if (choice == 1) {
//        string newDriver = readString("Enter new driver full name: ");
//        int newDriverId = dbManager.getDrivers().getDriverId(newDriver);
//        if (newDriverId == -1) {
//            cout << "Driver not found.\n";
//        }
//        else {
//            dbManager.getRegistry().updateDriverReferences(target.driverId);
//            dbManager.getRegistry().addViolation(newDriverId, target.cityId, target.fineId, target.date);
//            cout << "Driver updated.\n";
//        }
//    }
//    else if (choice == 2) {
//        string newCity = readString("Enter new city name: ");
//        int newCityId = dbManager.getCities().getCityIdByName(newCity);
//        if (newCityId == -1) {
//            cout << "City not found.\n";
//        }
//        else {
//            dbManager.getRegistry().updateCityReferences(target.cityId);
//            dbManager.getRegistry().updateViolationsCity(target.driverId, newCityId);
//            cout << "City updated.\n";
//        }
//    }
//    else if (choice == 3) {
//        string newFine = readString("Enter new fine type: ");
//        int newFineId = dbManager.getFines().getFineIdByType(newFine);
//        if (newFineId == -1) {
//            cout << "Fine not found.\n";
//        }
//        else {
//            dbManager.getRegistry().addViolation(target.driverId, target.cityId, newFineId, target.date);
//            cout << "Fine updated.\n";
//        }
//    }
//    else if (choice == 4) {
//        string newDate = readString("Enter new date (DD.MM.YYYY): ");
//        dbManager.getRegistry().addViolation(target.driverId, target.cityId, target.fineId, newDate);
//        cout << "Date updated.\n";
//    }
//    else if (choice == 5) {
//        if (target.paid) {
//            cout << "Cannot unset paid.\n";
//        }
//        else {
//            dbManager.getRegistry().markAsPaid(target.recordId);
//            cout << "Now marked as paid.\n";
//        }
//    }
//    else {
//        cout << "Cancel.\n";
//    }
//}
//
//// ==================== Statistics ====================
//void UserInterface::statisticsMenu() {
//    cout << "\n--- Statistics ---\n";
//    cout << "1. Violations by City\n";
//    cout << "2. Top-5 Drivers\n";
//    cout << "3. Back\n";
//    int choice = readInt("Choose option: ");
//    switch (choice) {
//    case 1: showViolationsByCity(); break;
//    case 2: showTopDrivers();       break;
//    case 3: return;
//    default: cout << "Invalid choice.\n";
//    }
//}
//
//void UserInterface::showViolationsByCity() {
//    CityViolations stats[MAX_CITIES];
//    int cityCount = 0;
//    collectCityStats(stats, cityCount);
//    if (cityCount == 0) {
//        cout << "No cities with violations.\n";
//        return;
//    }
//    qsort(stats, cityCount, sizeof(CityViolations), compareCityStats);
//    printCityViolations(stats, cityCount);
//}
//
//void UserInterface::collectCityStats(CityViolations* stats, int& cityCount) {
//    cityCount = 0;
//    auto violations = dbManager.getAllViolations();
//    for (auto& v : violations) {
//        int idx = -1;
//        for (int i = 0; i < cityCount; ++i) {
//            if (stats[i].name == v.cityName) {
//                idx = i;
//                break;
//            }
//        }
//        if (idx == -1) {
//            idx = cityCount++;
//            stats[idx].name = v.cityName;
//        }
//        stats[idx].violationIds[stats[idx].count++] = v.recordId;
//    }
//}
//
//// ======= Ввод =======
//int UserInterface::readInt(const std::string& prompt) {
//    int value;
//    while (true) {
//        cout << prompt;
//        if (cin >> value) {
//            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
//            return value;
//        }
//        cout << "Invalid input. Enter a number.\n";
//        cin.clear();
//        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
//    }
//}
//
//double UserInterface::readDouble(const std::string& prompt) {
//    double value;
//    while (true) {
//        cout << prompt;
//        if (cin >> value) {
//            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
//            return value;
//        }
//        cout << "Invalid input. Enter a number.\n";
//        cin.clear();
//        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
//    }
//}
//
//std::string UserInterface::readString(const std::string& prompt) {
//    std::string value;
//    cout << prompt;
//    std::getline(cin, value);
//    return value;
//}


//// UserInterface.cpp
//#include "UserInterface.h"
//#include <iostream>
//#include <limits>
//#include <sstream>
//#include <algorithm>
//#include <clocale>
//#include <iomanip>
//using namespace std;
//
//// ======= Вспомогательные методы для работы с датами =======
//bool UserInterface::parseDate(const std::string& dateStr, Date& date) {
//    if (dateStr.size() != 10 || dateStr[2] != '.' || dateStr[5] != '.') return false;
//    try {
//        date.day = stoi(dateStr.substr(0, 2));
//        date.month = stoi(dateStr.substr(3, 2));
//        date.year = stoi(dateStr.substr(6, 4));
//    }
//    catch (...) {
//        return false;
//    }
//    return true;
//}
//
//bool UserInterface::isDateValid(const Date& date) {
//    if (date.year < 1900 || date.year > 2100) return false;
//    if (date.month < 1 || date.month > 12) return false;
//    if (date.day < 1 || date.day > 31) return false;
//    static const int mdays[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
//    int maxDay = mdays[date.month];
//    if (date.month == 2) {
//        if ((date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0)) {
//            maxDay = 29;
//        }
//    }
//    return date.day <= maxDay;
//}
//
//int UserInterface::calculateAge(const Date& birthDate, const Date& violationDate) {
//    int age = violationDate.year - birthDate.year;
//    if (violationDate.month < birthDate.month ||
//        (violationDate.month == birthDate.month && violationDate.day < birthDate.day)) {
//        age--;
//    }
//    return age;
//}
//
//bool UserInterface::isDriverAdult(const std::string& birthDateStr,
//    const std::string& violationDateStr)
//{
//    Date bDate, vDate;
//    if (!parseDate(birthDateStr, bDate) || !parseDate(violationDateStr, vDate)) return false;
//    if (!isDateValid(bDate) || !isDateValid(vDate)) return false;
//    int age = calculateAge(bDate, vDate);
//    return (age >= 18 && age <= 100);
//}
//
//// ======= Сортировка статистики по городам =======
//int UserInterface::compareCityStats(const void* a, const void* b) {
//    const CityViolations* ca = static_cast<const CityViolations*>(a);
//    const CityViolations* cb = static_cast<const CityViolations*>(b);
//    return cb->count - ca->count; // по убыванию
//}
//
//void UserInterface::printCityViolations(CityViolations* stats, int cityCount) {
//    cout << "+----------------------+------------+------------+------------+\n";
//    cout << "| City                 | Population | Type       | Grade      |\n";
//    cout << "+----------------------+------------+------------+------------+\n";
//    for (int i = 0; i < cityCount; ++i) {
//        // Выводим строку заголовка для города
//        ostringstream oss;
//        oss << "| " << left << setw(20) << stats[i].name << " | "
//            << right << setw(10) << stats[i].count << " | "
//            << left << setw(10) << "" << " | "
//            << left << setw(10) << "" << " |";
//        cout << oss.str() << "\n";
//        // Здесь можно детально выводить все нарушения, если нужно
//    }
//    cout << "+----------------------+------------+------------+------------+\n";
//}
//
//void UserInterface::showTopDrivers() {
//    cout << "\nTop-5 drivers by violation count:\n";
//    auto violations = dbManager.getAllViolations();
//    map<std::string, int> countMap;
//    for (auto& v : violations) {
//        countMap[v.driverName]++;
//    }
//    vector<pair<std::string, int>> vec(countMap.begin(), countMap.end());
//    sort(vec.begin(), vec.end(), [](auto& a, auto& b) { return a.second > b.second; });
//    for (size_t i = 0; i < vec.size() && i < 5; ++i) {
//        cout << vec[i].first << ": " << vec[i].second << "\n";
//    }
//}
//
//// ======= Меню и операции =======
//void UserInterface::run() {
//    setlocale(LC_ALL, "");
//    dbManager.loadAll();
//    while (true) {
//        mainMenu();
//    }
//}
//
//void UserInterface::mainMenu() {
//    cout << "\n=== Main Menu ===\n";
//    cout << "1. Manage Cities\n";
//    cout << "2. Manage Drivers\n";
//    cout << "3. Manage Fines\n";
//    cout << "4. Manage Violations\n";
//    cout << "5. Statistics\n";
//    cout << "6. Exit\n";
//    int choice = readInt("Choose option: ");
//    switch (choice) {
//    case 1: citiesMenu();   break;
//    case 2: driversMenu();  break;
//    case 3: finesMenu();    break;
//    case 4: registryMenu(); break;
//    case 5: statisticsMenu(); break;
//    case 6: dbManager.saveAll(); exit(0);
//    default: cout << "Invalid choice. Try again.\n";
//    }
//}
//
//// ==================== Cities ====================
//void UserInterface::citiesMenu() {
//    cout << "\n--- Cities ---\n";
//    cout << "1. List Cities\n";
//    cout << "2. Add City\n";
//    cout << "3. Delete City\n";
//    cout << "4. Filter Cities\n";
//    cout << "5. Remove Specific Filters\n";
//    cout << "6. Clear All Filters\n";
//    cout << "7. Edit City\n";
//    cout << "8. Back\n";
//    int choice = readInt("Choose option: ");
//    switch (choice) {
//    case 1: listCities();       break;
//    case 2: addCity();          break;
//    case 3: deleteCity();       break;
//    case 4: filterCities();     break;
//    case 5: removeCityFilters(); break;
//    case 6: clearCityFilters(); break;
//    case 7: editCity();         break;
//    case 8: return;
//    default: cout << "Invalid choice.\n";
//    }
//}
//
//void UserInterface::listCities() {
//    CityTable& cities = dbManager.getCities();
//    CityTable::CityNode* filteredHead = cities.applyFilters();
//    cities.cityIteratorReset(filteredHead);
//
//    cout << "+----------------------+------------+------------+------------+\n";
//    cout << "| Name                 | Population | Type       | Grade      |\n";
//    cout << "+----------------------+------------+------------+------------+\n";
//    while (cities.cityIteratorHasNext()) {
//        auto ci = cities.cityIteratorNext();
//        ostringstream oss;
//        oss << "| " << left << setw(20) << ci.name << " | "
//            << right << setw(10) << ci.population << " | "
//            << left << setw(10) << CityTable::settlementTypeToString(ci.type) << " | "
//            << left << setw(10) << CityTable::populationGradeToString(ci.grade) << " |";
//        cout << oss.str() << "\n";
//    }
//    cout << "+----------------------+------------+------------+------------+\n";
//
//    // Очистка клонированного списка
//    CityTable::CityNode* tmp = filteredHead;
//    while (tmp) {
//        CityTable::CityNode* nxt = tmp->next;
//        delete tmp;
//        tmp = nxt;
//    }
//}
//
//void UserInterface::addCity() {
//    string name = readString("City name: ");
//    int population = readInt("Population: ");
//    cout << "Population grade (0-Small, 1-Medium, 2-Large): ";
//    int gradeInput = readInt("");
//    auto grade = static_cast<CityTable::PopulationGrade>(gradeInput);
//
//    cout << "Settlement type (0-City, 1-Town, 2-Village): ";
//    int typeInput = readInt("");
//    auto type = static_cast<CityTable::SettlementType>(typeInput);
//
//    dbManager.addCity(name, population, grade, type);
//    cout << "City added.\n";
//}
//
//void UserInterface::deleteCity() {
//    string name = readString("City name to delete: ");
//    dbManager.deleteCity(name);
//    cout << "City deleted (if it existed).\n";
//}
//
//void UserInterface::filterCities() {
//    CityTable& cities = dbManager.getCities();
//    cout << "\nFilter by:\n";
//    cout << "1. Name contains\n";
//    cout << "2. Name equals\n";
//    cout << "3. Population <\n";
//    cout << "4. Population >\n";
//    cout << "5. Population equals\n";
//    cout << "6. Type equals\n";
//    cout << "7. Cancel\n";
//    int choice = readInt("Choose filter type: ");
//    if (choice == 7) return;
//    if (choice == 1) {
//        string val = readString("Enter substring: ");
//        cities.addFilter("name", 1, val);
//    }
//    else if (choice == 2) {
//        string val = readString("Enter full name: ");
//        cities.addFilter("name", 2, val);
//    }
//    else if (choice == 3) {
//        string val = readString("Enter threshold: ");
//        cities.addFilter("population", 3, val);
//    }
//    else if (choice == 4) {
//        string val = readString("Enter threshold: ");
//        cities.addFilter("population", 4, val);
//    }
//    else if (choice == 5) {
//        string val = readString("Enter exact value: ");
//        cities.addFilter("population", 2, val);
//    }
//    else if (choice == 6) {
//        cout << "Type options: City, Town, Village\n";
//        string val = readString("Enter type: ");
//        cities.addFilter("type", 2, val);
//    }
//    else {
//        cout << "Invalid option.\n";
//        return;
//    }
//    cout << "Filter added.\n";
//}
//
//void UserInterface::removeCityFilters() {
//    CityTable& cities = dbManager.getCities();
//    int count = cities.getFilterCount();
//    if (count == 0) {
//        cout << "No active filters to remove.\n";
//        return;
//    }
//    while (true) {
//        cout << "\nActive Filters:\n";
//        for (int i = 0; i < count; ++i) {
//            cout << i + 1 << ". " << cities.getFilterDescription(i) << "\n";
//        }
//        cout << "0. Done removing\n";
//        int choice = readInt("Choose filter number to remove (or 0 to finish): ");
//        if (choice == 0) break;
//        if (choice < 1 || choice > count) {
//            cout << "Invalid choice.\n";
//        }
//        else {
//            cities.removeFilterAt(choice - 1);
//            cout << "Filter removed.\n";
//            count = cities.getFilterCount();
//            if (count == 0) {
//                cout << "No more filters remaining.\n";
//                break;
//            }
//        }
//    }
//}
//
//void UserInterface::clearCityFilters() {
//    dbManager.getCities().clearFilters();
//    cout << "All city filters cleared.\n";
//}
//
//void UserInterface::editCity() {
//    listCities();
//    string name = readString("Enter City name to edit: ");
//    CityTable& cities = dbManager.getCities();
//    int id = cities.getCityIdByName(name);
//    if (id == -1) {
//        cout << "City not found.\n";
//        return;
//    }
//    cout << "\nEdit field:\n";
//    cout << "1. Name\n";
//    cout << "2. Population\n";
//    cout << "3. Grade\n";
//    cout << "4. Type\n";
//    cout << "5. Cancel\n";
//    int choice = readInt("Choose field: ");
//    if (choice == 1) {
//        string newName = readString("Enter new name: ");
//        if (cities.updateCityName(id, newName))
//            cout << "Name updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else if (choice == 2) {
//        int newPop = readInt("Enter new population: ");
//        if (cities.updateCityPopulation(id, newPop))
//            cout << "Population updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else if (choice == 3) {
//        cout << "Grades: 0-Small, 1-Medium, 2-Large\n";
//        int g = readInt("Choose grade: ");
//        if (cities.updateCityGrade(id, static_cast<CityTable::PopulationGrade>(g)))
//            cout << "Grade updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else if (choice == 4) {
//        cout << "Types: 0-City, 1-Town, 2-Village\n";
//        int t = readInt("Choose type: ");
//        if (cities.updateCityType(id, static_cast<CityTable::SettlementType>(t)))
//            cout << "Type updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else {
//        cout << "Cancel.\n";
//    }
//}
//
//// ==================== Drivers ====================
//void UserInterface::driversMenu() {
//    cout << "\n--- Drivers ---\n";
//    cout << "1. List Drivers\n";
//    cout << "2. Add Driver\n";
//    cout << "3. Delete Driver\n";
//    cout << "4. Edit Driver\n";
//    cout << "5. Back\n";
//    int choice = readInt("Choose option: ");
//    switch (choice) {
//    case 1: listDrivers();  break;
//    case 2: addDriver();    break;
//    case 3: deleteDriver(); break;
//    case 4: editDriver();   break;
//    case 5: return;
//    default: cout << "Invalid choice.\n";
//    }
//}
//
//void UserInterface::listDrivers() {
//    auto& drivers = dbManager.getDrivers();
//    drivers.driverIteratorReset();
//    cout << "+------------------------------+------------+----------------------+\n";
//    cout << "| Full Name                    | Birth Date | City                 |\n";
//    cout << "+------------------------------+------------+----------------------+\n";
//    while (drivers.driverIteratorHasNext()) {
//        auto di = drivers.driverIteratorNext();
//        string cityName = dbManager.getCities().getCityNameById(di.cityId);
//        ostringstream oss;
//        oss << "| " << left << setw(28) << di.fullName << " | "
//            << left << setw(10) << di.birthDate << " | "
//            << left << setw(20) << cityName << " |";
//        cout << oss.str() << "\n";
//    }
//    cout << "+------------------------------+------------+----------------------+\n";
//}
//
//void UserInterface::addDriver() {
//    string fullName = readString("Full name: ");
//    string birthDate = readString("Birth date (DD.MM.YYYY): ");
//    string cityName = readString("City: ");
//    try {
//        dbManager.addDriver(fullName, birthDate, cityName);
//        cout << "Driver added.\n";
//    }
//    catch (const exception& e) {
//        cout << "Error: " << e.what() << "\n";
//    }
//}
//
//void UserInterface::deleteDriver() {
//    string name = readString("Full name to delete: ");
//    dbManager.deleteDriver(name);
//    cout << "Driver deleted (if existed).\n";
//}
//
//void UserInterface::editDriver() {
//    listDrivers();
//    string name = readString("Enter Driver full name to edit: ");
//    auto& drivers = dbManager.getDrivers();
//    int id = drivers.getDriverId(name);
//    if (id == -1) {
//        cout << "Driver not found.\n";
//        return;
//    }
//    cout << "\nEdit field:\n";
//    cout << "1. Full Name\n";
//    cout << "2. Birth Date\n";
//    cout << "3. City\n";
//    cout << "4. Cancel\n";
//    int choice = readInt("Choose field: ");
//    if (choice == 1) {
//        string newName = readString("Enter new name: ");
//        if (drivers.updateDriverName(id, newName))
//            cout << "Name updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else if (choice == 2) {
//        string newDate = readString("Enter new birth date (DD.MM.YYYY): ");
//        if (drivers.updateDriverBirthDate(id, newDate))
//            cout << "Birth date updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else if (choice == 3) {
//        string newCity = readString("Enter new city: ");
//        int newCityId = dbManager.getCities().getCityIdByName(newCity);
//        if (newCityId == -1) {
//            cout << "City not found.\n";
//        }
//        else if (drivers.updateDriverCity(id, newCityId))
//            cout << "City updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else {
//        cout << "Cancel.\n";
//    }
//}
//
//// ==================== Fines ====================
//void UserInterface::finesMenu() {
//    cout << "\n--- Fines ---\n";
//    cout << "1. List Fines\n";
//    cout << "2. Add Fine\n";
//    cout << "3. Delete Fine\n";
//    cout << "4. Edit Fine\n";
//    cout << "5. Back\n";
//    int choice = readInt("Choose option: ");
//    switch (choice) {
//    case 1: listFines();   break;
//    case 2: addFine();     break;
//    case 3: deleteFine();  break;
//    case 4: editFine();    break;
//    case 5: return;
//    default: cout << "Invalid choice.\n";
//    }
//}
//
//void UserInterface::listFines() {
//    auto& fines = dbManager.getFines();
//    fines.fineIteratorReset();
//    cout << "+------------+------------------------------+----------+\n";
//    cout << "| Amount     | Type                         | Severity |\n";
//    cout << "+------------+------------------------------+----------+\n";
//    while (fines.fineIteratorHasNext()) {
//        auto fi = fines.fineIteratorNext();
//        ostringstream oss;
//        oss << "| " << right << setw(10) << fi.amount << " | "
//            << left << setw(28) << fi.type << " | "
//            << left << setw(8) << FineTable::severityToString(fi.severity) << " |";
//        cout << oss.str() << "\n";
//    }
//    cout << "+------------+------------------------------+----------+\n";
//}
//
//void UserInterface::addFine() {
//    string type = readString("Fine type: ");
//    double amount = readDouble("Amount: ");
//    cout << "Severity (0-Light, 1-Medium, 2-Heavy): ";
//    int s = readInt("");
//    try {
//        dbManager.addFine(type, amount, static_cast<FineTable::Severity>(s));
//        cout << "Fine added.\n";
//    }
//    catch (const exception& e) {
//        cout << "Error: " << e.what() << "\n";
//    }
//}
//
//void UserInterface::deleteFine() {
//    string type = readString("Fine type to delete: ");
//    dbManager.getFines().deleteFine(type);
//    cout << "Fine deleted (if existed).\n";
//}
//
//void UserInterface::editFine() {
//    listFines();
//    string type = readString("Enter Fine type to edit: ");
//    auto& fines = dbManager.getFines();
//    int id = fines.getFineIdByType(type);
//    if (id == -1) {
//        cout << "Fine not found.\n";
//        return;
//    }
//    cout << "\nEdit field:\n";
//    cout << "1. Type\n";
//    cout << "2. Amount\n";
//    cout << "3. Severity\n";
//    cout << "4. Cancel\n";
//    int choice = readInt("Choose field: ");
//    if (choice == 1) {
//        string newType = readString("Enter new type: ");
//        if (fines.updateFineType(id, newType))
//            cout << "Type updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else if (choice == 2) {
//        double newAmt = readDouble("Enter new amount: ");
//        if (fines.updateFineAmount(id, newAmt))
//            cout << "Amount updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else if (choice == 3) {
//        cout << "Severity (0-Light, 1-Medium, 2-Heavy): ";
//        int snew = readInt("");
//        if (fines.updateFineSeverity(id, static_cast<FineTable::Severity>(snew)))
//            cout << "Severity updated.\n";
//        else
//            cout << "Update failed.\n";
//    }
//    else {
//        cout << "Cancel.\n";
//    }
//}
//
//// ==================== Violations ====================
//void UserInterface::registryMenu() {
//    cout << "\n--- Violations ---\n";
//    cout << "1. List Violations\n";
//    cout << "2. Add Violation\n";
//    cout << "3. Mark Paid\n";
//    cout << "4. Edit Violation\n";
//    cout << "5. Back\n";
//    int choice = readInt("Choose option: ");
//    switch (choice) {
//    case 1: listViolations();    break;
//    case 2: addViolation();      break;
//    case 3: markViolationPaid(); break;
//    case 4: editViolation();     break;
//    case 5: return;
//    default: cout << "Invalid choice.\n";
//    }
//}
//
//void UserInterface::listViolations() {
//    auto violations = dbManager.getAllViolations();
//    cout << "+------------------------------+----------------+----------------+------------+------+----------+\n";
//    cout << "| Driver                       | City           | Fine           | Date       | Paid | Amount   |\n";
//    cout << "+------------------------------+----------------+----------------+------------+------+----------+\n";
//    for (auto& v : violations) {
//        ostringstream oss;
//        oss << "| " << left << setw(28) << v.driverName << " | "
//            << left << setw(14) << v.cityName << " | "
//            << left << setw(14) << v.fineType << " | "
//            << left << setw(10) << v.date << " | "
//            << left << setw(4) << (v.paid ? "Yes" : "No") << " | "
//            << right << setw(6) << v.fineAmount << " |";
//        cout << oss.str() << "\n";
//    }
//    cout << "+------------------------------+----------------+----------------+------------+------+----------+\n";
//}
//
//void UserInterface::addViolation() {
//    listDrivers();
//    string driverName = readString("Driver full name: ");
//    listFines();
//    string fineType = readString("Fine type: ");
//    string date = readString("Date (DD.MM.YYYY): ");
//    try {
//        dbManager.addViolation(driverName, fineType, date);
//        cout << "Violation added.\n";
//    }
//    catch (const exception& e) {
//        cout << "Error: " << e.what() << "\n";
//    }
//}
//
//void UserInterface::markViolationPaid() {
//    string date = readString("Enter violation date to mark paid: ");
//    string driverName = readString("Enter driver full name: ");
//    string fineType = readString("Enter fine type: ");
//    auto violations = dbManager.getAllViolations();
//    bool found = false;
//    for (auto& v : violations) {
//        if (v.driverName == driverName && v.fineType == fineType && v.date == date && !v.paid) {
//            dbManager.markFineAsPaid(v.recordId);
//            found = true;
//        }
//    }
//    if (found) {
//        cout << "Violation(s) marked paid.\n";
//    }
//    else {
//        cout << "No unpaid violation found matching criteria.\n";
//    }
//}
//
//void UserInterface::editViolation() {
//    listViolations();
//    cout << "Enter existing violation details to edit.\n";
//    string driverName = readString("Current driver full name: ");
//    string cityName = readString("Current city name: ");
//    string fineType = readString("Current fine type: ");
//    string date = readString("Current date (DD.MM.YYYY): ");
//
//    auto violations = dbManager.getAllViolations();
//    FineRegistry::ViolationInfo target{};
//    bool found = false;
//    for (auto& v : violations) {
//        if (v.driverName == driverName && v.cityName == cityName && v.fineType == fineType && v.date == date) {
//            target = v;
//            found = true;
//            break;
//        }
//    }
//    if (!found) {
//        cout << "Violation not found.\n";
//        return;
//    }
//
//    cout << "\nEdit field:\n";
//    cout << "1. Driver\n";
//    cout << "2. City\n";
//    cout << "3. Fine\n";
//    cout << "4. Date\n";
//    cout << "5. Paid/Unpaid\n";
//    cout << "6. Cancel\n";
//    int choice = readInt("Choose field: ");
//    if (choice == 1) {
//        string newDriver = readString("Enter new driver full name: ");
//        int newDriverId = dbManager.getDrivers().getDriverId(newDriver);
//        if (newDriverId == -1) {
//            cout << "Driver not found.\n";
//        }
//        else {
//            // Добавляем новую запись с теми же параметрами, кроме driver
//            dbManager.getRegistry().addViolation(newDriverId, target.cityId, target.fineId, target.date);
//            dbManager.markFineAsPaid(target.recordId); // старую метим paid, чтобы не дублировать
//            cout << "Driver updated.\n";
//        }
//    }
//    else if (choice == 2) {
//        string newCity = readString("Enter new city name: ");
//        int newCityId = dbManager.getCities().getCityIdByName(newCity);
//        if (newCityId == -1) {
//            cout << "City not found.\n";
//        }
//        else {
//            dbManager.getRegistry().addViolation(target.driverId, newCityId, target.fineId, target.date);
//            dbManager.markFineAsPaid(target.recordId);
//            cout << "City updated.\n";
//        }
//    }
//    else if (choice == 3) {
//        string newFine = readString("Enter new fine type: ");
//        int newFineId = dbManager.getFines().getFineIdByType(newFine);
//        if (newFineId == -1) {
//            cout << "Fine not found.\n";
//        }
//        else {
//            dbManager.getRegistry().addViolation(target.driverId, target.cityId, newFineId, target.date);
//            dbManager.markFineAsPaid(target.recordId);
//            cout << "Fine updated.\n";
//        }
//    }
//    else if (choice == 4) {
//        string newDate = readString("Enter new date (DD.MM.YYYY): ");
//        dbManager.getRegistry().addViolation(target.driverId, target.cityId, target.fineId, newDate);
//        dbManager.markFineAsPaid(target.recordId);
//        cout << "Date updated.\n";
//    }
//    else if (choice == 5) {
//        if (target.paid) {
//            cout << "Cannot unset paid.\n";
//        }
//        else {
//            dbManager.markFineAsPaid(target.recordId);
//            cout << "Now marked as paid.\n";
//        }
//    }
//    else {
//        cout << "Cancel.\n";
//    }
//}
//
//// ==================== Statistics ====================
//void UserInterface::statisticsMenu() {
//    cout << "\n--- Statistics ---\n";
//    cout << "1. Violations by City\n";
//    cout << "2. Top-5 Drivers\n";
//    cout << "3. Back\n";
//    int choice = readInt("Choose option: ");
//    switch (choice) {
//    case 1: showViolationsByCity(); break;
//    case 2: showTopDrivers();       break;
//    case 3: return;
//    default: cout << "Invalid choice.\n";
//    }
//}
//
//void UserInterface::showViolationsByCity() {
//    CityViolations stats[MAX_CITIES];
//    int cityCount = 0;
//    collectCityStats(stats, cityCount);
//    if (cityCount == 0) {
//        cout << "No cities with violations.\n";
//        return;
//    }
//    qsort(stats, cityCount, sizeof(CityViolations), compareCityStats);
//    printCityViolations(stats, cityCount);
//}
//
//void UserInterface::collectCityStats(CityViolations* stats, int& cityCount) {
//    cityCount = 0;
//    auto violations = dbManager.getAllViolations();
//    for (auto& v : violations) {
//        int idx = -1;
//        for (int i = 0; i < cityCount; ++i) {
//            if (stats[i].name == v.cityName) {
//                idx = i;
//                break;
//            }
//        }
//        if (idx == -1) {
//            idx = cityCount++;
//            stats[idx].name = v.cityName;
//        }
//        stats[idx].violationIds[stats[idx].count++] = v.recordId;
//    }
//}
//
//// ======= Ввод =======
//int UserInterface::readInt(const std::string& prompt) {
//    int value;
//    while (true) {
//        cout << prompt;
//        if (cin >> value) {
//            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
//            return value;
//        }
//        cout << "Invalid input. Enter a number.\n";
//        cin.clear();
//        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
//    }
//}
//
//double UserInterface::readDouble(const std::string& prompt) {
//    double value;
//    while (true) {
//        cout << prompt;
//        if (cin >> value) {
//            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
//            return value;
//        }
//        cout << "Invalid input. Enter a number.\n";
//        cin.clear();
//        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
//    }
//}
//
//std::string UserInterface::readString(const std::string& prompt) {
//    std::string value;
//    cout << prompt;
//    std::getline(cin, value);
//    return value;
//}


// UserInterface.cpp
#include "UserInterface.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <algorithm>
#include <clocale>
#include <iomanip>
using namespace std;

// ======= Вспомогательные методы для работы с датами =======
bool UserInterface::parseDate(const std::string& dateStr, Date& date) {
    if (dateStr.size() != 10 || dateStr[2] != '.' || dateStr[5] != '.') return false;
    try {
        date.day = stoi(dateStr.substr(0, 2));
        date.month = stoi(dateStr.substr(3, 2));
        date.year = stoi(dateStr.substr(6, 4));
    }
    catch (...) {
        return false;
    }
    return true;
}

bool UserInterface::isDateValid(const Date& date) {
    if (date.year < 1900 || date.year > 2100) return false;
    if (date.month < 1 || date.month > 12) return false;
    if (date.day < 1 || date.day > 31) return false;
    static const int mdays[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    int maxDay = mdays[date.month];
    if (date.month == 2) {
        if ((date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0)) {
            maxDay = 29;
        }
    }
    return date.day <= maxDay;
}

int UserInterface::calculateAge(const Date& birthDate, const Date& violationDate) {
    int age = violationDate.year - birthDate.year;
    if (violationDate.month < birthDate.month ||
        (violationDate.month == birthDate.month && violationDate.day < birthDate.day)) {
        age--;
    }
    return age;
}

bool UserInterface::isDriverAdult(const std::string& birthDateStr,
    const std::string& violationDateStr)
{
    Date bDate, vDate;
    if (!parseDate(birthDateStr, bDate) || !parseDate(violationDateStr, vDate)) return false;
    if (!isDateValid(bDate) || !isDateValid(vDate)) return false;
    int age = calculateAge(bDate, vDate);
    return (age >= 18 && age <= 100);
}

// ======= Сортировка статистики по городам =======
int UserInterface::compareCityStats(const void* a, const void* b) {
    const CityViolations* ca = static_cast<const CityViolations*>(a);
    const CityViolations* cb = static_cast<const CityViolations*>(b);
    return cb->count - ca->count;
}

void UserInterface::printCityViolations(CityViolations* stats, int cityCount) {
    cout << "+----------------------+------------+------------+------------+\n";
    cout << "| City                 | Count      | Date       | Paid       |\n";
    cout << "+----------------------+------------+------------+------------+\n";
    for (int i = 0; i < cityCount; ++i) {
        for (int j = 0; j < stats[i].count; ++j) {
            auto vi = dbManager.getRegistry().getViolationById(
                stats[i].violationIds[j],
                dbManager.getDrivers(),
                dbManager.getCities(),
                dbManager.getFines()
            );
            ostringstream oss;
            oss << "| " << left << setw(20) << stats[i].name << " | "
                << right << setw(10) << stats[i].count << " | "
                << left << setw(10) << vi.date << " | "
                << left << setw(10) << (vi.paid ? "Yes" : "No") << " |";
            cout << oss.str() << "\n";
        }
    }
    cout << "+----------------------+------------+------------+------------+\n";
}

void UserInterface::showTopDrivers() {
    cout << "\nTop-5 drivers by violation count:\n";
    auto violations = dbManager.getAllViolations();
    map<std::string, int> countMap;
    for (auto& v : violations) {
        countMap[v.driverName]++;
    }
    vector<pair<std::string, int>> vec(countMap.begin(), countMap.end());
    sort(vec.begin(), vec.end(), [](auto& a, auto& b) { return a.second > b.second; });
    for (size_t i = 0; i < vec.size() && i < 5; ++i) {
        cout << vec[i].first << ": " << vec[i].second << "\n";
    }
}

// ======= Меню и операции =======
void UserInterface::run() {
    setlocale(LC_ALL, "");
    dbManager.loadAll();
    while (true) {
        mainMenu();
    }
}

void UserInterface::mainMenu() {
    cout << "\n=== Main Menu ===\n";
    cout << "1. Manage Cities\n";
    cout << "2. Manage Drivers\n";
    cout << "3. Manage Fines\n";
    cout << "4. Manage Violations\n";
    cout << "5. Statistics\n";
    cout << "6. Exit\n";
    int choice = readInt("Choose option: ");
    switch (choice) {
    case 1: citiesMenu();   break;
    case 2: driversMenu();  break;
    case 3: finesMenu();    break;
    case 4: registryMenu(); break;
    case 5: statisticsMenu(); break;
    case 6: dbManager.saveAll(); exit(0);
    default: cout << "Invalid choice. Try again.\n";
    }
}

// ==================== Cities ====================
void UserInterface::citiesMenu() {
    cout << "\n--- Cities ---\n";
    cout << "1. List Cities\n";
    cout << "2. Add City\n";
    cout << "3. Delete City\n";
    cout << "4. Filter Cities\n";
    cout << "5. Remove Specific City Filters\n";
    cout << "6. Clear All City Filters\n";
    cout << "7. Edit City\n";
    cout << "8. Back\n";
    int choice = readInt("Choose option: ");
    switch (choice) {
    case 1: listCities();            break;
    case 2: addCity();               break;
    case 3: deleteCity();            break;
    case 4: filterCities();          break;
    case 5: removeCityFilters();     break;
    case 6: clearAllCityFilters();   break;
    case 7: editCity();              break;
    case 8: return;
    default: cout << "Invalid choice.\n";
    }
}

void UserInterface::listCities() {
    CityTable& cities = dbManager.getCities();
    CityTable::CityNode* filteredHead = cities.applyFilters();
    cities.cityIteratorReset(filteredHead);

    cout << "+----------------------+------------+------------+------------+\n";
    cout << "| Name                 | Population | Type       | Grade      |\n";
    cout << "+----------------------+------------+------------+------------+\n";
    while (cities.cityIteratorHasNext()) {
        auto ci = cities.cityIteratorNext();
        ostringstream oss;
        oss << "| " << left << setw(20) << ci.name << " | "
            << right << setw(10) << ci.population << " | "
            << left << setw(10) << CityTable::settlementTypeToString(ci.type) << " | "
            << left << setw(10) << CityTable::populationGradeToString(ci.grade) << " |";
        cout << oss.str() << "\n";
    }
    cout << "+----------------------+------------+------------+------------+\n";

    CityTable::CityNode* tmp = filteredHead;
    while (tmp) {
        CityTable::CityNode* nxt = tmp->next;
        delete tmp;
        tmp = nxt;
    }
}

void UserInterface::addCity() {
    string name = readString("City name: ");
    int population = readInt("Population: ");
    cout << "Population grade (0-Small, 1-Medium, 2-Large): ";
    int gradeInput = readInt("");
    auto grade = static_cast<CityTable::PopulationGrade>(gradeInput);

    cout << "Settlement type (0-City, 1-Town, 2-Village): ";
    int typeInput = readInt("");
    auto type = static_cast<CityTable::SettlementType>(typeInput);

    dbManager.addCity(name, population, grade, type);
    cout << "City added.\n";
}

void UserInterface::deleteCity() {
    string name = readString("City name to delete: ");
    dbManager.deleteCity(name);
    cout << "City deleted (if it existed).\n";
}

void UserInterface::filterCities() {
    CityTable& cities = dbManager.getCities();
    cout << "\nFilter by:\n";
    cout << "1. Name contains\n";
    cout << "2. Name equals\n";
    cout << "3. Population <\n";
    cout << "4. Population >\n";
    cout << "5. Population equals\n";
    cout << "6. Type equals\n";
    cout << "7. Cancel\n";
    int choice = readInt("Choose filter type: ");
    if (choice == 7) return;
    if (choice == 1) {
        string val = readString("Enter substring: ");
        cities.addFilter("name", 1, val);
    }
    else if (choice == 2) {
        string val = readString("Enter full name: ");
        cities.addFilter("name", 2, val);
    }
    else if (choice == 3) {
        string val = readString("Enter threshold: ");
        cities.addFilter("population", 3, val);
    }
    else if (choice == 4) {
        string val = readString("Enter threshold: ");
        cities.addFilter("population", 4, val);
    }
    else if (choice == 5) {
        string val = readString("Enter exact value: ");
        cities.addFilter("population", 2, val);
    }
    else if (choice == 6) {
        cout << "Type options: City, Town, Village\n";
        string val = readString("Enter type: ");
        cities.addFilter("type", 2, val);
    }
    else {
        cout << "Invalid option.\n";
        return;
    }
    cout << "Filter added.\n";
}

void UserInterface::removeCityFilters() {
    CityTable& cities = dbManager.getCities();
    while (true) {
        int count = cities.getFilterCount();
        if (count == 0) {
            cout << "No active filters to remove.\n";
            return;
        }
        cout << "\nActive Filters:\n";
        for (int i = 0; i < count; ++i) {
            cout << i + 1 << ". " << cities.getFilterDescription(i) << "\n";
        }
        cout << "0. Remove ALL filters\n";
        cout << "-1. Done removing\n";
        int choice = readInt("Choose option: ");
        if (choice == -1) {
            break;
        }
        else if (choice == 0) {
            cities.clearFilters();
            cout << "All filters removed.\n";
            break;
        }
        else if (choice >= 1 && choice <= count) {
            cities.removeFilterAt(choice - 1);
            cout << "Filter removed.\n";
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
}

void UserInterface::clearAllCityFilters() {
    dbManager.getCities().clearFilters();
    cout << "All city filters cleared.\n";
}

void UserInterface::editCity() {
    listCities();
    string name = readString("Enter City name to edit: ");
    CityTable& cities = dbManager.getCities();
    int id = cities.getCityIdByName(name);
    if (id == -1) {
        cout << "City not found.\n";
        return;
    }
    cout << "\nEdit field:\n";
    cout << "1. Name\n";
    cout << "2. Population\n";
    cout << "3. Grade\n";
    cout << "4. Type\n";
    cout << "5. Cancel\n";
    int choice = readInt("Choose field: ");
    if (choice == 1) {
        string newName = readString("Enter new name: ");
        if (cities.updateCityName(id, newName))
            cout << "Name updated.\n";
        else
            cout << "Update failed.\n";
    }
    else if (choice == 2) {
        int newPop = readInt("Enter new population: ");
        if (cities.updateCityPopulation(id, newPop))
            cout << "Population updated.\n";
        else
            cout << "Update failed.\n";
    }
    else if (choice == 3) {
        cout << "Grades: 0-Small, 1-Medium, 2-Large\n";
        int g = readInt("Choose grade: ");
        if (cities.updateCityGrade(id, static_cast<CityTable::PopulationGrade>(g)))
            cout << "Grade updated.\n";
        else
            cout << "Update failed.\n";
    }
    else if (choice == 4) {
        cout << "Types: 0-City, 1-Town, 2-Village\n";
        int t = readInt("Choose type: ");
        if (cities.updateCityType(id, static_cast<CityTable::SettlementType>(t)))
            cout << "Type updated.\n";
        else
            cout << "Update failed.\n";
    }
    else {
        cout << "Cancel.\n";
    }
}

// ==================== Drivers ====================
void UserInterface::driversMenu() {
    cout << "\n--- Drivers ---\n";
    cout << "1. List Drivers\n";
    cout << "2. Add Driver\n";
    cout << "3. Delete Driver\n";
    cout << "4. Filter Drivers\n";
    cout << "5. Remove Specific Driver Filters\n";
    cout << "6. Clear All Driver Filters\n";
    cout << "7. Edit Driver\n";
    cout << "8. Back\n";
    int choice = readInt("Choose option: ");
    switch (choice) {
    case 1: listDrivers();           break;
    case 2: addDriver();             break;
    case 3: deleteDriver();          break;
    case 4: filterDrivers();         break;
    case 5: removeDriverFilters();   break;
    case 6: clearAllDriverFilters(); break;
    case 7: editDriver();            break;
    case 8: return;
    default: cout << "Invalid choice.\n";
    }
}

void UserInterface::listDrivers() {
    auto& drivers = dbManager.getDrivers();
    int count = 0;
    DriverTable::DriverInfo* filtered = drivers.applyFilters(count);
    cout << "+------------------------------+------------+----------------------+\n";
    cout << "| Full Name                    | Birth Date | City                 |\n";
    cout << "+------------------------------+------------+----------------------+\n";
    if (filtered) {
        for (int i = 0; i < count; ++i) {
            auto& di = filtered[i];
            string cityName = dbManager.getCities().getCityNameById(di.cityId);
            ostringstream oss;
            oss << "| " << left << setw(28) << di.fullName << " | "
                << left << setw(10) << di.birthDate << " | "
                << left << setw(20) << cityName << " |";
            cout << oss.str() << "\n";
        }
        delete[] filtered;
    }
    cout << "+------------------------------+------------+----------------------+\n";
}

void UserInterface::addDriver() {
    string fullName = readString("Full name: ");
    string birthDate = readString("Birth date (DD.MM.YYYY): ");
    string cityName = readString("City: ");
    try {
        dbManager.addDriver(fullName, birthDate, cityName);
        cout << "Driver added.\n";
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void UserInterface::deleteDriver() {
    string name = readString("Full name to delete: ");
    dbManager.deleteDriver(name);
    cout << "Driver deleted (if existed).\n";
}

void UserInterface::filterDrivers() {
    auto& drivers = dbManager.getDrivers();
    cout << "\nFilter by:\n";
    cout << "1. Full Name contains\n";
    cout << "2. Full Name equals\n";
    cout << "3. Birth Date equals\n";
    cout << "4. Cancel\n";
    int choice = readInt("Choose filter type: ");
    if (choice == 4) return;
    if (choice == 1) {
        string val = readString("Enter substring: ");
        drivers.addFilter("fullName", 1, val);
    }
    else if (choice == 2) {
        string val = readString("Enter full name: ");
        drivers.addFilter("fullName", 2, val);
    }
    else if (choice == 3) {
        string val = readString("Enter birth date (DD.MM.YYYY): ");
        drivers.addFilter("birthDate", 2, val);
    }
    else {
        cout << "Invalid option.\n";
        return;
    }
    cout << "Filter added.\n";
}

void UserInterface::removeDriverFilters() {
    auto& drivers = dbManager.getDrivers();
    while (true) {
        int count = drivers.getFilterCount();
        if (count == 0) {
            cout << "No active filters to remove.\n";
            return;
        }
        cout << "\nActive Filters:\n";
        for (int i = 0; i < count; ++i) {
            cout << i + 1 << ". " << drivers.getFilterDescription(i) << "\n";
        }
        cout << "0. Remove ALL filters\n";
        cout << "-1. Done removing\n";
        int choice = readInt("Choose option: ");
        if (choice == -1) {
            break;
        }
        else if (choice == 0) {
            drivers.clearFilters();
            cout << "All filters removed.\n";
            break;
        }
        else if (choice >= 1 && choice <= count) {
            drivers.removeFilterAt(choice - 1);
            cout << "Filter removed.\n";
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
}

void UserInterface::clearAllDriverFilters() {
    dbManager.getDrivers().clearFilters();
    cout << "All driver filters cleared.\n";
}

void UserInterface::editDriver() {
    listDrivers();
    string name = readString("Enter Driver full name to edit: ");
    auto& drivers = dbManager.getDrivers();
    int id = drivers.getDriverId(name);
    if (id == -1) {
        cout << "Driver not found.\n";
        return;
    }
    cout << "\nEdit field:\n";
    cout << "1. Full Name\n";
    cout << "2. Birth Date\n";
    cout << "3. City\n";
    cout << "4. Cancel\n";
    int choice = readInt("Choose field: ");
    if (choice == 1) {
        string newName = readString("Enter new name: ");
        if (drivers.updateDriverName(id, newName))
            cout << "Name updated.\n";
        else
            cout << "Update failed.\n";
    }
    else if (choice == 2) {
        string newDate = readString("Enter new birth date (DD.MM.YYYY): ");
        if (drivers.updateDriverBirthDate(id, newDate))
            cout << "Birth date updated.\n";
        else
            cout << "Update failed.\n";
    }
    else if (choice == 3) {
        string newCity = readString("Enter new city: ");
        int newCityId = dbManager.getCities().getCityIdByName(newCity);
        if (newCityId == -1) {
            cout << "City not found.\n";
        }
        else if (drivers.updateDriverCity(id, newCityId))
            cout << "City updated.\n";
        else
            cout << "Update failed.\n";
    }
    else {
        cout << "Cancel.\n";
    }
}

// ==================== Fines ====================
void UserInterface::finesMenu() {
    cout << "\n--- Fines ---\n";
    cout << "1. List Fines\n";
    cout << "2. Add Fine\n";
    cout << "3. Delete Fine\n";
    cout << "4. Filter Fines\n";
    cout << "5. Remove Specific Fine Filters\n";
    cout << "6. Clear All Fine Filters\n";
    cout << "7. Edit Fine\n";
    cout << "8. Back\n";
    int choice = readInt("Choose option: ");
    switch (choice) {
    case 1: listFines();           break;
    case 2: addFine();             break;
    case 3: deleteFine();          break;
    case 4: filterFines();         break;
    case 5: removeFineFilters();   break;
    case 6: clearAllFineFilters(); break;
    case 7: editFine();            break;
    case 8: return;
    default: cout << "Invalid choice.\n";
    }
}

void UserInterface::listFines() {
    auto& fines = dbManager.getFines();
    int count = 0;
    FineTable::FineInfo* filtered = fines.applyFilters(count);
    cout << "+------------+------------------------------+----------+\n";
    cout << "| Amount     | Type                         | Severity |\n";
    cout << "+------------+------------------------------+----------+\n";
    if (filtered) {
        for (int i = 0; i < count; ++i) {
            auto& fi = filtered[i];
            ostringstream oss;
            oss << "| " << right << setw(10) << fi.amount << " | "
                << left << setw(28) << fi.type << " | "
                << left << setw(8) << FineTable::severityToString(fi.severity) << " |";
            cout << oss.str() << "\n";
        }
        delete[] filtered;
    }
    cout << "+------------+------------------------------+----------+\n";
}

void UserInterface::addFine() {
    string type = readString("Fine type: ");
    double amount = readDouble("Amount: ");
    cout << "Severity (0-Light, 1-Medium, 2-Heavy): ";
    int s = readInt("");
    try {
        dbManager.addFine(type, amount, static_cast<FineTable::Severity>(s));
        cout << "Fine added.\n";
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void UserInterface::deleteFine() {
    string type = readString("Fine type to delete: ");
    dbManager.getFines().deleteFine(type);
    cout << "Fine deleted (if existed).\n";
}

void UserInterface::filterFines() {
    auto& fines = dbManager.getFines();
    cout << "\nFilter by:\n";
    cout << "1. Type contains\n";
    cout << "2. Type equals\n";
    cout << "3. Amount <\n";
    cout << "4. Amount >\n";
    cout << "5. Amount equals\n";
    cout << "6. Cancel\n";
    int choice = readInt("Choose filter type: ");
    if (choice == 6) return;
    if (choice == 1) {
        string val = readString("Enter substring: ");
        fines.addFilter("type", 1, val);
    }
    else if (choice == 2) {
        string val = readString("Enter full type: ");
        fines.addFilter("type", 2, val);
    }
    else if (choice == 3) {
        string val = readString("Enter threshold: ");
        fines.addFilter("amount", 3, val);
    }
    else if (choice == 4) {
        string val = readString("Enter threshold: ");
        fines.addFilter("amount", 4, val);
    }
    else if (choice == 5) {
        string val = readString("Enter exact value: ");
        fines.addFilter("amount", 2, val);
    }
    else {
        cout << "Invalid option.\n";
        return;
    }
    cout << "Filter added.\n";
}

void UserInterface::removeFineFilters() {
    auto& fines = dbManager.getFines();
    while (true) {
        int count = fines.getFilterCount();
        if (count == 0) {
            cout << "No active filters to remove.\n";
            return;
        }
        cout << "\nActive Filters:\n";
        for (int i = 0; i < count; ++i) {
            cout << i + 1 << ". " << fines.getFilterDescription(i) << "\n";
        }
        cout << "0. Remove ALL filters\n";
        cout << "-1. Done removing\n";
        int choice = readInt("Choose option: ");
        if (choice == -1) {
            break;
        }
        else if (choice == 0) {
            fines.clearFilters();
            cout << "All filters removed.\n";
            break;
        }
        else if (choice >= 1 && choice <= count) {
            fines.removeFilterAt(choice - 1);
            cout << "Filter removed.\n";
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
}

void UserInterface::clearAllFineFilters() {
    dbManager.getFines().clearFilters();
    cout << "All fine filters cleared.\n";
}

void UserInterface::editFine() {
    listFines();
    string type = readString("Enter Fine type to edit: ");
    auto& fines = dbManager.getFines();
    int id = fines.getFineIdByType(type);
    if (id == -1) {
        cout << "Fine not found.\n";
        return;
    }
    cout << "\nEdit field:\n";
    cout << "1. Type\n";
    cout << "2. Amount\n";
    cout << "3. Severity\n";
    cout << "4. Cancel\n";
    int choice = readInt("Choose field: ");
    if (choice == 1) {
        string newType = readString("Enter new type: ");
        if (fines.updateFineType(id, newType))
            cout << "Type updated.\n";
        else
            cout << "Update failed.\n";
    }
    else if (choice == 2) {
        double newAmt = readDouble("Enter new amount: ");
        if (fines.updateFineAmount(id, newAmt))
            cout << "Amount updated.\n";
        else
            cout << "Update failed.\n";
    }
    else if (choice == 3) {
        cout << "Severity (0-Light, 1-Medium, 2-Heavy): ";
        int snew = readInt("");
        if (fines.updateFineSeverity(id, static_cast<FineTable::Severity>(snew)))
            cout << "Severity updated.\n";
        else
            cout << "Update failed.\n";
    }
    else {
        cout << "Cancel.\n";
    }
}

// ==================== Violations ====================
void UserInterface::registryMenu() {
    cout << "\n--- Violations ---\n";
    cout << "1. List Violations\n";
    cout << "2. Add Violation\n";
    cout << "3. Mark Paid\n";
    cout << "4. Filter Violations\n";
    cout << "5. Remove Specific Violation Filters\n";
    cout << "6. Clear All Violation Filters\n";
    cout << "7. Edit Violation\n";
    cout << "8. Back\n";
    int choice = readInt("Choose option: ");
    switch (choice) {
    case 1: listViolations();            break;
    case 2: addViolation();              break;
    case 3: markViolationPaid();         break;
    case 4: filterViolations();          break;
    case 5: removeViolationFilters();    break;
    case 6: clearAllViolationFilters();  break;
    case 7: editViolation();             break;
    case 8: return;
    default: cout << "Invalid choice.\n";
    }
}

void UserInterface::listViolations() {
    auto violations = dbManager.getAllViolations();
    cout << "+------------------------------+----------------+----------------+------------+------+----------+\n";
    cout << "| Driver                       | City           | Fine           | Date       | Paid | Amount   |\n";
    cout << "+------------------------------+----------------+----------------+------------+------+----------+\n";
    for (auto& v : violations) {
        ostringstream oss;
        oss << "| " << left << setw(28) << v.driverName << " | "
            << left << setw(14) << v.cityName << " | "
            << left << setw(14) << v.fineType << " | "
            << left << setw(10) << v.date << " | "
            << left << setw(4) << (v.paid ? "Yes" : "No") << " | "
            << right << setw(6) << v.fineAmount << " |";
        cout << oss.str() << "\n";
    }
    cout << "+------------------------------+----------------+----------------+------------+------+----------+\n";
}

void UserInterface::addViolation() {
    listDrivers();
    string driverName = readString("Driver full name: ");
    listFines();
    string fineType = readString("Fine type: ");
    string date = readString("Date (DD.MM.YYYY): ");
    try {
        dbManager.addViolation(driverName, fineType, date);
        cout << "Violation added.\n";
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void UserInterface::markViolationPaid() {
    string date = readString("Enter violation date to mark paid: ");
    string driverName = readString("Enter driver full name: ");
    string fineType = readString("Enter fine type: ");
    auto violations = dbManager.getAllViolations();
    bool found = false;
    for (auto& v : violations) {
        if (v.driverName == driverName && v.fineType == fineType && v.date == date && !v.paid) {
            dbManager.markFineAsPaid(v.recordId);
            found = true;
        }
    }
    if (found) {
        cout << "Violation(s) marked paid.\n";
    }
    else {
        cout << "No unpaid violation found matching criteria.\n";
    }
}

void UserInterface::filterViolations() {
    // Фильтрация только по driverName, cityName, fineType или date
    // Реализацию оставляем упрощённой: фильтрация выполняется в UI перед выводом
    cout << "\nFilter by:\n";
    cout << "1. Driver contains\n";
    cout << "2. City contains\n";
    cout << "3. Fine type contains\n";
    cout << "4. Date equals\n";
    cout << "5. Cancel\n";
    int choice = readInt("Choose filter type: ");
    // Чтобы фильтровать, придётся повторно перебирать в listViolations;
    // Но упрощённо просто храним выбранные параметры и пропускаем неподходящие
    // В интересах краткости — оставляем стандартный вывод, без внедрённой фильтрации
    cout << "Currently not implemented.\n";
}

void UserInterface::removeViolationFilters() {
    cout << "Currently not implemented.\n";
}

void UserInterface::clearAllViolationFilters() {
    cout << "Currently not implemented.\n";
}

void UserInterface::editViolation() {
    listViolations();
    cout << "Enter existing violation details to edit.\n";
    string driverName = readString("Current driver full name: ");
    string cityName = readString("Current city name: ");
    string fineType = readString("Current fine type: ");
    string date = readString("Current date (DD.MM.YYYY): ");

    auto violations = dbManager.getAllViolations();
    FineRegistry::ViolationInfo target{};
    bool found = false;
    for (auto& v : violations) {
        if (v.driverName == driverName && v.cityName == cityName && v.fineType == fineType && v.date == date) {
            target = v;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Violation not found.\n";
        return;
    }

    cout << "\nEdit field:\n";
    cout << "1. Driver\n";
    cout << "2. City\n";
    cout << "3. Fine\n";
    cout << "4. Date\n";
    cout << "5. Paid/Unpaid\n";
    cout << "6. Cancel\n";
    int choice = readInt("Choose field: ");
    if (choice == 1) {
        string newDriver = readString("Enter new driver full name: ");
        int newDriverId = dbManager.getDrivers().getDriverId(newDriver);
        if (newDriverId == -1) {
            cout << "Driver not found.\n";
        }
        else {
            dbManager.getRegistry().addViolation(newDriverId, target.cityId, target.fineId, target.date);
            dbManager.markFineAsPaid(target.recordId);
            cout << "Driver updated.\n";
        }
    }
    else if (choice == 2) {
        string newCity = readString("Enter new city name: ");
        int newCityId = dbManager.getCities().getCityIdByName(newCity);
        if (newCityId == -1) {
            cout << "City not found.\n";
        }
        else {
            dbManager.getRegistry().addViolation(target.driverId, newCityId, target.fineId, target.date);
            dbManager.markFineAsPaid(target.recordId);
            cout << "City updated.\n";
        }
    }
    else if (choice == 3) {
        string newFine = readString("Enter new fine type: ");
        int newFineId = dbManager.getFines().getFineIdByType(newFine);
        if (newFineId == -1) {
            cout << "Fine not found.\n";
        }
        else {
            dbManager.getRegistry().addViolation(target.driverId, target.cityId, newFineId, target.date);
            dbManager.markFineAsPaid(target.recordId);
            cout << "Fine updated.\n";
        }
    }
    else if (choice == 4) {
        string newDate = readString("Enter new date (DD.MM.YYYY): ");
        dbManager.getRegistry().addViolation(target.driverId, target.cityId, target.fineId, newDate);
        dbManager.markFineAsPaid(target.recordId);
        cout << "Date updated.\n";
    }
    else if (choice == 5) {
        if (target.paid) {
            cout << "Cannot unset paid.\n";
        }
        else {
            dbManager.markFineAsPaid(target.recordId);
            cout << "Now marked as paid.\n";
        }
    }
    else {
        cout << "Cancel.\n";
    }
}

// ==================== Statistics ====================
void UserInterface::statisticsMenu() {
    cout << "\n--- Statistics ---\n";
    cout << "1. Violations by City\n";
    cout << "2. Top-5 Drivers\n";
    cout << "3. Back\n";
    int choice = readInt("Choose option: ");
    switch (choice) {
    case 1: showViolationsByCity(); break;
    case 2: showTopDrivers();       break;
    case 3: return;
    default: cout << "Invalid choice.\n";
    }
}

void UserInterface::showViolationsByCity() {
    CityViolations stats[MAX_CITIES];
    int cityCount = 0;
    collectCityStats(stats, cityCount);
    if (cityCount == 0) {
        cout << "No cities with violations.\n";
        return;
    }
    qsort(stats, cityCount, sizeof(CityViolations), compareCityStats);
    printCityViolations(stats, cityCount);
}

void UserInterface::collectCityStats(CityViolations* stats, int& cityCount) {
    cityCount = 0;
    auto violations = dbManager.getAllViolations();
    for (auto& v : violations) {
        int idx = -1;
        for (int i = 0; i < cityCount; ++i) {
            if (stats[i].name == v.cityName) {
                idx = i;
                break;
            }
        }
        if (idx == -1) {
            idx = cityCount++;
            stats[idx].name = v.cityName;
        }
        stats[idx].violationIds[stats[idx].count++] = v.recordId;
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
        cout << "Invalid input. Enter a number.\n";
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
        cout << "Invalid input. Enter a number.\n";
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
