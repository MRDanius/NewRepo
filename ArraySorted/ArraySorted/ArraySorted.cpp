#include <iostream>

using namespace std;

const int SIZE = 10;

// Функция для слияния двух частей массива (часть алгоритма Merge Sort)
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Функция сортировки слиянием (Merge Sort)
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Функция для нахождения пересечения двух массивов
int intersection(int A[], int B[], int result[]) {
    int i = 0, j = 0, k = 0;
    while (i < SIZE && j < SIZE) {
        if (A[i] == B[j]) {
            result[k++] = A[i];
            i++;
            j++;
        }
        else if (A[i] < B[j]) {
            i++;
        }
        else {
            j++;
        }
    }
    return k; // Возвращаем количество элементов в пересечении
}

// Функция для нахождения объединения двух массивов
int unionArrays(int A[], int B[], int result[]) {
    int i = 0, j = 0, k = 0;
    while (i < SIZE && j < SIZE) {
        if (A[i] == B[j]) {
            result[k++] = A[i];
            i++;
            j++;
        }
        else if (A[i] < B[j]) {
            result[k++] = A[i++];
        }
        else {
            result[k++] = B[j++];
        }
    }

    while (i < SIZE) {
        result[k++] = A[i++];
    }

    while (j < SIZE) {
        result[k++] = B[j++];
    }

    return k; // Возвращаем количество элементов в объединении
}

// Функция для нахождения A без B
int differenceAB(int A[], int B[], int result[]) {
    int i = 0, j = 0, k = 0;
    while (i < SIZE && j < SIZE) {
        if (A[i] < B[j]) {
            result[k++] = A[i++];
        }
        else if (A[i] == B[j]) {
            i++;
            j++;
        }
        else {
            j++;
        }
    }

    while (i < SIZE) {
        result[k++] = A[i++];
    }

    return k; // Возвращаем количество элементов в A без B
}

// Функция для нахождения B без A
int differenceBA(int A[], int B[], int result[]) {
    int i = 0, j = 0, k = 0;
    while (i < SIZE && j < SIZE) {
        if (B[j] < A[i]) {
            result[k++] = B[j++];
        }
        else if (A[i] == B[j]) {
            i++;
            j++;
        }
        else {
            i++;
        }
    }

    while (j < SIZE) {
        result[k++] = B[j++];
    }

    return k; // Возвращаем количество элементов в B без A
}

// Функция для вывода массива
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int A[SIZE], B[SIZE];

    // Ввод массива A
    cout << "Введите 10 элементов массива A: ";
    for (int i = 0; i < SIZE; i++) {
        cin >> A[i];
    }

    // Ввод массива B
    cout << "Введите 10 элементов массива B: ";
    for (int i = 0; i < SIZE; i++) {
        cin >> B[i];
    }

    // Сортируем массивы
    mergeSort(A, 0, SIZE - 1);
    mergeSort(B, 0, SIZE - 1);

    int result[SIZE * 2]; // Максимальный размер объединения — 20 элементов
    int choice;

    // Меню
    cout << "Выберите операцию:\n";
    cout << "1. A объединение B\n";
    cout << "2. A пересечение B\n";
    cout << "3. A без B\n";
    cout << "4. B без A\n";
    cout << "Введите ваш выбор: ";
    cin >> choice;

    int size = 0;

    switch (choice) {
    case 1:
        size = unionArrays(A, B, result);
        cout << "Объединение A и B: ";
        break;
    case 2:
        size = intersection(A, B, result);
        cout << "Пересечение A и B: ";
        break;
    case 3:
        size = differenceAB(A, B, result);
        cout << "A без B: ";
        break;
    case 4:
        size = differenceBA(A, B, result);
        cout << "B без A: ";
        break;
    default:
        cout << "Неверный выбор!" << endl;
        return 1;
    }

    printArray(result, size);

    return 0;
}
