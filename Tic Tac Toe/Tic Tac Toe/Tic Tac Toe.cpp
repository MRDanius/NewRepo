#include "GameLauncher.h"
#include "GameState.h"

int main() {
    initialize_states(); // Инициализация графа состояний
    GameLauncher::start();
    free_memory();       // Очистка памяти
    return 0;
}