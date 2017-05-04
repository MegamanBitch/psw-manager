#ifndef ENTROPY_H
#define ENTROPY_H

#include <iostream>
#include <cmath>
#include <cstring>
#include "struttura_dati.h"
#include "funzioni.h"

/**
* @file
* Library for calculating password entropy
*/

/*
* @enum type_of_character
* @brief enum for the classification of characters
*/
enum type_of_character{
  LOWERCASE,
  UPPERCASE,
  DIGIT,
  SPECIAL_CHARACTER,
};

/**
* @var ::type_of_character::LOWERCASE
* lowercase characters
* @var ::type_of_character::UPPERCASE
* uppercase characters
* @var ::type_of_character::DIGIT
* digits
* @var ::type_of_character::SPECIAL_CHARACTER
* special characters
*/

/**
* Entropy structure:
* @struct entropy_t entropy.h 'entropy.h
* @brief type of character that appears in the password
*/
struct entropy_t {
  unsigned short has_lowercase, has_uppercase, has_digit, has_specialCaracter;
  unsigned short ris;
};

/**
* @var ::entropy_t::has_lowercase
* number of lowercase characters in the password
* @var ::entropy_t::has_uppercase
* number of uppercase characters in the password
* @var ::entropy_t::has_digit
* number of digits in the password
* @var ::entropy_t::has_specialCaracter
* number of special characters in the password
* @var ::entropy_t::ris
* entropy of the password
*/


/**
* @brief function that return the entropy of the single character
*
* @param[in] c character inserted
* @return ::entropy_t::ris the current total entropy of the passsord
*/
double get_entropy(const gchar *c);

/*
* Funzione che, dato un carattere, ritorna il tipo come descritto nell'enumeratore
*/
/**
* @brief function that, given a character, returns the type as described in ::type_of_character
*
* @param[in] car character to evaluate
* @return ::type_of_character
*/
int pool_of_character(const gchar *car);


/**
* @brief reset ::entropy_t
*/
void entropy_reset();












#endif
