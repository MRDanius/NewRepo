//#include <iostream>
//
//using namespace std;
//
//const int SIZE = 10;
//
//// Функция для слияния двух частей массива (часть алгоритма Merge Sort)
//void merge(int arr[], int left, int mid, int right) {
//    int n1 = mid - left + 1;
//    int n2 = right - mid;
//
//    int* L = new int[n1];  // Динамически выделяем память для массива L
//    int* R = new int[n2];  // Динамически выделяем память для массива R
//
//    for (int i = 0; i < n1; i++)
//        L[i] = arr[left + i];
//    for (int i = 0; i < n2; i++)
//        R[i] = arr[mid + 1 + i];
//
//    int i = 0, j = 0, k = left;
//    while (i < n1 && j < n2) {
//        if (L[i] <= R[j]) {
//            arr[k] = L[i];
//            i++;
//        }
//        else {
//            arr[k] = R[j];
//            j++;
//        }
//        k++;
//    }
//
//    while (i < n1) {
//        arr[k] = L[i];
//        i++;
//        k++;
//    }
//
//    while (j < n2) {
//        arr[k] = R[j];
//        j++;
//        k++;
//    }
//
//    delete[] L;  // Освобождаем память, выделенную для массива L
//    delete[] R;  // Освобождаем память, выделенную для массива R
//}
//
//// Функция сортировки слиянием (Merge Sort)
//void mergeSort(int arr[], int left, int right) {
//    if (left < right) {
//        int mid = left + (right - left) / 2;
//
//        mergeSort(arr, left, mid);
//        mergeSort(arr, mid + 1, right);
//
//        merge(arr, left, mid, right);
//    }
//}
//
//// Функция для нахождения пересечения двух массивов
//int intersection(int A[], int B[], int result[]) {
//    int i = 0, j = 0, k = 0;
//    while (i < SIZE && j < SIZE) {
//        if (A[i] == B[j]) {
//            result[k++] = A[i];
//            i++;
//            j++;
//        }
//        else if (A[i] < B[j]) {
//            i++;
//        }
//        else {
//            j++;
//        }
//    }
//    return k; // Возвращаем количество элементов в пересечении
//}
//
//// Функция для нахождения объединения двух массивов
//int unionArrays(int A[], int B[], int result[]) {
//    int i = 0, j = 0, k = 0;
//    while (i < SIZE && j < SIZE) {
//        if (A[i] == B[j]) {
//            result[k++] = A[i];
//            i++;
//            j++;
//        }
//        else if (A[i] < B[j]) {
//            result[k++] = A[i++];
//        }
//        else {
//            result[k++] = B[j++];
//        }
//    }
//
//    while (i < SIZE) {
//        result[k++] = A[i++];
//    }
//
//    while (j < SIZE) {
//        result[k++] = B[j++];
//    }
//
//    return k; // Возвращаем количество элементов в объединении
//}
//
//// Функция для нахождения A без B
//int differenceAB(int A[], int B[], int result[]) {
//    int i = 0, j = 0, k = 0;
//    while (i < SIZE && j < SIZE) {
//        if (A[i] < B[j]) {
//            result[k++] = A[i++];
//        }
//        else if (A[i] == B[j]) {
//            i++;
//            j++;
//        }
//        else {
//            j++;
//        }
//    }
//
//    while (i < SIZE) {
//        result[k++] = A[i++];
//    }
//
//    return k; // Возвращаем количество элементов в A без B
//}
//
//// Функция для нахождения B без A
//int differenceBA(int A[], int B[], int result[]) {
//    int i = 0, j = 0, k = 0;
//    while (i < SIZE && j < SIZE) {
//        if (B[j] < A[i]) {
//            result[k++] = B[j++];
//        }
//        else if (A[i] == B[j]) {
//            i++;
//            j++;
//        }
//        else {
//            i++;
//        }
//    }
//
//    while (j < SIZE) {
//        result[k++] = B[j++];
//    }
//
//    return k; // Возвращаем количество элементов в B без A
//}
//
//// Функция для вывода массива
//void printArray(int arr[], int size) {
//    for (int i = 0; i < size; i++) {
//        cout << arr[i] << " ";
//    }
//    cout << endl;
//}
//
//int main() {
//    int A[SIZE], B[SIZE];
//
//    // Ввод массива A
//    cout << "Enter 10 elements for array A: ";
//    for (int i = 0; i < SIZE; i++) {
//        cin >> A[i];
//    }
//
//    // Ввод массива B
//    cout << "Enter 10 elements for array B: ";
//    for (int i = 0; i < SIZE; i++) {
//        cin >> B[i];
//    }
//
//    // Сортируем массивы
//    mergeSort(A, 0, SIZE - 1);
//    mergeSort(B, 0, SIZE - 1);
//
//    int result[SIZE * 2]; // Максимальный размер объединения — 20 элементов
//    int choice;
//
//    // Меню
//    cout << "Select an operation:\n";
//    cout << "1. A union B\n";
//    cout << "2. A intersection B\n";
//    cout << "3. A minus B\n";
//    cout << "4. B minus A\n";
//    cout << "Enter your choice: ";
//    cin >> choice;
//
//    int size = 0;
//
//    switch (choice) {
//    case 1:
//        size = unionArrays(A, B, result);
//        cout << "Union of A and B: ";
//        break;
//    case 2:
//        size = intersection(A, B, result);
//        cout << "Intersection of A and B: ";
//        break;
//    case 3:
//        size = differenceAB(A, B, result);
//        cout << "A minus B: ";
//        break;
//    case 4:
//        size = differenceBA(A, B, result);
//        cout << "B minus A: ";
//        break;
//    default:
//        cout << "Invalid choice!" << endl;
//        return 1;
//    }
//
//    printArray(result, size);
//
//    return 0;
//}




