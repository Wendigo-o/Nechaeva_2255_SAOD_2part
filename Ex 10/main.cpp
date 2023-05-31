// main.cpp : Defines the entry point for the console application.
#include <iostream>
#include <string>
#include <time.h>
#include <list>
#include "LZ77.h"
using namespace std;
//#include "RollingHash.h"

int main()
{
	string sFInName, sFOutName;
	ofstream os;
	ifstream is;
	char cRead;
	cout << " введите первую букву (c - compressing; d - decompressing):";
	cin >> cRead; cin.get();

	if (cRead != 'c' && cRead != 'd') {printf("Ошибка: операция не распознана\n");
		return -1;
	}
	cout << "введите название 'Input File':" << endl;
	getline(cin, sFInName);
	cout << "введите название 'Output File':" << endl;
	getline(cin, sFOutName);

	// Открываем потоки для ввода и вывода
	is.open(sFInName, ios::binary);
	os.open(sFOutName, ios::binary);

	if (!is.is_open()) {cout << "Ошибка: не может открыть файл " << sFInName << "!.." << endl;
		return -1;
	}
	if (!os.is_open()) {cout << "Ошибка: не может открыть файл " << sFOutName << "!.." << endl;
		return -1;
	}
	if (cRead == 'c')
	{
		auto t1 = clock();
		//cout << time(0) << endl;
		if (CompressFile(is, os) >= 0) {
			cout << clock() - t1 << endl;
			cout << "Сжатие прошло успешно" << endl;
		}
		else {cout << "Ошибка сжатия" << endl;}
		//cout << time(0) << endl;
	}

	else if (cRead == 'd')
	{
		int res = DecompressFile(is, os);
		if (res >= 0) {
			cout << res <<" Распаковка прошла успешно" << endl;
		}
		else {
			cout << "Ошибка распаковки" << endl;
		}
	}

    return 0;
}

