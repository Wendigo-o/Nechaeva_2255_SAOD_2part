#include <iostream>
#include <cassert>
#include "LZ77.h"
#include "fio.h"
#include "OptHashTable.h"

#define LEN_BITS 6						// Размер поля длины в коде (bit)
#define OFF_BITS 14						// Размер поля смещения в коде (bit)
#define WND_SZ ((1<<OFF_BITS)-1)		// Размер окна словаря
#define LA_BUF_SZ ((1<<LEN_BITS)-1)	+ 1 // Размер буфера кодирования (look ahead)
#define BUF_SZ 2*WND_SZ + LA_BUF_SZ	// Размер памяти под буфер чтения (2 размера скользящего окна словаря + буфер кодирования)

/// <summary>
/// Выводит код в поток 
/// </summary>
/// <param name="os">Входной поток</param>
/// <param name="wnd">скользящее окно</param>
/// <param name="r">дескриптор найденной цепочки</param>
/// <param name="laIdx">индекс начала буфера кодирования в окне</param>
void outputCode(ofstream& os, unsigned char* wnd, find_result r, int laIdx)
{
	if (r.len >= 2){
		outputBits(os, r.len, LEN_BITS);
		outputBits(os, r.idx, OFF_BITS);
		outputBits(os, wnd[laIdx + r.len], 8);
	}
	else{
		// Специальное кодирования цепочек длины <2 // (l, ch) (l, ch, ch)
		outputBits(os, r.len, LEN_BITS);
		for (int i = 0; i <= r.len; i++)
			outputBits(os, (int)wnd[laIdx + i], 8);
	}
}

/// <summary>
/// Находит максимальный общий префикс 2-х строк, не больше максимальной длины 
/// </summary>
/// <param name="w">одна из строк</param>
/// <param name="l">вторая строка</param>
/// <param name="max">максимальная длина</param>
/// <returns>длину общего префикса</returns>
inline int prefix(unsigned char* w, unsigned char* l, int max)
{
	unsigned char* p = w, * pm = w + max;
	while (p < pm && *p == *l) { p++; l++; }
	return (p - w);
}


/// <summary>
/// Находит наилучшее (наиболее длинное) совпадение префикса буфера кодирования и подстроки в скользящем окне.
/// </summary>
/// <param name="wnd">буфер чтения</param>
/// <param name="w_idx">индекс начала скользящего окна в буфере чтения</param>
/// <param name="lab">буфер кодирования</param>
/// <param name="lab_sz">размер буфера кодирования</param>
/// <returns>лучшее найденное совпадение</returns>
find_result findTheBest(unsigned char* buf, int w_idx, unsigned char* lab, int lab_sz)
{
	if (buf == lab || lab_sz < 2)
		return find_result(lab - buf);
	int maxIdx = -1, mLen = 0;
	for (unsigned char* p = buf + w_idx; p < lab; p++){
		int len = prefix(p, lab, lab_sz-1);
		if (len > mLen){
			maxIdx = lab - p;
			mLen = len;
		}
	}
	return find_result(maxIdx, mLen);
}

