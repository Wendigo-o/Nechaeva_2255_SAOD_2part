#include <iostream>
#include "Aggregate.h"
#include "Child.h"
#include "Test.h"
using namespace std;

int main()
{
    cout << "Main start" << endl;
    Test test;
    Test* b = new Test(); 
    delete b;
    Test* c = new Test[2]; 
    delete[] c;
    test.foo(test);
    
    Child child;
    Aggregate agg;
}


