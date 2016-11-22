#ifndef ENTROPY_H
#define ENTROPY_H

#include <iostream>
#include <cmath>
#include <cstring>
#include "struttura_dati.h"
#include "funzioni.h"

/*
* enumerato per la classificazione dei tipi di caratteri
*/
enum type_of_character{
  LOWERCASE,
  UPPERCASE,
  DIGIT,
  SPECIAL_CHARACTER,
};

struct entropy_t {
  unsigned short has_lowercase, has_uppercase, has_digit, has_specialCaracter;
  unsigned short ris;
};

void entropy_inizializza(entropy_t &e);
double get_entropy(const gchar *c);
int pool_of_character(const gchar *car);
void entropy_azzera();












#endif
