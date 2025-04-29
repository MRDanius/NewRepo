//#include <iostream>
//using namespace std;
//
//int rand(int y) {
//    cout << y << endl;
//    y++;
//    return rand(y); // Рекурсивный вызов для переполнения стека
//}
//
//int main() {
//    rand(1);
//    return 0;
//}


#include <iostream>
using namespace std;

int main() {
    
    int* y; 

    while (true) {
        int* x = new int;  
        y = x;           
        cout << y << endl;
    }

    return 0;
}


