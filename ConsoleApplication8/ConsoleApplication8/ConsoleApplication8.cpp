#include <iostream>
using namespace std;

// Умножение двух матриц 2x2
void multiplyMatrices(long long a[2][2], long long b[2][2]) {
    long long result[2][2];
    result[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
    result[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
    result[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
    result[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];

    // Копируем результат обратно в a
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            a[i][j] = result[i][j];
}

// Быстрое возведение матрицы в степень
void powerMatrix(long long matrix[2][2], long long n) {
    if (n <= 1)
        return;

    long long base[2][2] = { {1, 1}, {1, 0} };

    // Рекурсивное деление
    powerMatrix(matrix, n / 2);
    multiplyMatrices(matrix, matrix); // Квадрат матрицы

    if (n % 2 != 0) // Если степень нечётная
        multiplyMatrices(matrix, base);
}

// Функция для нахождения n-го числа Фибоначчи
long long fibonacci(long long n) {
    if (n == 0)
        return 0;

    long long matrix[2][2] = { {1, 1}, {1, 0} };

    // Возводим матрицу в степень n-1
    powerMatrix(matrix, n - 1);

    // Возвращаем верхний левый элемент матрицы
    return matrix[0][0];
}

int main() {
    long long n;
    cout << "Enter n: ";
    cin >> n;

    cout << "Fibonacci number " << n << " is: " << fibonacci(n) << endl;

    return 0;
}
