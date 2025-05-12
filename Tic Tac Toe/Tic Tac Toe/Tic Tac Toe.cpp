#include "GameLauncher.h"
#include "GameState.h"
#include <clocale>


int main() {

    setlocale(LC_ALL, "RU");
    initialize_states(); // Инициализация графа состояний
    GameLauncher::start();
    free_memory();       // Очистка памяти
    return 0;
}