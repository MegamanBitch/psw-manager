#ifndef CRITTOGRAFIA_H
#define CRITTOGRAFIA_H

#include <openssl/sha.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <sstream>
#include <string.h>
#include <iomanip>
#include "struttura_dati.h"
#include "debug.h"
#include "file.h"

/**
* @file
* library that manages all the cryptography of the program.
*/

/**
* @brief init openssl library
*
*/
void openssl_user_list_init();

/**
* @brief close openssl library
*/
void openssl_quit();


/**
* @brief function that returns the sha512 of the given string
* @param[in] stringa
* @return string sha512 of the given string
*/
std::string sha512(std::string stringa);


/**
* @brief function that encrypt username and password
* 1) Generate a salt  https://it.wikipedia.org/wiki/Sale_(crittografia)
* 2) Concat the salt to the user's password and name
* 3) Hash them
* 4) Save the username, password and salt into a text file
* @param[in] filename name of the file in which to save
* @param[in] name name of the user
* @param[in] password password of the user
* @return TRUE if the variables are successfully written on the file
*/
bool openssl_encrypt(const std::string filename, const std::string name, std::string password);



/**
* @brief function that decrypt username and password
* 1) Load the salt from the file
* 2) Concat the salt to the input password
* 3) Hash the input parameters and compare
* @param[in] username username taken from the login mask
* @param[in] password password taken from the login mask
* @param[in] salt salt generated
* @param[in] saved_username username read from the file
* @param[in] saved_password password read from the file
* @return TRUE if the credentials taken from the login mask matches the saved one
*/
bool openssl_decrypt(const std::string username, const std::string password, size_t salt, const std::string saved_username, const std::string saved_password);



#endif