#include <iostream>

using namespace std;

const int SIZE = 10;

// Функция для слияния двух частей массива (часть алгоритма Merge Sort)
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

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

    delete[] L;
    delete[] R;
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

// Универсальная функция для нахождения объединения, пересечения или разности массивов
int setOperation(int A[], int B[], int result[], bool findUnion, bool findIntersection) {
    int i = 0, j = 0, k = 0;

    while (i < SIZE && j < SIZE) {
        if (A[i] == B[j]) {
            if (findIntersection || findUnion) result[k++] = A[i];
            i++;
            j++;
        }
        else if (A[i] < B[j]) {
            if (findUnion || !findIntersection) result[k++] = A[i];
            i++;
        }
        else {
            if (findUnion) result[k++] = B[j];
            j++;
        }
    }

    while (i < SIZE && (findUnion || !findIntersection)) {
        result[k++] = A[i++];
    }

    while (j < SIZE && findUnion) {
        result[k++] = B[j++];
    }

    return k;
}

// Функция для нахождения разности A и B или B и A
int difference(int A[], int B[], int result[], bool isAB) {
    return setOperation(isAB ? A : B, isAB ? B : A, result, false, false);
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
    cout << "Enter 10 elements for array A: ";
    for (int i = 0; i < SIZE; i++) {
        cin >> A[i];
    }

    // Ввод массива B
    cout << "Enter 10 elements for array B: ";
    for (int i = 0; i < SIZE; i++) {
        cin >> B[i];
    }

    // Сортируем массивы
    mergeSort(A, 0, SIZE - 1);
    mergeSort(B, 0, SIZE - 1);

    int result[SIZE * 2];
    int choice, size = 0;

    // Меню
    cout << "Select an operation:\n";
    cout << "1. A union B\n";
    cout << "2. A intersection B\n";
    cout << "3. A minus B\n";
    cout << "4. B minus A\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        size = setOperation(A, B, result, true, false);
        cout << "Union of A and B: ";
        break;
    case 2:
        size = setOperation(A, B, result, false, true);
        cout << "Intersection of A and B: ";
        break;
    case 3:
        size = difference(A, B, result, true);
        cout << "A minus B: ";
        break;
    case 4:
        size = difference(A, B, result, false);
        cout << "B minus A: ";
        break;
    default:
        cout << "Invalid choice!" << endl;
        return 1;
    }

    printArray(result, size);

    return 0;
}
