#pragma once
#include <iostream>
#include "Test.h"
using namespace std;

class Test
{
public:
	static int nCount;
	Test();
	Test(const Test& obj);
	~Test();
	void foo(Test test);
};

