#ifndef ENTROPY_H
#define ENTROPY_H

#include <iostream>
#include <cmath>
#include <cstring>
#include "struttura_dati.h"
#include "funzioni.h"

enum type_of_character{
  LOWERCASE,
  UPPERCASE,
  ALPHANUMERIC,
  
}

int get_entropy(password_t &p);
int pool_of_character(char c);












#endif
