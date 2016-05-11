#include "entropy.h"

int get_entropy(string &s){
  unsigned short num_caratteri = s.length();
  for (size_t i = 0; i < num_caratteri; i++) {
    pool_of_character(s[i]);
  }
  return 0;
}

int pool_of_character(char c){
  return 0;
}
