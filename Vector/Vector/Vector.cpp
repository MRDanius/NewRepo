#include <iostream>
#include <cmath>

using namespace std;

// Структура для точки в пространстве
struct Point {
    double x;
    double y;
    double z;
};

// Структура для вектора в пространстве
struct Vector {
    double x;
    double y;
    double z;
};

// Функция получения вектора по двум точкам (от p1 к p2)
Vector getVector(const Point& p1, const Point& p2) {
    return { p2.x - p1.x, p2.y - p1.y, p2.z - p1.z };
}

// Функция вычисления длины вектора
double vectorLength(const Vector& v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Функция получения нормированного вектора
Vector normalizeVector(const Vector& v) {
    double len = vectorLength(v);
    if (len == 0) {
        cerr << "Error: Cannot normalize a zero vector." << endl;
    }
    return { v.x / len, v.y / len, v.z / len };
}

// Функция вычисления скалярного произведения двух векторов
double dotProduct(const Vector& v1, const Vector& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Функция вычисления векторного произведения двух векторов
Vector crossProduct(const Vector& v1, const Vector& v2) {
    return {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}

// Функция вычисления смешанного произведения трёх векторов
double mixedProduct(const Vector& v1, const Vector& v2, const Vector& v3) {

    Vector cp = crossProduct(v2, v3);
    return dotProduct(v1, cp);
}

// Функция вывода вектора
void printVector(const Vector& v) {
    cout << "<" << v.x << ", " << v.y << ", " << v.z << ">";
}

int main() {
    int choice;

    // Вывод меню операций
    cout << "Choose an operation:" << endl;
    cout << "1. Get vector from two points" << endl; //вектор по двум точкам
    cout << "2. Normalize vector " << endl; // нормальный вектор
    cout << "3. Compute length of vector " << endl; //длина вектора
    cout << "4. Dot product of two vectors " << endl; // скалярное 
    cout << "5. Cross product of two vectors " << endl; //векторное
    cout << "6. Mixed product of three vectors " << endl; //смешанное
    cout << "Enter your choice (1-6): ";
    cin >> choice;

    switch (choice) {
    case 1: {
        // Получение вектора по двум точкам
        Point p1, p2;
        cout << "Enter the coordinates of the first point (x y z): ";
        cin >> p1.x >> p1.y >> p1.z;
        cout << "Enter the coordinates of the second point (x y z): ";
        cin >> p2.x >> p2.y >> p2.z;
        Vector v = getVector(p1, p2);
        cout << endl << "Vector derived from points: ";
        printVector(v);
        cout << endl;
        break;
    }
    case 2: {
        // Нормализация вектора, полученного по двум точкам
        Point p1, p2;
        cout << "Enter the coordinates of the first point (x y z): ";
        cin >> p1.x >> p1.y >> p1.z;
        cout << "Enter the coordinates of the second point (x y z): ";
        cin >> p2.x >> p2.y >> p2.z;
        Vector v = getVector(p1, p2);
        Vector vn = normalizeVector(v);
        cout << endl << "Normalized vector: ";
        printVector(vn);
        cout << endl;
        break;
    }
    case 3: {
        // Вычисление длины вектора, полученного по двум точкам
        Point p1, p2;
        cout << "Enter the coordinates of the first point (x y z): ";
        cin >> p1.x >> p1.y >> p1.z;
        cout << "Enter the coordinates of the second point (x y z): ";
        cin >> p2.x >> p2.y >> p2.z;
        Vector v = getVector(p1, p2);
        double len = vectorLength(v);
        cout << endl << "Length of vector: " << len << endl;
        break;
    }
    case 4: {
        // Скалярное произведение двух векторов (вводим векторы напрямую)
        Vector v1, v2;
        cout << "Enter the coordinates of the first vector (x y z): ";
        cin >> v1.x >> v1.y >> v1.z;
        cout << "Enter the coordinates of the second vector (x y z): ";
        cin >> v2.x >> v2.y >> v2.z;
        double dot = dotProduct(v1, v2);
        cout << endl << "Dot product: " << dot << endl;
        break;
    }
    case 5: {
        // Векторное произведение двух векторов (вводим векторы напрямую)
        Vector v1, v2;
        cout << "Enter the coordinates of the first vector (x y z): ";
        cin >> v1.x >> v1.y >> v1.z;
        cout << "Enter the coordinates of the second vector (x y z): ";
        cin >> v2.x >> v2.y >> v2.z;
        Vector cp = crossProduct(v1, v2);
        cout << endl << "Cross product: ";
        printVector(cp);
        cout << endl;
        break;
    }
    case 6: {
        // Смешанное произведение трёх векторов (вводим векторы напрямую)
        Vector v1, v2, v3;
        cout << "Enter the coordinates of the first vector (x y z): ";
        cin >> v1.x >> v1.y >> v1.z;
        cout << "Enter the coordinates of the second vector (x y z): ";
        cin >> v2.x >> v2.y >> v2.z;
        cout << "Enter the coordinates of the third vector (x y z): ";
        cin >> v3.x >> v3.y >> v3.z;
        double mp = mixedProduct(v1, v2, v3);
        cout << endl << "Mixed product: " << mp << endl;
        break;
    }
    default: {
        cout << "Invalid choice. Exiting." << endl;
        break;
    }
    }

    return 0;
}