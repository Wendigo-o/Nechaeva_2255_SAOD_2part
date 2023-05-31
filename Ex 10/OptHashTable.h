#pragma once
#include "find_result.h"
#include <iostream>
using namespace std;
#define TBL_SZ 0x3FFF
class OptHashTable
{
private:
	/// <summary>
	/// Узел списка hash-таблицы
	/// </summary>
	struct node {
		unsigned char *idx; //указатель на данные в буфере чтения
		node* pNext;
		node(unsigned char* i, node* next = 0) :idx(i), pNext(next) {}
	};

	node** nodes; // массив списков. Все узлы одного списка имеют одинаковый хеш = индексу в nodes

	/// <summary>
	/// hash-функция
	/// </summary>
	/// <param name="str">указатель на ключ (2 байта)</param>
	/// <returns>значение [0-TBL_SZ]</returns>
	inline unsigned short hash(unsigned char* str) {
		return *(unsigned short*)str & TBL_SZ;
	}

	/// <summary>
	/// Находит максимальный общий префикс 2-х строк, не больше максимальной длины 
	/// </summary>
	/// <param name="w">одна из строк</param>
	/// <param name="l">вторая строка</param>
	/// <param name="max">максимально допустимая длина совпадения</param>
	/// <returns>длину максимального общего префикса (не более max)</returns>
	inline static int prefix(unsigned char* w, unsigned char* l, int max) {
		unsigned char* p = w;
		unsigned char* pm = w + max;

		while (*p == *l && p < pm ) {
			p++; l++;
		}
		return (p - w);
	}
	/// <summary>
	/// Добавляет узел в таблицу.
	/// private, т.к. важен порядок добавления.
	/// </summary>
	/// <param name="buf">указатель на ключ (адрес в буфере чтения)</param>
	inline void insertNode(unsigned char* buf)
	{
		int h = hash(buf);
		nodes[h] = new node(buf, nodes[h]);
	}

	/// <summary>
	/// Удаляет хвост списка. Зануляет переданную ссылку
	/// </summary>
	/// <param name="p">начало хвоста</param>
	inline void remove_tail(node* (&p))
	{
		node* v = p;
		while (v) {
			node* prev = v;
			v = v->pNext;
			delete prev;
		}
		if(p) p = 0;
	}
public:
	OptHashTable() {
		nodes = new node * [TBL_SZ+1] {0};
	}
	~OptHashTable() {
		for (int i = 0; i < TBL_SZ+1; i++)
			remove_tail(nodes[i]);
		delete[]nodes;
	}
	/// <summary>
	/// Сдвигает адреса. Применяется после перемещения буфера чтения. 
	/// Узлы с адресами, которые "ушли из окна" удаляются.
	/// </summary>
	/// <param name="wnd">начало окна, которое будет перемещено в начало буфера чтения</param>
	/// <param name="shift">сдвиг окна, который будет выполнен в буфере чтения</param>
	void UpdateTable(unsigned char* wnd, int shift)
	{
		for (int i = 0; i < TBL_SZ+1; i++){
			// cout << "here" << endl;
			node* nd = nodes[i];
			while(nd){
				nd->idx = nd->idx - shift;
				if (nd->idx < wnd){ remove_tail(nd->pNext);}
				// cout << "before next" << endl;
				if(nd)
					nd = nd->pNext;
				// cout << "after next" << endl;
			}
		}

		// Доработать 2
		//1. Пробехаться по всей таблице и сместить поля idx на -shift
		//2. Если полученное значение < wnd, то удалить все последующие узлы таблицы. Использовать remove_tail
	}

	/// <summary>
	/// Заполняет таблицу данными в нужном порядке (от дальних к ближайшим)
	/// </summary>
	/// <param name="lab">Look Ahead буфер</param>
	/// <param name="size">размер блока окна, примыкающий к lab, которым нужно "накормить" таблицу</param>
	void FeedTable(unsigned char* lab, int size)
	{
		for (int i = size; i > 0; i--)
			insertNode(lab - i);
		// cout << "here" << " " << lab << size << endl;
	}

	/// <summary>
	/// Находит наибольшее совпадение префикса lab в w_buf
	/// </summary>
	/// <param name="w_buf">буфер бегущего окна</param>
	/// <param name="lab">начало буфера кодирования. lab - w_buf = размер ссылочного словаря</param>
	/// <param name="lab_sz">текущий размер lab</param>
	/// <returns>код наилучшего совпадения</returns>
	find_result FindTheBest(unsigned char* w_buf, unsigned char* lab, int lab_sz) {
		// Граничные случаи: размер окна lab-w_buf == 0 или lab_sz == 1.
		if (w_buf == lab || lab_sz < 2)
			return find_result(lab - w_buf);
		int mIdx = -1, mLen = 0;
		int h = hash(lab);
		node* nd = nodes[h];
		while(nd && nd->idx >= w_buf){
			int len = prefix(nd->idx, lab, lab_sz-1);
			// cout << len << endl;
			// cout << nd->idx << endl;
			// cout << lab << endl;
			if (len > mLen){
				mIdx = lab - nd->idx;
				mLen = len;
			}
			nd = nd->pNext;
		}
		return find_result(mIdx, mLen);
		// Доработать здесь! (1)
		// вычислить хеш и найти соответствующий ему список,
		// пробежать по списку и найти узел с максимальным совпадением префикса node->idx и lab,
		// но только для тех узлов, у которых idx >= начала окна (т.е. указывает внутрь окна)
		// 
		// вычислить и вернуть find_result. Первым параметром смещение от lab, вторым длина совпадения

	}
};
