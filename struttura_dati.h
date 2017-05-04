/**
 * Header file data structure.
 */


/* Begin data structure header file */

#ifndef STRUTTURA_DATI_H
#define STRUTTURA_DATI_H

#include <string>
#include <gtk/gtk.h>

/**
* @file
* Data structure library.
*/

/**
* @var user_list
* @brief global GSList that stores the user lists
* @see handler_add_user ::handler_add_user
*/
extern GSList *user_list;

/**
* @brief Function that initialize @var user_list to NULL
* @param NULL
*/
void user_list_init();

/**
* Entry structure:
* @struct entry_t
* @brief represent a website|field that every user can add.
* A new entry is created every time @see ::handler_get_entry is called
*/
struct entry_t {
  std::string title;
  std::string username;
  std::string password;
  std::string url;
  std::string note;
};

/**
* @var entry_t::title
* string that stores the title
* @var entry_t::username
* string that stores the username
* @var entry_t::password
* string that stores the password
* @var entry_t::url
* string that stores the address
* @var entry_t::note
* string that stores the address
*/


/**
* User structure:
* @struct user_t data_structure.h 'data_structure.h'
* @brief data structure used to manage users.
*/
struct user_t {
  GSList *entries;
  std::string name;
  std::string master_password;
};

/**
* @var user_t::entries
* GSList of entries @see ::entry_t
* @var user_t::name
* string that stores the name of the user
* @var user_t::master_password
* string that stores the password of the user
*/



/**
* @enum FileListStoreCols
* @brief contains the column names of the GtkTree model
*/
enum FileListStoreCols{
	COL_TITLE,
	COL_USERNAME,
	COL_PASSWORD,
	COL_URL,
  COL_NOTE
};

/**
* @var FileListStoreCols FileListStoreCols::COL_TITLE
* Column title
* @var FileListStoreCols FileListStoreCols::COL_USERNAME
* Column username
* @var FileListStoreCols FileListStoreCols::COL_PASSWORD
* Column password
* @var FileListStoreCols FileListStoreCols::COL_URL
* Column URL
* @var FileListStoreCols FileListStoreCols::COL_NOTE
* Column note
* @see entry_t ::entry_t
*/


/**
* Parameter structure:
* @struct parameters_t data_structure.h 'data_structure.h'
* @brief data structure used for the parameters in the generated password.
*/
struct parameters_t {
  unsigned short lowercase;
  unsigned short uppercase;
  unsigned short digits;
  unsigned short special;
};

/**
* @var parameters_t::lowercase
* unsigned short that stores the number of the lowercase in the generated password
* @var parameters_t::uppercase
* unsigned short that stores the number of the uppercase in the generated password
* @var parameters_t::digits
* unsigned short that stores the number of the digits in the generated password
* @var parameters_t::special
* unsigned short that stores the number of the special characters in the generated password
*/


#endif

/* end data structure header file */
