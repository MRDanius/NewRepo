

#include <iostream>

// Функция перемножения матриц
int* multiplicationMatrix(
    const int* matrixA, int rowsA, int colsA,
    const int* matrixB, int rowsB, int colsB,
    int& rowsResult, int& colsResult) {

    // Задаем размеры результирующей матрицы
    rowsResult = rowsA;
    colsResult = colsB;

    // Выделяем память под результирующую матрицу
    int* resultMatrix = new int[rowsResult * colsResult];

    // Инициализация элементов результирующей матрицы нулями
    for (int i = 0; i < rowsResult; ++i) {
        for (int j = 0; j < colsResult; ++j) {
            *(resultMatrix + i * colsResult + j) = 0;
        }
    }

    // Перемножение матриц
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                *(resultMatrix + i * colsResult + j) +=
                    (*(matrixA + i * colsA + k)) * (*(matrixB + k * colsB + j));
            }
        }
    }

    return resultMatrix;
}

// Функция для вывода матрицы
void printMatrix(const int* matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << *(matrix + i * cols + j) << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Задаем первую матрицу (2x3)
    const int matrixA[] = {
        1, 2, 3,
        4, 5, 6
    };
    int rowsA = 2, colsA = 3;   

    // Задаем вторую матрицу (3x2)
    const int matrixB[] = {
        7, 8,
        9, 10,
        11, 12
    };
    int rowsB = 3, colsB = 2;

    // Размеры результирующей матрицы
    int rowsResult, colsResult;

    // Умножение матриц
    int* resultMatrix = multiplicationMatrix(matrixA, rowsA, colsA, matrixA, rowsB, colsB, rowsResult, colsResult);

    if (resultMatrix != nullptr) {
        // Вывод результирующей матрицы
        std::cout << "Result:" << std::endl;
        printMatrix(resultMatrix, rowsResult, colsResult);

        // Очистка памяти
        delete[] resultMatrix;
    }

    return 0;
}