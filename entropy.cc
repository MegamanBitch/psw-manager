#include "entropy.h"

int get_entropy(password_t &p){
  unsigned short num_caratteri = strlen(p.stringa);
  for (size_t i = 0; i < num_caratteri; i++) {
    pool_of_character(p.stringa[i]);
  }

}

int pool_of_character(char c){

}
