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
  DIGIT,
  SPECIAL_CHARACTER,
};

int get_entropy(const gchar *c);
int pool_of_character(const gchar *car);












#endif
