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
/*
* Funzione che ritorna il valore dell'entropia aggiunta da un singolo carattere
*/
double get_entropy(const gchar *c);

/*
* Funzione che, dato un carattere, ritorna il tipo come descritto nell'enumeratore
*/
int pool_of_character(const gchar *car);

/*
* Funzione che azzera tutte le variabili
*/
void entropy_azzera();












#endif