/// <summary>
/// Выполняет компрессию входного потока в выходной 
/// </summary>
/// <param name="is">входной поток</param>
/// <param name="os">выходной поток</param>
/// <returns>длину is в случае успеха и -1 при ошибке</returns>
int CompressFile(ifstream& is, ofstream& os)
{
	OptHashTable hashTable;
	// Обработано байтов
	int nProc = 0;
	unsigned char* inBuf = new unsigned char[BUF_SZ];
	int nInBuf = BUF_SZ;
	is.read((char*)inBuf, BUF_SZ);
	if (!is)
		nInBuf = is.gcount();
	// Если файл короткий, то вообще не кодируем
	if (nInBuf < 8)	{
		for (int i = 0; i < nInBuf; i++) {
			outputBits(os, (int)*(inBuf + i), 8);
		}
		return 0;
	}

	int wIdx = 0, laIdx = 0, laSz = min(nInBuf - laIdx, LA_BUF_SZ);
	while (laSz > 2 || is)
	{
		assert(nInBuf - laIdx > 1);
		// find_result r = findTheBest(inBuf, wIdx, inBuf + laIdx, laSz);
		find_result r = hashTable.FindTheBest(inBuf+wIdx, inBuf + laIdx, laSz);
		// cout << r.len << " " << r.idx << endl;
		if (laIdx + r.len == nInBuf)
			r.len--;
		outputCode(os, inBuf, r, laIdx);
		nProc += r.len + 1;
		// Обработаны r.len+1 байтов. Смещаемся дальше.
		laIdx += r.len + 1;
		laSz = min(nInBuf - laIdx, LA_BUF_SZ);

		if (laIdx - wIdx > WND_SZ)
			wIdx = laIdx - WND_SZ;
		hashTable.FeedTable(inBuf + laIdx, r.len + 1);
		//Прошли часть буфера чтения, равное размеру словаря. Нужно продвинуться по буферу чтения.
		if (wIdx >= WND_SZ)
		{
			//Копируем рабочую часть буфера в начало
			// cout << "here 2" << endl;
			memmove(inBuf, inBuf + wIdx, nInBuf - wIdx);
			// дочитываем из потока и вычисляем количество в буфере
			if (is){
				is.read((char*)inBuf + (nInBuf - wIdx), wIdx);
				if (!is)
					nInBuf = nInBuf - wIdx + is.gcount();
			}
			else // В потоке уже нет данных. 
			nInBuf -= wIdx;
			laIdx -= wIdx;
			wIdx = 0;
			hashTable.UpdateTable(inBuf + wIdx, nInBuf - wIdx);
		}

	}

	// while не до 0! Могут остаться пара байтов...
	if (laSz){
		outputCode(os, inBuf, find_result(0, laSz - 1), laIdx);
	}
	// Чистим буфер вывода
	if (outputBits(os, -1, 0))
		return -1;
	return nProc + laSz;
}


/// <summary>
/// Читает длину очередного кода входного потока
/// </summary>
/// <param name="is">входной поток</param>
/// <returns>длину в случае успеха и -1 при ошибке</returns>

int getLength(ifstream &is){return inputBits(is, LEN_BITS);}
/// <summary>
/// Читает смещение очередного кода входного потока
/// </summary>
/// <param name="is">входной поток</param>
/// <returns>смещение в случае успеха и -1 при ошибке</returns>

int getOffset(ifstream &is{return inputBits(is, OFF_BITS);}

/// <summary>
/// Читает байт очередного кода входного потока
/// </summary>
/// <param name="is">входной поток</param>
/// <returns>байт в случае успеха и -1 при ошибке</returns>

int getByte(ifstream &is){return inputBits(is, 8);}

/// <summary>
/// Выполняет декомпрессию входного потока в выходной 
/// </summary>
/// <param name="is">входной поток</param>
/// <param name="os">выходной поток</param>
/// <returns>длину после декомпресии в случае успеха и -1 при ошибке</returns>

int DecompressFile(ifstream &is, ofstream &os)
{
	unsigned char *inBuf = new unsigned char[BUF_SZ] {0};
	unsigned char *pos = inBuf;
	int nInBuf = 0;
	int nWritten = 0;
	while (!is.eof())
	{
		int len = getLength(is);
		if (len == -1)
			break;
		if (len<2){
			for (int i = 0; i <= len; i++){
				int res = getByte(is);
				if (res == -1){
					break;
				}
				char byte = res;
				*pos++ = byte;
				assert(pos - inBuf <= BUF_SZ);
			}
		}
		else {
			int off = getOffset(is);
			if (off == -1){
				break;
			}
			else
			{
				int res = getByte(is);
				if (res == -1){
					break;
				}
				char byte = res;

				unsigned char *p = pos - off;
				for (int i = 0; i < len; i++) {
					*pos++ = *p++;
				}
				*pos++ = byte;
				assert(pos - inBuf <= BUF_SZ);
			}
		}
		if ((pos - inBuf) >= (2 * WND_SZ)){
			assert(pos - inBuf <= BUF_SZ);
			int nw = (pos - inBuf) - WND_SZ;
			os.write((char*)inBuf, nw);
			memmove((char*)inBuf, (char*)inBuf + nw, WND_SZ);
			pos = inBuf + WND_SZ;
			nWritten += nw;
		}
	}
	assert(pos - inBuf<BUF_SZ);
	os.write((char*)inBuf, pos - inBuf);
	nWritten += pos - inBuf;
	return nWritten;
}
