#include <iostream>
#include <cmath>

using namespace std;

// Константа точности
const double EPSILON = 1e-6;

// Функция для нахождения значения многочлена в точке x
double evaluate_polynomial(double* coefficients, int degree, double x) {
    double result = 0;

    // Вычисляем значение многочлена в точке x
    for (int i = degree; i >= 0; --i) {
        result += coefficients[i] * pow(x, i);
    }

    return result;
}

// Функция для вывода многочлена
void print_polynomial(double* coefficients, int degree, double right_side) {
    bool first = true; // Флаг для первого члена

    for (int i = degree; i >= 0; --i) {
        if (coefficients[i] != 0) { // Пропускаем нулевые коэффициенты
            if (!first) {
                // Добавляем знак между членами
                cout << (coefficients[i] > 0 ? " + " : " - ");
            }
            else {
                // Для первого члена проверяем знак отдельно
                if (coefficients[i] < 0) {
                    cout << "-";
                }
                first = false; // Сбрасываем флаг
            }

            // Вывод значения коэффициента (без знака, так как знак уже учтен)
            if (fabs(coefficients[i]) != 1 || i == 0) {
                cout << fabs(coefficients[i]);
            }

            // Вывод переменной и степени, если степень больше 0
            if (i > 0) {
                cout << "x";
                if (i > 1) {
                    cout << "^" << i;
                }
            }
        }
    }

    cout << " = " << right_side << endl;
}

// Функция для поиска корня методом половинного деления
double bisection_method(double* coefficients, int degree, double left, double right) {
    double mid;

    // Проверяем значение функции в начальных точках
    double f_left = evaluate_polynomial(coefficients, degree, left);
    double f_right = evaluate_polynomial(coefficients, degree, right);

    if (fabs(f_left) < EPSILON) {
        return left; // Левый конец является корнем
    }
    if (fabs(f_right) < EPSILON) {
        return right; // Правый конец является корнем
    }

    while ((right - left) >= EPSILON) {
        mid = (left + right) / 2;
        double f_mid = evaluate_polynomial(coefficients, degree, mid);

        // Проверяем, является ли mid корнем
        if (fabs(f_mid) < EPSILON) {
            return mid;
        }

        // Выбираем отрезок, содержащий корень
        if (f_left * f_mid < 0) {
            right = mid;
            f_right = f_mid;
        }
        else {
            left = mid;
            f_left = f_mid;
        }
    }

    // Возвращаем приближённое значение корня
    return (left + right) / 2;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int degree;
    cout << "Введите степень многочлена (максимум 10): ";
    cin >> degree;

    if (degree < 0 || degree > 10) {
        cout << "Степень многочлена должна быть в пределах от 0 до 10." << endl;
        return 1;
    }

    // Используем динамическое выделение памяти для хранения коэффициентов многочлена
    double* coefficients = new double[degree + 1]();

    // Вводим коэффициенты
    cout << "Введите коэффициенты для многочлена (начиная от старшего члена):" << endl;
    for (int i = degree; i >= 0; --i) {
        cout << "Коэффициент при x^" << i << ": ";
        cin >> coefficients[i];
    }

    // Спрашиваем правую часть уравнения
    double right_side;
    cout << "Введите правую часть уравнения (после '='): ";
    cin >> right_side;

    // Корректируем коэффициенты с учетом правой части
    coefficients[0] -= right_side;

    // Выводим начальный многочлен
    cout << "Многочлен: ";
    print_polynomial(coefficients, degree, right_side);

    // Ввод границ интервала
    double a, b;
    cout << "Введите границы отрезка [a, b] для метода половинного деления:" << endl;
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;

    // Поиск корня
    double root = bisection_method(coefficients, degree, a, b);

    if (isnan(root)) {
        cout << "Корень не найден." << endl;
    }
    else {
        cout << "Приближённый корень: x = " << root << endl;
    }

    // Освобождаем память
    delete[] coefficients;

    return 0;
}
