#pragma once
#include <vector>
#include <string>

class WF
{ 
public:
	int* pm;
	int M;
	int N;
	std::vector<std::string> prevVersion, curVersion;
	WF() {
	}
	void Compare(std::istream& prev, std::istream& current) {
		char buf[512];
		while (prev.good()){
			M++;
			prev.getline(buf, sizeof(buf));
			prevVersion.push_back(buf);}
		while (current.good()){
			N++;
			current.getline(buf, sizeof(buf));
			curVersion.push_back(buf);}
		pm = new int[(N + 1) * (M + 1)];
		for (int i = 0; i <= M; i++)
			pm[i] = i;
		for (int i = 1; i <= N; i++)
			pm[i * (M + 1)] = i;
		int p;
		for (int i = 1; i <= M; i++)
			for (int j = 1; j <= N; j++){
				p = (curVersion[j - 1] == prevVersion[i - 1]) ? 0 : 1;
				pm[i + (M + 1) * j] = std::min(std::min(pm[(i - 1) + (M + 1) * j] + 1, pm[i + (M + 1) * (j - 1)] + 1), pm[(i - 1) + (M + 1) * (j - 1)] + p);}
	}
	int Rows() const {return N + 1;}//возвращает количество строк матрицы Вагнера-Фишера;
	int Columns() const {return M + 1;}//возвращает количество столбцов матрицы;
	int Get(int i, int j) const {return (pm[i + M * j]);}//возвращает значение i - го, j - го элемента матрицы;
	void Set(int i, int j, int val) {pm[i + M * j] = val;}//задает значение i-го,j-го элемента матрицы;
	int Distance() const {return pm[(N + 1) * (M + 1) - 1];}// возвращает расстояние между последовательностями, которыми проинициализирован объект.

	std::string Prescription() const {
		int i = M;
		int j = N;
		std::string resback = "";
		std::string res = "";
		while ((i > 0) && (j > 0)){
			if (pm[(i - 1) + (M + 1) * (j - 1)] <= std::min(pm[(i - 1) + (M + 1) * j], pm[i + (M + 1) * (j - 1)])){
				i--;
				j--;
				resback += (curVersion[j] == prevVersion[i]) ? "." : "r";}
			else if (pm[i + (M + 1) * (j - 1)] <= pm[(i - 1) + (M + 1) * j]){
				j--;
				resback += "i";}
			else{
				i--;
				resback += "d";}
		}
		if (j > 0)
			for (int k = j; k > 0; k--){resback += "i";}
		if (i > 0)
			for (int k = i; k > 0; k--){resback += "d";}
		for (int i = resback.size() - 1; i >= 0; i--) {res = res.append(1, resback[i]);};
		return res;
	}
	std::string PrevLine(int i) const {return prevVersion[i];}
	std::string CurLine(int i) const {return curVersion[i];}
	~WF(){delete[] pm;}
};

