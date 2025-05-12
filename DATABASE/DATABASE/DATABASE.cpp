#include "UserInterface.h"
#include <clocale>

int main() {
    setlocale(LC_ALL, "Russian");
    UserInterface ui;
    ui.run();
    return 0;
}
