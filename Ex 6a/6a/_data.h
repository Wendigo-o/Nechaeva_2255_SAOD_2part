#pragma once
#include <iostream>

class _data
{
    int* pData;
    int nCount;

    friend class Array;

    _data(int sz, int* p = 0) {
        nCount = 1;
        pData = new int[sz];
        if (p == 0) std::fill(pData, pData + sz, 0);
        else pData = p;

    }

    void AddRef() {
        nCount++;
        std::cout << this << " _data AddRef count: " << nCount << std::endl;
    }
    void Release() {
        nCount--;
        std::cout << this << " _data Release count: " << nCount << std::endl;
        if (nCount == 0) {
            delete this;
        }
    }
};


