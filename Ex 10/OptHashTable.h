#pragma once
#include "find_result.h"
#include <iostream>
using namespace std;
#define TBL_SZ 0x3FFF
class OptHashTable
{
private:
	/// <summary>
	/// ���� ������ hash-�������
	/// </summary>
	struct node {
		unsigned char *idx; //��������� �� ������ � ������ ������
		node* pNext;
		node(unsigned char* i, node* next = 0) :idx(i), pNext(next) {}
	};

	node** nodes; // ������ �������. ��� ���� ������ ������ ����� ���������� ��� = ������� � nodes

	/// <summary>
	/// hash-�������
	/// </summary>
	/// <param name="str">��������� �� ���� (2 �����)</param>
	/// <returns>�������� [0-TBL_SZ]</returns>
	inline unsigned short hash(unsigned char* str) {
		return *(unsigned short*)str & TBL_SZ;
	}

	/// <summary>
	/// ������� ������������ ����� ������� 2-� �����, �� ������ ������������ ����� 
	/// </summary>
	/// <param name="w">���� �� �����</param>
	/// <param name="l">������ ������</param>
	/// <param name="max">����������� ���������� ����� ����������</param>
	/// <returns>����� ������������� ������ �������� (�� ����� max)</returns>
	inline static int prefix(unsigned char* w, unsigned char* l, int max) {
		unsigned char* p = w;
		unsigned char* pm = w + max;

		while (*p == *l && p < pm ) {
			p++; l++;
		}
		return (p - w);
	}
	/// <summary>
	/// ��������� ���� � �������.
	/// private, �.�. ����� ������� ����������.
	/// </summary>
	/// <param name="buf">��������� �� ���� (����� � ������ ������)</param>
	inline void insertNode(unsigned char* buf)
	{
		int h = hash(buf);
		nodes[h] = new node(buf, nodes[h]);
	}

	/// <summary>
	/// ������� ����� ������. �������� ���������� ������
	/// </summary>
	/// <param name="p">������ ������</param>
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
	/// �������� ������. ����������� ����� ����������� ������ ������. 
	/// ���� � ��������, ������� "���� �� ����" ���������.
	/// </summary>
	/// <param name="wnd">������ ����, ������� ����� ���������� � ������ ������ ������</param>
	/// <param name="shift">����� ����, ������� ����� �������� � ������ ������</param>
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

		// ���������� 2
		//1. ����������� �� ���� ������� � �������� ���� idx �� -shift
		//2. ���� ���������� �������� < wnd, �� ������� ��� ����������� ���� �������. ������������ remove_tail
	}

	/// <summary>
	/// ��������� ������� ������� � ������ ������� (�� ������� � ���������)
	/// </summary>
	/// <param name="lab">Look Ahead �����</param>
	/// <param name="size">������ ����� ����, ����������� � lab, ������� ����� "���������" �������</param>
	void FeedTable(unsigned char* lab, int size)
	{
		for (int i = size; i > 0; i--)
			insertNode(lab - i);
		// cout << "here" << " " << lab << size << endl;
	}

	/// <summary>
	/// ������� ���������� ���������� �������� lab � w_buf
	/// </summary>
	/// <param name="w_buf">����� �������� ����</param>
	/// <param name="lab">������ ������ �����������. lab - w_buf = ������ ���������� �������</param>
	/// <param name="lab_sz">������� ������ lab</param>
	/// <returns>��� ���������� ����������</returns>
	find_result FindTheBest(unsigned char* w_buf, unsigned char* lab, int lab_sz) {
		// ��������� ������: ������ ���� lab-w_buf == 0 ��� lab_sz == 1.
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
		// ���������� �����! (1)
		// ��������� ��� � ����� ��������������� ��� ������,
		// ��������� �� ������ � ����� ���� � ������������ ����������� �������� node->idx � lab,
		// �� ������ ��� ��� �����, � ������� idx >= ������ ���� (�.�. ��������� ������ ����)
		// 
		// ��������� � ������� find_result. ������ ���������� �������� �� lab, ������ ����� ����������

	}
};
