#include "text_generator.h"


int main() {
    
    TextGenerator tg;
    tg.train("training.txt");
    tg.generate("smart", 40);
    return 0;
}
//C:\Users\виталий\source\repos\TextG\TextG
