#include "text_generator.h"
#include <clocale>

int main() {
    setlocale(LC_ALL, "Russian");
    TextGenerator tg;
    tg.train("training.txt");
    tg.generate("alice", 7);
    return 0;
}