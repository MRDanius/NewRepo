#include "Utils.h"
#include <cctype>
#include <cstring>
using namespace std;
bool isValid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

Point parseChessNotation(const char* s) {
    if (strlen(s) != 2) return Point(-1, -1);
    int x = toupper(s[0]) - 'A';
    int y = s[1] - '1';
    return Point(x, y);
}

const char* toChessNotation(Point p) {
    static char buffer[3];
    buffer[0] = 'A' + p.x;
    buffer[1] = '1' + p.y;
    buffer[2] = '\0';
    return buffer;
}