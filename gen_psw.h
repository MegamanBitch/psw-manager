#ifndef GEN_PSW_H
#define GEN_PSW_H

#include <iostream>
#include <cstdlib>
#include "struttura_dati.h"
#include "debug.h"

/**
* Costante che descrive il numero di lettere maiuscole
*/
const int RANGE_UPPERCASE = 25;

/**
* Costante che descrive il numero di lettere minuscole
*/
const int RANGE_LOWERCASE = 25;

/**
* Costante che descrive il numero di numeri
*/
const int RANGE_DIGITS = 9;

/**
* Costante che descrive il numero di caratteri speciali
*/
const int RANGE_SPECIAL_CHARACTERS = 22;

/**
* Costante che descrive il numero delle parentesi
*/
const int RANGE_BRACKETS = 8;

/**
* Array costante con i caratteri ASCII delle parentesi usate dal programma
*/
static const int BRACKETS[8] = {40, 41, 60, 62, 91, 93, 123, 125};

/**
* Array costante con i caratteri ASCII dei caratteri speciali usati dal programma
*/
static const int SPECIAL_CHARACTERS[22] = {33, 34, 35, 36, 37, 38, 39, 42, 43, 44, 46, 47, 58, 59, 61, 63, 64,
                                            92, 94, 96, 124, 126};

void flag_inizializza(flag_parameters_t &PARAMETERS);
int getRandom_char(flag_parameters_t &PARAMETERS, unsigned short lun_psw);






#endif
