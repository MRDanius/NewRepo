#include <iostream>
#include <cmath>

using namespace std;

// Функция для вывода многочлена
void print_polynomial(double* coeffs, int degree, double rhs) {
    bool isFirst = true;
    int ChatGPT
    // Выводим многочлен
    for (int i = degree; i >= 0; --i) {
        if (coeffs[i] != 0) {
            if (!isFirst) {
                cout << (coeffs[i] > 0 ? " + " : " - ");
            }
            else if (coeffs[i] < 0) {
                cout << "-";
            } 
            if (i == 0 || fabs(coeffs[i]) != 1) {
                cout << fabs(coeffs[i]);
            }

            if (i > 0) {
                cout << "x";
            }

            if (i > 1) {
                cout << "^" << i;
            }
            isFirst = false;
        }
    }

    cout << " = " << rhs << endl;
}

// Функция для нахождения значения многочлена в точке x
double evaluate_polynomial(double* coeffs, int degree, double x) {
    double value = 0;

    // Вычисляем значение многочлена в точке x
    for (int i = degree; i >= 0; --i) {
        value += coeffs[i] * pow(x, i);
    }

    return value;
}

// Функция для нахождения корней линейного уравнения
double find_linear_root(double a, double b) {
    if (a == 0) {
        if (b == 0) {
            cout << "infinitely many solutions." << endl;
        }
        else {
            cout << "no solutions." << endl;
        }
        return NAN;
    }
    return -b / a;
}

// Метод Ньютона для нахождения корней многочлена
double newton_method(double* coeffs, int degree, double start = 0.0, int maxIter = 60, double eps = 1e-6) {
    double x = start;

    for (int iter = 0; iter < maxIter; ++iter) {
        double fx = evaluate_polynomial(coeffs, degree, x); // Значение многочлена в точке x

        if (fabs(fx) < eps) {
            cout << "Root found: x = " << x << endl;
            return x;
        }

        // Находим производную многочлена
        double* deriv_coeffs = new double[degree];
        for (int i = degree; i > 0; --i) {
            deriv_coeffs[i - 1] = coeffs[i] * i;
        }

        double f_prime_x = evaluate_polynomial(deriv_coeffs, degree - 1, x); // Значение производной в точке x

        delete[] deriv_coeffs;

        if (fabs(f_prime_x) < eps) {
            cout << "Derivative is too small" << endl;
            return NAN;
        }

        x -= fx / f_prime_x; // Шаг метода Ньютона
    }

    cout << "Newton's method did not work." << endl;
    return NAN;
}

int main() {
    

    int degree;
    cout << "Enter the degree of the polynomial (maximum 10): ";
    cin >> degree;


    // Динамическое выделение памяти для коэффициентов
    double* coeffs = new double[degree + 1];

    cout << "Enter the coefficients for the polynomial (starting with the highest):" << endl;
    for (int i = degree; i >= 0; --i) {
        cout << "Coefficient at x^" << i << ": ";
        cin >> coeffs[i];
    }

    // Ввод правой части уравнения
    double rhs;
    cout << "Enter the right side of the equation (after the '='): ";
    cin >> rhs;

    // Корректируем свободный член
    coeffs[0] -= rhs;

    // Вывод многочлена
    cout << "Polynomial: ";
    print_polynomial(coeffs, degree, rhs);

    // Метод Ньютона
    double guess;
    cout << "Enter the initial guess for Newton's method: ";
    cin >> guess;

    newton_method(coeffs, degree, guess);

    // Освобождаем память
    delete[] coeffs;

    return 0;
}
