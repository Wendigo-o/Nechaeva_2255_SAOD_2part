#include <iostream>
#include <cstring>
#include <cmath>

class PH{
  const unsigned short k = 2;
  const unsigned short Q = 65521;

  public:
    size_t len;
    unsigned long long* kp;

    PH(size_t L){
      std::cout << "PH created: ";
      len = L+1;
      kp = new unsigned long long[len];
      for(size_t i=0; i<len; i++){
        unsigned long long n = pow(k, i);
        kp[i] = n % Q;
        std::cout << kp[i] << " ";
      }
      std::cout << std::endl;
    }

    ~PH(){
      std::cout << "PH deleted" << std::endl;
      delete[] kp;
    }

    size_t Hash(const char* s){
      size_t h = 0;
      size_t num;
      for(size_t i=0; i<len-1; i++){
        num = s[i];
        h += num * kp[len-2-i];}
      h = h % Q;
      std::cout << "Created hash = " << h << " for str "; 
      for(size_t i=0; i<len-1; i++){ std::cout << s[i]; }; 
      std::cout << std::endl;  
      return h;
    }
    //Shifted - сдвиг
    size_t Shift(size_t h, char pref, char suff){
      size_t num1 = pref;
      size_t num2 = suff;
      size_t hash = ((k * h) - (num1 * kp[len-1]) + num2) % Q;
      std::cout << "Shifted hash " << h << " to " << hash; 
      return hash;
    }
};
    //podtext - подстрока
void find_in_text(char* text, const char** podtext, size_t podtext_count){
  size_t text_len = strlen(text);
  size_t podtext_len = strlen(podtext[0]);
  PH* pol_hash = new PH(podtext_len);
  size_t hashes[5]; 
  for(size_t i=0; i< podtext_count; i++){
    hashes[i] = pol_hash -> Hash(podtext[i]);
  } std::cout << std::endl;
  size_t current_hash;
  char* current_podtext = new char[podtext_len+1];
  
  for(size_t i=0; i<(text_len- podtext_len)+1; i++){
    strncpy(current_podtext, &text[i], podtext_len); current_podtext[podtext_len] = 0;
    current_hash = pol_hash -> Hash(current_podtext);
    for(size_t j=0; j< podtext_count; j++){
      bool flag = false;
      if(current_hash == hashes[j]){
        if(strcmp(current_podtext, podtext[j]) == 0){
          std::cout << "podstroka " << podtext[j] << " index " << i << std::endl << std::endl;}}}}

  delete pol_hash;
}
