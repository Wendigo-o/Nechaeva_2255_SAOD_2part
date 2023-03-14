#pragma once
using namespace std;

class Str
{
	char* m_pszText;
public:
	Str() 
	{
		m_pszText = new char[1]{0};
	}

	Str(const char* p) 
	{
		if (p) {
			m_pszText = new char[strlen(p) + 1];
			strcpy_s(m_pszText, strlen(p) + 1, p);
		}
		else
			m_pszText = new char[1]{0};
	}

	operator const char* ()const { return m_pszText; } //вывод на консоль

	Str(const Str& s) //Константная ссылка на объект , копирование
	{
		m_pszText = new char[strlen(s.m_pszText) + 1];
		strcpy_s(m_pszText,
			strlen(s.m_pszText) + 1,
			s.m_pszText);
	}

	//операция присваивания
	const Str& operator = (const Str& s) //Константная ссылка на объект
	{
		if (&s == this) return *this;
		delete[] m_pszText;	 //Освобождаем текущие данные					//Дальше просто копирование
		m_pszText = new char[strlen(s.m_pszText) + 1];
		strcpy_s(m_pszText,
			strlen(s.m_pszText) + 1,
			s.m_pszText);
		return *this;
	}

	Str& operator +=(const char* sz)
	{
		char* newStr = new char[strlen(m_pszText) + strlen(sz) + 1];
		int i = 0;
		for (; i < strlen(m_pszText); i++) newStr[i] = m_pszText[i];
		for (int j = 0; j < strlen(sz); i++, j++) newStr[i] = sz[j];
		newStr[i] = '\0';

		delete[] this->m_pszText;
		m_pszText = newStr;
		newStr = nullptr;
		return *this;
	}
	Str operator +(const char* sz) const
	{
		Str newStr = new char[strlen(m_pszText) + strlen(sz) + 1];
		int i = 0;
		for (; i < strlen(m_pszText); i++) newStr.m_pszText[i] = m_pszText[i];
		for (int j = 0; j < strlen(sz); i++, j++) newStr.m_pszText[i] = sz[j];
		newStr.m_pszText[i] = '\0';

		return newStr;
	}

	~Str() { delete[]m_pszText; }

};


