#include "vector_algebra.h"
#include <iostream>
#include <cmath>

using namespace std;

Vector getVector(const Point& p1, const Point& p2) {
    return { p2.x - p1.x, p2.y - p1.y, p2.z - p1.z };
}

double vectorLength(const Vector& v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector normalizeVector(const Vector& v) {
    double len = vectorLength(v);
    if (len == 0) {
        cerr << "Error: Cannot normalize a zero vector." << endl;
        exit(1);
    }
    return { v.x / len, v.y / len, v.z / len };
}

double dotProduct(const Vector& v1, const Vector& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector crossProduct(const Vector& v1, const Vector& v2) {
    return {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}

void printVector(const Vector& v) {
    cout << "<" << v.x << ", " << v.y << ", " << v.z << ">";
}