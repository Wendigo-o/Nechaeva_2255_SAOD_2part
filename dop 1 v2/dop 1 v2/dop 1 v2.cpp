#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <array>
#include <vector>
int main(int argc, const char** argv) {

    double result = 0;

    //std::string stroka;
    //std::string stroka(argv.data());
    //std::string str(argv);
    //std::string current_exec_name = argv[0]; // Name of the current exec program

    std::string stroka = "";
    for (int i = 1; i < argc; i++) stroka.append(std::string(argv[i]).append(" "));
    char znak;
    char t = '5';
    char arr[] = { '0','1', '2', '3', '4', '5','6','7','8','9' };
    std::string cifra1 = "";
    std::string cifra2 = "";

    //std::cout << argv[1][1] << std::endl;
    if (argv[1][0] == 'a' && argv[1][1] == 'd' && argv[1][2] == 'd') {
        bool flag = false;
        for (int i = 4; i < stroka.length(); i++) {
            if (stroka[i] == ' ') {
                flag = true;
            }
            else if (!flag){
                cifra1 += stroka[i];
            }
            else {
                cifra2 += stroka[i];
            }
        }
        double c1 = atoi(cifra1.c_str());
        double c2 = atoi(cifra2.c_str());
        std::cout << c1 << " + " << c2 << " = " << c1+c2 << std::endl;
        return 0;

    }
    else {

        for (int i = 0; i < stroka.length(); i++) {
            if (std::find(std::begin(arr), std::end(arr), stroka[i]) != std::end(arr)) {
                cifra2 += stroka[i];
            }
            else {
                znak = stroka[i];
                cifra1 = cifra2;
                cifra2 = "";
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
}
