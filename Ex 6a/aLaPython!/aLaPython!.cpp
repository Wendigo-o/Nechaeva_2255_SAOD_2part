#include <iostream>
#include "Array.h"

int main()
{
    //п. 12 и 13
    int v[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
    Array* t = new Array(4, 3, v);
    std::cout << t << std::endl;

    // вариант 7
    std::cout << "rows: " << t->Rows() << " cols: " << t->Cols() << std::endl;
    std::cout << "Array[1][0]: " << t->Item(1, 0) << std::endl;
    std::cout << "Array[3][1]: " << t->Item(3, 1) << std::endl;

    Array* reshaped = t->Reshape(2, 6);
    std::cout << *reshaped;

    std::cout << std::endl << "element changed in first Array" << std::endl;
    t->Item(1, 1) = 10 * t->Item(1, 1);
    std::cout << *t << std::endl << *reshaped << std::endl;

    delete[] t;
    delete[] v;
    delete[] reshaped;
}

