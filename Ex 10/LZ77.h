#pragma once
#include <fstream>
using namespace std;

int CompressFile(ifstream &is, ofstream &os);
int DecompressFile(ifstream &is, ofstream &os);

