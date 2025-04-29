#pragma once

#include "Point.h"

const int N = 8;

bool isValid(int x, int y);
Point parseChessNotation(const char* s);
const char* toChessNotation(Point p);