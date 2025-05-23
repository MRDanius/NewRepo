//#include "UserInterface.h"
//#include <clocale>
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//    UserInterface ui;
//    ui.run();
//    return 0;
//}

//#include "UserInterface.h"
//
//int main() {
//    try {
//        UserInterface ui;
//        ui.run();
//    }
//    catch (const std::exception& e) {
//        std::cerr << "⛔ Critical error: " << e.what() << std::endl;
//        return 1;
//    }
//    return 0;
//}

// DATABASE.cpp
#include "UserInterface.h"

int main() {
    try {
        UserInterface ui;
        ui.run();
    }
    catch (const std::exception& e) {
        std::cerr << "⛔ Critical error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
