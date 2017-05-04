#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include "debug.h"
#include "struttura_dati.h"
#include "crittografia.h"
#include "funzioni.h"

/**
* @file
* file saving and loading library
*/


/**
* @brief create a text file with the given name
*
* @param[in] name filename
* @return TRUE if the file has been created
*/
bool file_init(const std::string name);


/**
* @brief write user credentials in the file
*
* @param[in] filename name of the file
* @param[in] username name of the user
* @param[in] password password of the user
* @param[in] salt generated salt to add entropy
* @return TRUE if the credentials has been written
*/
bool save_credentials(const std::string filename, const std::string username, const std::string password, const size_t salt);


/**
* @brief check if the credentials match
*
* @param[in] filename file to open
* @param[in] username username taken from the login mask
* @param[in] password password taken from the login mask
* @return TRUE if the credentials match
*/
bool login_check(const std::string filename, const std::string username, const std::string password);


/**
* @brief this function is invoked each time a new entry is added, so it is only necessary to save the last element of the entry list.
*
* @param[in] filename in which to write
* @param[in] username name of the user in ::user_list
* @return TRUE if the entry has been written
*/
bool save_entries(const std::string filename, const std::string username);


/**
* @brief load the entries from file to ::user_list
*
* @param[in] filename name of the file
* @param[in] username name of the user in ::user_t
* @param[in] password master_password in ::user_t
* @return TRUE if the entries have been loaded correctly
*/
bool load_entries(std::string filename, std::string username, std::string password);

/**
* @brief function that ignores the white spaces
*
* @param[in] input istream
* @param[in] output string that stores the entry
*/
void getEntry(std::istream& input, std::string& output);


#endif
