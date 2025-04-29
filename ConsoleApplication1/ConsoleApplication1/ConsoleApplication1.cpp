#include <iostream>
using namespace std;

int b = 22;

int main(){
	for (int i = 1; i < 50; i++) {
		if (b % i == 0) {
			cout << i << endl;			
		}
	}
}

