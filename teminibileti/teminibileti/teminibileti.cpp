#include <iostream>
#include <locale>  // Для работы с локалями
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");  // Устанавливаем локаль на русскую

    string ticket;

    // Ввод числа от пользователя
    cout << "Введите 6-значное число: ";
    cin >> ticket;

    // Проверка, что число состоит из 6 цифр
    if (ticket.length() != 6) {
        cout << "Число должно быть 6-значным!" << endl;
        return 1;
    }

    // Один цикл для проверки и поиска ближайшего счастливого билета
    for (int i = 0; i < 8; i++) {  // Ограничиваем цикл 8 итерациями
        // Суммы цифр для проверки "счастливости"
        int sum1 = (ticket[0] - '0') + (ticket[1] - '0') + (ticket[2] - '0');
        int sum2 = (ticket[3] - '0') + (ticket[4] - '0') + (ticket[5] - '0');

        // Проверяем, счастливый ли билет
        if (sum1 == sum2) {
            cout << "Счастливый билет: " << ticket << endl;
            return 0;  // Завершаем программу, если нашли счастливый билет
        }

        // Преобразуем строку в число, увеличиваем и обратно в строку
        int num = stoi(ticket) + 1;
        ticket = to_string(num);

        // Заполняем ведущие нули вручную
        if (ticket.length() == 5) ticket = "0" + ticket;
        if (ticket.length() == 4) ticket = "00" + ticket;
        if (ticket.length() == 3) ticket = "000" + ticket;
        if (ticket.length() == 2) ticket = "0000" + ticket;
        if (ticket.length() == 1) ticket = "00000" + ticket;
    }

    // Если счастливый билет не найден, выводим ближайший
    cout << "Ближайший счастливый билет: " << ticket << endl;

    return 0;
}