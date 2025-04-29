#include <iostream>
#include "particle.h"

using namespace std;

int main() {
    double a, T;
    Point p0;
    Vector v0;

    cout << "Enter cube edge length (a): ";
    cin >> a;
    cout << "Enter initial point (x y z): ";
    cin >> p0.x >> p0.y >> p0.z;
    cout << "Enter velocity vector (x y z): ";
    cin >> v0.x >> v0.y >> v0.z;
    cout << "Enter time (T): ";
    cin >> T;

    if (!isInsideCube(p0, a)) {
        cerr << "Error: Initial point is outside the cube." << endl;
        return 1;
    }

    Point final = calculateFinalPosition(a, p0, v0, T);
    cout << "Final position: (" << final.x << ", " << final.y << ", " << final.z << ")" << endl;

    return 0;
}


