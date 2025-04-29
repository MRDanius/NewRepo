
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

const int WIDTH = 40;
const int HEIGHT = 20;

class GameOfLife {
private:
    std::vector<std::vector<bool>> grid;
    std::vector<std::vector<bool>> nextGrid;

public:
    GameOfLife() : grid(HEIGHT, std::vector<bool>(WIDTH, false)),
        nextGrid(HEIGHT, std::vector<bool>(WIDTH, false)) {
        // Инициализация начального состояния (глайдер)
        int startX = 10, startY = 10;
        grid[startY][startX + 1] = true;
        grid[startY + 1][startX + 2] = true;
        grid[startY + 2][startX] = true;
        grid[startY + 2][startX + 1] = true;
        grid[startY + 2][startX + 2] = true;
    }

    void update() {
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                int neighbors = countNeighbors(x, y);
                if (grid[y][x]) {
                    nextGrid[y][x] = (neighbors == 2 || neighbors == 3);
                }
                else {
                    nextGrid[y][x] = (neighbors == 3);
                }
            }
        }
        grid.swap(nextGrid);
    }

    void display() const {
        system("cls"); // Очистка экрана (для Windows)
        // system("clear"); // Для Unix-подобных систем

        for (const auto& row : grid) {
            for (bool cell : row) {
                std::cout << (cell ? "■" : " ");
            }
            std::cout << std::endl;
        }
    }

private:
    int countNeighbors(int x, int y) const {
        int count = 0;
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0) continue;
                int nx = (x + dx + WIDTH) % WIDTH;
                int ny = (y + dy + HEIGHT) % HEIGHT;
                count += grid[ny][nx];
            }
        }
        return count;
    }
};

int main() {
    GameOfLife game;

    while (true) {
        game.display();
        game.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
.