#include <iostream>
#include <cmath>
using namespace std;
const double EPSILON = pow(10, -6); // точность поиска корня

// Функция для вычисления значения кубического многочлена f(x) = ax^3 + bx^2 + cx + d
double f(double x, double a, double b, double c, double d) {
    return a * x * x * x + b * x * x + c * x + d;
}

// Рекурсивная функция для поиска корня методом половинного деления на отрезке [left, right]
double bisection(double a, double b, double c, double d, double left, double right) {
    // Находим середину отрезка
    double mid = (left + right) / 2;
    double f_mid = f(mid, a, b, c, d);

    // Проверка условия f(left) * f(right) < 0
    if (f(left, a, b, c, d) * f(right, a, b, c, d) > 0) {
        cout << "No root or multiple roots in the interval." << endl;
        return NAN; // Возвращаем NaN, если корень не отделён
    }

    // Проверяем, является ли mid корнем
    if (/*fabs(f_mid) < EPSILON && */(right - left) < EPSILON) {
        return mid; // Возвращаем приближённое значение корня
    }

    // Рекурсивный вызов для выбранного отрезка
    if (f(left, a, b, c, d) * f_mid < 0) {
        return bisection(a, b, c, d, left, mid);
    }
    else {
        return bisection(a, b, c, d, mid, right);
    }
}

int main() {
    double a, b, c, d, left, right;

    // Ввод коэффициентов кубического многочлена и границ отрезка
    cout << "Enter polynomial coefficients (a, b, c, d): ";
    cin >> a >> b >> c >> d;
    cout << "Enter interval boundaries (left, right): ";
    cin >> left >> right;

    // Поиск корня
    double root = bisection(a, b, c, d, left, right);

    if (!isnan(root)) {
        cout << "Approximate root value: " << root << endl;
    }
    else {
        cout << "Root not found within the specified interval." << endl;
    }

    return 0;
}
