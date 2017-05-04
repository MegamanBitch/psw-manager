#ifndef GEN_PSW_H
#define GEN_PSW_H

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "struttura_dati.h"
#include "debug.h"

/**
* @file
* generate password library
*
* 1) randomly generate a number LL which will be the number of lowercase letters.
* LC must be in range [1..L-4]
*
* 2) randomly generate number UL for uppercase. Must be in range [1..L-LL-3]
*
* 3) randomly generate a number of LD digits. LD must be in range [1..L-LL-UL-2]
*
* 4) randomly generate a number of SL special characters. SL must be [L-LL-UL-LD]
*
* 5) randomly generate LL lowercase letters, UL uppercase letters, LD digits and
* SL characters and keep them in a list(array)
*
* 6) Shuffle the array randomly
*/

/**
* @var RANGE_UPPERCASE
* @brief number of uppercase letters in the alphabet
*/
const int RANGE_UPPERCASE = 25;

/**
* @var RANGE_LOWERCASE
* @brief number of lowercase letters in the alphabet
*/
const int RANGE_LOWERCASE = 25;

/**
* @var RANGE_DIGITS
* @brief number of digits
*/
const int RANGE_DIGITS = 9;

/**
* @var RANGE_SPECIAL_CHARACTERS
* @brief number of special characters usable in this program
*/
const int RANGE_SPECIAL_CHARACTERS = 31;

/**
* @var SPECIAL_CHARACTERS
* @brief const array with the special characters usable in this program
*/
static const char SPECIAL_CHARACTERS[32] = {'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-',
                                            '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^',
                                            '_', '`', '{', '|', '}', '~'};


/**
* @var LOWERCASE_CHARACTERS
* @brief const array with the lowercase letters in the alphabet
*/
static const char LOWERCASE_CHARACTERS[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                                              'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

/**
* @var UPPERCASE_CHARACTERS
* @brief const array with the uppercase letters in the alphabet
*/
static const char UPPERCASE_CHARACTERS[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                                              'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

/**
* @var DIGITS_CHARACTERS
* @brief const array with the digits
*/
static const char DIGITS_CHARACTERS[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};


/**
* @brief initialize the variables in ::parameters_t
*
* @param[in] parameters struct ::parameters_t
* @param[in] lun_psw password length
*/
void generate_numbers(parameters_t &parameters, const unsigned short lun_psw);

/**
* @brief number of lowercase letters in the generated password
* If the password length is 4, return 1 lowercase, 1 uppercase, 1 digit
* and 1 special. This is the worst case.
* If the password length is fewer than 4 return all lowercase.
* If the length is greater than 4 return a random number of lowercase in the
* [1..,N-4] range
*
* @param[in] end number of free usable characters left
* @return number of lowercase letters in ::parameters_t::lowercase
*/
unsigned short generate_lowercase(const unsigned short end);

/**
* @brief number of uppercase letters in the generated password
*
* @param[in] end number of free usable characters left
* @return number of uppercase letters in ::parameters_t::uppercase
*/
unsigned short generate_uppercase(const unsigned short end);

/**
* @brief number of digits in the generated password
*
* @param[in] end number of free usable characters left
* @return number of digits in ::parameters_t::digits
*/
unsigned short generate_digits(const unsigned short end);

/**
* @brief number of special characters in generated password
*
* @param[in] end number of free usable characters left
* @return number of special character in ::parameters_t::special
*/
unsigned short generate_special(const unsigned short end);



#endif
