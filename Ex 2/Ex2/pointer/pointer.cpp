// pointer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "utils.h";
using namespace std;


int main()
{
    int a = 3, b = 5;
    cout << a << ' ' << b << endl;
    Swap(a, b);
    cout << a << ' ' << b << endl;
    Swap1(&a, &b);
    cout << a << ' ' << b << endl;

}
 

