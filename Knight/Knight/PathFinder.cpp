#include <iostream>
#include "PathFinder.h"
#include "SimpleStack.h"
#include <queue>

using namespace std;

const int dx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
const int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

void bfs(Point start, Point end, Point parent[N][N]) {
    queue<Point> q;
    bool visited[N][N] = {};

    q.push(start);
    visited[start.x][start.y] = true;
    parent[start.x][start.y] = Point(-1, -1);

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        if (current.x == end.x && current.y == end.y) return;

        for (int i = 0; i < 8; ++i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (isValid(nx, ny) && !visited[nx][ny]) {
                visited[nx][ny] = true;
                parent[nx][ny] = current;
                q.push(Point(nx, ny));
            }
        }
    }
}

void dfs(Point start, Point end, Point parent[N][N]) {
    SimpleStack stack;
    bool visited[N][N] = {};

    stack.push(start);
    visited[start.x][start.y] = true;
    parent[start.x][start.y] = Point(-1, -1);

    while (!stack.isEmpty()) {
        Point current = stack.top();
        stack.pop();

        if (current.x == end.x && current.y == end.y) return;

        for (int i = 7; i >= 0; --i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (isValid(nx, ny) && !visited[nx][ny]) {
                visited[nx][ny] = true;
                parent[nx][ny] = current;
                stack.push(Point(nx, ny));
            }
        }
    }
}

void printPath(Point end, Point parent[N][N]) {
    Point path[64];
    int count = 0;
    Point current = end;

    while (current.x != -1 || current.y != -1) {
        path[count++] = current;
        current = parent[current.x][current.y];
    }

    for (int i = count - 1; i >= 0; --i) {
        cout << toChessNotation(path[i]) << " ";
    }
    cout << endl;
}