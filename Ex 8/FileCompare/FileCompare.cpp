#include <iostream>
#include "WF.h"
#include <fstream>

int main()
{
    WF a = WF();
    std::ifstream prev("prev.txt");
	std::ifstream curr("cur.txt");
	a.Compare(prev, curr);
	std::cout << "Rows: " << a.Rows() << std::endl;
	std::cout << "Columns: " << a.Columns() << std::endl;
	std::cout << "Distance: " << a.Distance() << std::endl;
	std::cout << a.Prescription() << std::endl;
}

