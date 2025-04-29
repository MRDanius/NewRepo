#include <iostream>
#include <cmath>

const double EPSILON = pow(10, -6);  // Точность

// Функция для вычисления значения многочлена
double equation(double A, double B, double C, double D, double x) {
    return A * x * x * x + B * x * x + C * x + D;
}

// Функция для нахождения корня методом секущих
double findRoot(double A, double B, double C, double D, double x0, double x1) {
    double f0 = equation(A, B, C, D, x0);
    double f1 = equation(A, B, C, D, x1);

    while (fabs(x1 - x0) > EPSILON) {
        // Вычисляем новое приближение
        double x2 = x1 - f1 * (x1 - x0) / (f1 - f0);

        // Сдвигаем границы для следующей итерации
        x0 = x1;
        f0 = f1;
        x1 = x2;
        f1 = equation(A, B, C, D, x1);
    }

    return x1;
}

int main() {
    double A, B, C, D, x0, x1;
    std::cout << "Enter A, B, C, D and interval boundary [x0, x1]: ";
    std::cin >> A >> B >> C >> D >> x0 >> x1;

    double root = findRoot(A, B, C, D, x0, x1);
    std::cout << "Approximate root value: " << root << std::endl;

    return 0;
}