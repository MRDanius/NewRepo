#pragma once
#include "Point.h"
#include "Utils.h"

void bfs(Point start, Point end, Point parent[N][N]);
void dfs(Point start, Point end, Point parent[N][N]);
void printPath(Point end, Point parent[N][N]);