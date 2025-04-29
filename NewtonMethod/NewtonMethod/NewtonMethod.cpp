#include <iostream>
#include <cmath>

using namespace std;

// Кубическая функция
double f(double x, int a, int b, int c, int d) {
    return a * pow(x, 3) + b * pow(x, 2) + c * x + d;
}

// Производная функции
double df(double x, int a, int b, int c) {
    return 3 * a * pow(x, 2) + 2 * b * x + c;
}

// Метод Ньютона
double newton(int a, int b, int c, int d, double x0, double epsilon) {
    double x = x0;
    while (true) {
        double fx = f(x, a, b, c, d);
        double dfx = df(x, a, b, c);

        if (abs(dfx) < epsilon) { // Предотвращение деления на ноль
            cout << "Derivative too small (x = " << x << "), method failed." << endl;
            return NAN;
        }

        double x_new = x - fx / dfx;

        if (abs(x_new - x) < epsilon) {
            return x_new; // Найден корень
        }

        x = x_new;
    }
}

void inputCoefficients(double& a, double& b, double& c, double& d) {
    cout << "Enter coefficients a, b, c, d: ";
    cin >> a >> b >> c >> d;

    // Проверка на успешный ввод
    while (cin.fail()) {
        cout << "Input error. Please enter integer numbers for coefficients a, b, c, d." << endl;
        cin.clear(); // Сбрасываем состояние потока
        cin >> a >> b >> c >> d;
    }
}

void inputBounds(double& Xleft, double& Xright) {
    cout << "Enter Xleft and Xright: ";
    cin >> Xleft >> Xright;

    // Проверка на успешный ввод
    while (cin.fail()) {
        cout << "Input error. Please enter numbers for Xleft and Xright." << endl;
        cin.clear(); // Сбрасываем состояние потока
        cin >> Xleft >> Xright;
    }
}

int main() {
    double a, b, c, d;
    double Xleft, Xright;
    double epsilon = pow(10, -6);

    inputCoefficients(a, b, c, d);
    inputBounds(Xleft, Xright);

    // Начальное приближение
    double x0 = (Xleft + Xright) / 2;

    // Находим корень
    double root = newton(a, b, c, d, x0, epsilon);

    if (!isnan(root)) {
        cout << "Found root: " << root << endl;
    }
    else {
        cout << "Root not found." << endl;
    }

    return 0;
}
