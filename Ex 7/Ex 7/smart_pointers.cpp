#include <iostream>
#include <memory>
#include "Test.h"
using namespace std;

int main() {
	unique_ptr<Test[]> p (new Test[3]);
	for(int i=0; i<3; i++) {
		p.get()[i].value = i + 1;
		p.get()[i].get_value();}
	p.reset(new Test[2]);

	return 0;
}
