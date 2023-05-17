#include <iostream>
#include <list>
#include <string.h>
#include <chrono>
#include <unordered_set>
#include "main.h"
using namespace std;

int main() {
  size_t N = 1000;
  list<string> list1, list2, common;
  for(size_t i=0; i<N; i++) {
    list1.push_back(getRandom(7));
    list2.push_back(getRandom(7));
  }
  
  for(size_t i=0; i<N/2; i++) {
    common.push_back(getRandom(7));
  }
  for (auto &c : common) {
		int i = rand() % list1.size();
		int j = rand() % list2.size();
		for(auto it=list1.begin(); it!=list1.end(); it++, i--) {
			if (i == 0) {
				list1.insert(it, c);
				break;}}
    for(auto it=list2.begin(); it!=list2.end(); it++, j--) {
			if (j == 0) {
				list2.insert(it, c);
				break;}}}
  int count = 0;
  auto start1 = chrono::steady_clock::now();
  for(string n:list1) {
    for(string m:list2) {
      if(n.compare(m) == 0) {count++;}
    }
  }
  auto stop1 = chrono::steady_clock::now();
  auto dt1 = chrono::duration_cast<chrono:: microseconds>(stop1 - start1).count();
  std::cout << endl << count << " " << "list: " << dt1 << " ms" << endl;
  count = 0;
  unordered_set<string> set1, set2;
  for (auto iter1 = list1.begin(); iter1 != list1.end(); iter1++) {set1.insert(*iter1);}
  for (auto iter2 = list2.begin(); iter2 != list2.end(); iter2++) {set2.insert(*iter2);}
  auto start2 = chrono::steady_clock::now();
  for(string n:set1) {
    if(set2.contains(n)) {count++;}
  }
  auto stop2 = chrono::steady_clock::now();
  auto dt2 = chrono::duration_cast<chrono:: microseconds>(stop2 - start2).count();
  std::cout << endl << count << " unordered_set: " << dt2 << " ms" << endl;



  return 0;
}
