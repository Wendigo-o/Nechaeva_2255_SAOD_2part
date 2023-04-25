#pragma once
#include "_data.h"

class Array
{
	int rows, cols;
	friend class _data;
	_data* pDataRef;
public:
	// п.5
	Array(int m, int n, int* p = 0) {
		rows = m; cols = n;
		pDataRef = new _data(m * n, p);
		std::cout << this << " Array created with " << rows << " x " << cols << " shape | data: " << pDataRef << std::endl;
	}
	// п.6
	Array(const Array& a) {
		pDataRef = a.pDataRef;
		pDataRef->AddRef();
		std::cout << this << " Array copied from " << &a << std::endl;
	}
	// п.8
	int Rows() const { return rows; }
	int Cols() const { return cols; }

	// п.9
	int& Item(int i, int j) {
		if (i >= 0 && i <= rows - 1 && j >= 0 && j <= cols - 1) {return pDataRef->pData[cols * i + j]; }
		else {
			std::cout << "i = " << i << " | rows = " << rows - 1 << " | j = " << j << " | cols = " << cols - 1 << std::endl;
			throw std::out_of_range("throw out of range");
		}
	}
	// п.10
	int Item(int i, int j) const {
		if (i >= 0 && i <= rows - 1 && j >= 0 && j <= cols - 1) {
			int elem = pDataRef->pData[cols * i + j];
			return elem;
		}
		else {
			throw std::out_of_range("throw out of range");
		}
	}
	//вариант 7, п. 1
	Array* Reshape(int m, int n) {
		if (m * n == rows * cols) {
			Array* reshaped = new Array(m, n);
			reshaped->pDataRef->Release();
			reshaped->pDataRef = this->pDataRef;
			return reshaped;
		}
		else {
			throw std::invalid_argument("Array & View size mismatch");
		}
	}
	// п.7
	~Array() {
		this->pDataRef->Release();
		std::cout << this << " Array deleted" << std::endl;
	}
};
// п.11
std::ostream& operator << (std::ostream& os, Array& t) {
	int rows = t.Rows();
	int cols = t.Cols();
	for (int i = 0; rows - i != 0; i++) {
		os << "[ ";
		for (int j = 0; cols - j != 0; j++) {
			int num = t.Item(i, j);
			os << num;
			if (j != cols - 1) { os << ", "; }
		}
		os << " ]" << std::endl;
	}

	return os;
}

