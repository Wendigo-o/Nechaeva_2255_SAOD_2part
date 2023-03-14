#pragma once
#include <iostream>
#include <cmath> //библиотека с математическими функциями
using namespace std;

class Complex
{
	public: double Re, Im;
	
	//конструктор
	Complex(double re = 0, double im=0)
	{
		this -> Re = re; 
		this -> Im = im;
	}

	Complex operator +(const Complex& c)const
	{
		return Complex(Re + c.Re, Im + c.Im);
	}

	Complex operator -(const Complex& c)const
	{
		return Complex(Re - c.Re, Im - c.Im);
	}

	Complex operator *(const Complex& c)const
	{
		return Complex(Re * c.Re - Im * c.Im, Re * c.Im + c.Re * Im);
	}

	Complex operator /(const Complex& c)const
	{
		return Complex((Re * c.Re + Im * c.Im) / (c.Re * c.Re + c.Im * c.Im), (-Re * c.Im + c.Re * Im) / (c.Re * c.Re + c.Im * c.Im));
	}

	Complex Conjugate() {
		return Complex(Re, -Im);
	}

	Complex Mod() {
		return sqrt(pow(Re, 2) + pow(Im, 2));
	}

	Complex Arg() {
		if (sqrt(pow(Re, 2) + pow(Im, 2))) {
			return 0;
		}
		else if (Re > 0)
		{
			return atan(Im / Re);
		}
		else if (Re < 0)
		{
			if (Im >= 0)
			{
				return acos(-1) + atan(Im / Re);
			}
			else
			{
				return -acos(-1) - atan(Im / Re);
			}
		}
		else
		{
			if (Im > 0)
			{
				return acos(0);
			}
			if (Im < 0)
			{
				return -acos(0);
			}
		}
	}

};

//переопределение операции << 
inline ostream& operator << (ostream& o, const Complex& c)
{
	return o << '(' << c.Re << ", " << c.Im << ')';
}


