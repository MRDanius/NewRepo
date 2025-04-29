//#include <iostream>
//using namespace std;
//
//int* rand(int y)
//{
//    y++;
//    return &y;
//
//}
//
//
//int main()
//{
//
//    int x = 0;
//    int* z = &x;
//    int* u = &x;
//    while (x < 10)
//    {
//        z = rand(x);
//        x++;
//    }
//    while (x < 20)
//    {
//        u = rand(x);
//        x++;
//    }
//    cout << *z << ' ' << *u;
//    return 0;
//}

#include <iostream>;

using namespace std;

int* rand(int y)
{
	y++;
	return rand(y);

}

int main()
{
	int y = rand();
	cout << y;
}

