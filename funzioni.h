#ifndef FUNZIONI_H
#define FUNZIONI_H


#include <iostream>
#include <cstring>
#include "entropy.h"
#include "struttura_dati.h"
#include "crittografia.h"
#include "debug.h"

/**
* @brief append user to the ::user_list
*
* @param[in] name ::user_t::name
* @param[in] password ::user_t::master_password
* @return TRUE if the user has been added
*/
bool add_user(std::string name, std::string password);

/**
* @brief append one ::user_t::entries::entry_t to ::user_list::user_t
*
* @param[in] nome_utente ::user_list::user_t::name
* @param[in] title ::entry_t::title
* @param[in] username ::entry_t::username
* @param[in] password ::entry_t::password
* @param[in] url ::entry_t::url
* @param[in] note ::entry_t::note
* @return TRUE if @var nome_utente is found in ::user_list::user_t::name
*/
bool add_entry(std::string nome_utente, std::string title, std::string username, std::string password, std::string url, std::string note);

/**
* @brief print everything in ::user_list
*/
void print_list();

#endif
