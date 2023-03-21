
#include <iostream>
#include "utils.h"
using namespace std;

int main()
{
    int a[5]{ 1,2,3,4,5 };
    for (int i = 0; i < 5; i++)
        cout << a[i] << ' ';
    cout << endl;

    rotate(a, 5, true); //в одну сторону
    for (int* p = a; p - a < 5; p++)
        cout << *p << ' ';
    cout << endl;

    rotate(a, 5); //возвращаем на место и в обратную сторону
    rotate(a, 5);
    for (int* p = a; p - a < 5; p++)
        cout << *p << ' ';
    cout << endl;
}
