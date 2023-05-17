#include <iostream>
#include <list>
#include <string>
using namespace std;




string getRandom(int len) {
	static char ab[] = "0123456789abcdefghifklmnopqrstuvwxyz";
	static int aLen = sizeof(ab)-1;
	string s(len, ' ');
	for (int i = 0; i < len; i++) { s[i] = ab[rand() % aLen]; }
	return s;
}
void printstr(list<string> list) {
  for(string n:list) { cout << n << " "; } 
  cout << endl;
}

