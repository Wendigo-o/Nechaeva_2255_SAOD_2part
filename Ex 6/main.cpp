#include <iostream>
#include "main.h"

int main(){
//хешы и сдвиги
  PH* test = new PH(5); // длина 5
  size_t h1 = test -> Hash("abcde");
  size_t h2 = test -> Hash("edabc");
  size_t sdvig = test -> Shift(h1, 'a', 'h');
  if(h2 == sdvig)
      { std::cout << "  YES";} 
  else 
      { std::cout << "  NO"; } 
  std::cout << std::endl;
  delete test;
  std::cout << std::endl;

  PH* test2 = new PH(7); // длина 7
  size_t h3 = test2 -> Hash("aabbccd");
  size_t h4 = test2 -> Hash("bbccaad");
  size_t sdvig2 = test2 -> Shift(h3, 'a', 'd');
  if(h4 == sdvig2)
      { std::cout << "  YES";} 
  else 
      { std::cout << "  NO"; } 
  std::cout << std::endl;
  delete test2;
  std::cout << std::endl;

  PH* test3 = new PH(20); // длина 20
  size_t h5 = test3 -> Hash("ABCABCBCBABCCBBABCCA");
  size_t h6 = test3 -> Hash("BAABCCCBCBACCBCBACAB");
  size_t sdvig3 = test3 -> Shift(h5, 'C', 'B');
  if(h6 == sdvig3)
      { std::cout << "  YES";} 
  else 
      { std::cout << "  NO"; } 
  std::cout << std::endl;
  delete test3;
  std::cout << std::endl;

  //поиск в тексте с неск. хешами
  char stroka[] = "aaabccacbbbacaba";
  const char* podstroka[] = {"aaa", "bbb", "cac", "aba"};
  std::cout << "stroka: ";
  for(int i=0; i<strlen(stroka); i++)
      { std::cout << stroka[i]; } 
      std::cout << std::endl << "podstroka: ";
  for(size_t j=0; j<4; j++){
      for(int i=0; i<strlen(podstroka[j]); i++)
          { std::cout << podstroka[j][i]; } 
          std::cout << " | ";
  } std::cout << std::endl;
  find_in_stroka(stroka, podstroka, 4);
  return 0;
}
