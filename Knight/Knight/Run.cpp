#include "Run.h"
#include "Utils.h"
#include "PathFinder.h"
#include <iostream>

using namespace std;
void runKnightPathFinder() {
    char startStr[3], endStr[3];
    cout << "Enter starting position (e.g. A1): ";
    cin >> startStr;
    cout << "Enter ending position (e.g. H8): ";
    cin >> endStr;

    Point start = parseChessNotation(startStr);
    Point end = parseChessNotation(endStr);

    if (!isValid(start.x, start.y)) {
        cout << "Invalid start position!\n";
        return;
    }
    if (!isValid(end.x, end.y)) {
        cout << "Invalid end position!\n";
        return;
    }

    Point parentBFS[N][N];
    Point parentDFS[N][N];

    cout << "\nBFS path (shortest): ";
    bfs(start, end, parentBFS);
    printPath(end, parentBFS);

    cout << "DFS path: ";
    dfs(start, end, parentDFS);
    printPath(end, parentDFS);
}