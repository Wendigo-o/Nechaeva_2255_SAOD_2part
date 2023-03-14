#include <iostream>
#include "Complex.h"


int main()
{
	Complex a(1, 2), b = 3;
	cout << "a =" << a << ", b = " << b << "\n" << endl;

	cout << "a + b = " << a + b << endl;
	cout << "a - b = " << a - b << endl;
	cout << "a * b = " << a * b << endl;
	cout << "a / b = " << a / b << endl;

	cout << "\nConjugate a = " << a.Conjugate() << endl;
	cout << "Mod a = " << a.Mod() << endl;

	cout << "\nMas = ";
	Complex v[4]{ 1,2, Complex(2,3) };
	for (int i = 0; i < 4; i++)
		cout << v[i] << "; ";
	cout << "\n" << endl;

	Complex* pc;
	pc = new Complex(1);
	cout << "Complex(1): " << * pc << endl;
	cout << "Re: " << pc->Re << ", Im: " << pc->Im << endl;
	delete pc;
	cout << "\n" << endl;

	pc = new Complex;
	cout << "Complex: " << *pc << endl;
	cout << "Re: " << pc->Re << ", Im: " << pc->Im << endl;
	delete pc;
	cout << "\n" << endl;

	pc = new Complex(1, 2);
	cout << "Complex(1, 2): " << *pc << endl;
	cout << "Re: " << pc->Re << ", Im: " << pc->Im << endl;
	delete pc;
	cout << "\n" << endl;

	pc = new Complex[3];
	cout << "pc[1].Re for Complex[3]: ";
	cout << pc[1].Re << endl;
	delete[] pc;
	cout << "pc[1].Re for Complex[3]{0, 333}: ";
	pc = new Complex[3]{ 0, 333};
	cout << pc[1].Re << endl;
	delete[] pc;
}