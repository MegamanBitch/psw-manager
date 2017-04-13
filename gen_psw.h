#ifndef GEN_PSW_H
#define GEN_PSW_H

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "struttura_dati.h"
#include "debug.h"

/**
* 1) randomly generate number L which will be the exact length of your password.
* Namely, generate is so that it is greater than 8
*
* 2) randomly generate a number LL which will be the number of lowercase letters.
* LC must be in range [1..L-2]
*
* 3) randomly generate number LU for uppercase. Must be in range [1..L-LL-1]
*
* 4) LD = L-LL-LU number of uppercase digits
*
* 5) randomly generate LL lowercase letters, LU uppercase letters, and LD digits
* and keep them in a list(array)

* 6) Shuffle the array randomly
*/



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
const int RANGE_SPECIAL_CHARACTERS = 31;

/**
* Array costante con i caratteri ASCII dei caratteri speciali usati dal programma
*/
static const char SPECIAL_CHARACTERS[32] = {'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-',
                                            '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^',
                                            '_', '`', '{', '|', '}', '~'};


/**
* Array costante con le lettere lowercase
*/
static const char LOWERCASE_CHARACTERS[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                                              'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

/**
* Array costante con le lettere uppercase
*/
static const char UPPERCASE_CHARACTERS[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                                              'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

/**
* Array costante con le digits
*/
static const char DIGITS_CHARACTERS[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void generate_numbers(parameters_t &parameters, const unsigned short lun_psw);

unsigned short generate_lowercase(const unsigned short start, const unsigned short end);

unsigned short generate_uppercase(const unsigned short start, const unsigned short end);

unsigned short generate_digits(const unsigned short start, const unsigned short end);

unsigned short generate_special(const unsigned short start, const unsigned short end);


char random_password();





#endif
