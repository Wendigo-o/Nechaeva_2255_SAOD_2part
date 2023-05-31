#include "fio.h"

/// <summary>
/// ������� ���� � �������� �����
/// ������� �������� ������ ����� �� �������� ����������� �������� � ����� �������� �������� � ������� � �����.
/// </summary>
/// <param name="os">�������� �����</param>
/// <param name="val">��������, ������� ���� �������� ����� �������� � �����</param>
/// <param name="sz">���������� �������� ����� val</param>
/// <returns>0 ��� ������, -1 � ������ ������</returns>
int outputBits(ofstream &os, int val, int sz)
{
	static unsigned char cBuffer;		// ��� �������� �������� ����������� ��������
	static int iNumberOfBitsInBuffer;	// ��� �������� ����� ������� � �����
	int i2_in_power_NOBI = 1;
	// ����� � ����� ��������� ��� (������� �����)
	if (val == -1) {
		if (iNumberOfBitsInBuffer != 0) os.put(cBuffer);
		return 0;
	}
	// ���������� �����������
	if (val >= 0) {
		i2_in_power_NOBI <<= iNumberOfBitsInBuffer;
		for (int i = 0; i < sz; i++)
		{
			///  �������������� �����!
			// �������� � ����� ���� �������� ��������
			cBuffer += i2_in_power_NOBI*(val % 2);
			val /= 2;
			i2_in_power_NOBI *= 2;
			iNumberOfBitsInBuffer++;
			// ���� �������� ����, �� ����� ��� � �������� �����, ���������� ����� � �������� ����������� ��������� ����
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
/// ������ ���� ��������� ������
/// ������� �������� ������ ����� �� �������� ����������� �������� � ����� �������� �������� � ������� � �����.
/// </summary>
/// <param name="is">������� �����</param>
/// <param name="sz">���������� ����� ��� ������ <= 30 </param>
/// <returns>�������� � ���� ������ ��� ������, -1 � ������ ������</returns>
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