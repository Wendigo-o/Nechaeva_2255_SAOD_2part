#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
int main(int argc, char** argv) {

    double result = 0;

    std::string stroka;
    std::cin >> stroka;
    char znak;
    char t = '5';
    char arr[] = { '0','1', '2', '3', '4', '5','6','7','8','9' };
    std::string cifra1 = "";
    std::string cifra2 = "";
    for (int i = 0; i < stroka.length(); i++) {
        if (std::find(std::begin(arr), std::end(arr), stroka[i]) != std::end(arr)) {
            cifra2 += stroka[i];
        }
        else {
            znak = stroka[i];
            cifra1 = cifra2;
            cifra2 ="";
        }
     }
    double c1 = atoi(cifra1.c_str());
    double c2 = atoi(cifra2.c_str());
    switch (znak) {
    case '+': result = c1 + c2; break;
    case '-': result = c1 - c2; break;
    case '*': result = c1 * c2; break;
    case '/': result = c1 / c2; break;
    }
    std::cout << c1 << ' ' << znak << ' ' << c2 << " = " << result << std::endl;
    return 0;
}
