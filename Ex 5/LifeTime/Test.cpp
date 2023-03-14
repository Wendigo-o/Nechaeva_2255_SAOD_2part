#include "Test.h"
int Test::nCount = 0;
Test::Test() 
{
	nCount++;
	cout << "Create: " << nCount << endl;
}
Test::~Test()
{
	nCount--;
	cout << "Del: " << nCount << endl;
}
Test::Test(const Test& obj)
{
	nCount++;
	cout << "Copy: " << nCount << endl;
}
void Test::foo(Test t) 
{
	cout << "foo is running" << endl;
}