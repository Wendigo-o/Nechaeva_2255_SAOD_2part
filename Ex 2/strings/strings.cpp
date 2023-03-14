#include <iostream>
#include "utils.h";
using namespace std;

int main()
{
	char str[] = "Hello!";
	cout << str << endl;

	cout << strlen(str) << ' ' << sizeof(str) << endl;
	
	char t[32];
	string_copy(t, str);
	cout << t << endl;
	cout << strlen(t) << ' ' << sizeof(t) << endl;
	cout << compare(str, t) << endl;

	char str2[] = "Hello world!";
	cout << str2 << endl;
	cout << len(t) << ' ' << len(str2) << endl;

	cout << compare(t, str2) << endl;

}

