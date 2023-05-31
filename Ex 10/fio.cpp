#include "fio.h"

/// <summary>
/// Выводит биты в выходной поток
/// Функция набирает полные байты из остатков предыдущего значения и битов текущего значения и выводит в поток.
/// </summary>
/// <param name="os">выходной поток</param>
/// <param name="val">значение, младшие биты которого нужно записать в поток</param>
/// <param name="sz">количество значимых битов val</param>
/// <returns>0 при успехе, -1 в случае ошибки</returns>
int outputBits(ofstream &os, int val, int sz)
{
	static unsigned char cBuffer;		// для хранения остатков предыдущего значения
	static int iNumberOfBitsInBuffer;	// для хранения длины остатка в битах
	int i2_in_power_NOBI = 1;
	// Пишем в поток последний код (остатки битов)
	if (val == -1) {
		if (iNumberOfBitsInBuffer != 0) os.put(cBuffer);
		return 0;
	}
	// Собственно кодирование
	if (val >= 0) {
		i2_in_power_NOBI <<= iNumberOfBitsInBuffer;
		for (int i = 0; i < sz; i++)
		{
			///  Оптимизировать здесь!
			// Помещаем в буфер биты входного значения
			cBuffer += i2_in_power_NOBI*(val % 2);
			val /= 2;
			i2_in_power_NOBI *= 2;
			iNumberOfBitsInBuffer++;
			// Если заполнен байт, то пишем его в выходной поток, сбрасываем буфер и начинаем накапливать следующий байт
			if (iNumberOfBitsInBuffer >= 8) {
				os.put(cBuffer);
				cBuffer = (unsigned char)0;
				iNumberOfBitsInBuffer = 0;
				i2_in_power_NOBI = 1;
			}
		}
		return 0;
	}
	return -1;
}
/// <summary>
/// Читает биты выходного потока
/// Функция набирает полные байты из остатков предыдущего значения и битов текущего значения и выводит в поток.
/// </summary>
/// <param name="is">входной поток</param>
/// <param name="sz">количество битов для чтения <= 30 </param>
/// <returns>значение в виде целого при успехе, -1 в случае ошибки</returns>
int inputBits(ifstream &is, int sz)
{
	static unsigned char cBuffer;
	static int iNumberOfBitsInBuffer = 0;

	int i2_in_power_i = 1;
	int iVal = 0;
	for (int i = 0; i<sz; i++) {
		if (iNumberOfBitsInBuffer == 0) {
			is.get((char&)cBuffer);
			if (is.eof())
				return -1;
			iNumberOfBitsInBuffer = 8;
		}
		iVal += (cBuffer % 2)*i2_in_power_i;
		cBuffer /= 2;
		iNumberOfBitsInBuffer--;
		i2_in_power_i *= 2;
	}
	return iVal;
}