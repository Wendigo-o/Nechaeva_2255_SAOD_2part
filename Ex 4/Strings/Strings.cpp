#include <iostream>
#include "Str.h"

void Test(Str s) 
{
    cout << s << endl;
    cout << strlen(s) << endl;
}

int main()
{
    Str s = "123";
    cout << s << endl;
    cout << strlen(s) << endl;
    Test(s);
    cout << '\n' << endl;

    {
        Str t;
        t = s;
        t = s = t;
        Test(t);
        Test(s);
    }
    
    cout << "\nOperator += : " << endl;
    Str a = "Str1";
    Str b = "Str2";
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    a += b;
    cout << "a + b = " << a << endl;

    cout << "\nOperator + : " << endl;
    a = "Str3";
    b = "Str4";
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    Str ab = a + b;
    cout << "a + b = " << ab << endl;
    cout << "a + b + Str5 = " << (ab + "Str5") << endl;
}
