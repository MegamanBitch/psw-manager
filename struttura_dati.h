/**
 * Header file data structure.
 */


/* Begin data structure header file */

#ifndef STRUTTURA_DATI_H
#define STRUTTURA_DATI_H

#include <string>
#include <gtk/gtk.h>

/**
* @var user_list
* global GSList that stores the user lists.
* A new user is added in this list every time
* @see handler_add_user
* is called.
*/
extern GSList *user_list;

/**
* Function that initialize @var user_list to NULL
* @param NULL
* @return void
*/
void user_list_init();

/**
* Entry structure:
* @struct entry_t
* represent a website|field that every user can add.
* A new entry is created every time
* @see handler_get_entry
* is called
*/
struct entry_t {
  std::string title; /**< @var title string that stores the title */
  std::string username; /**< @var username string that stores the username */
  std::string password; /**< @var password string that stores the password */
  std::string url; /**< @var url string that stores the address */
  std::string note; /**< @var note string that stores the address */
};


/**
* User structure:
* @struct user_t
* data structure used to manage users.
*/
struct user_t {
  GSList *entries; /**< @var entries GSList of entries @see entry_t */
  std::string name; /**< @var name string that stores the name of the user */
  std::string master_password; /**< @var master_password string that stores the password of the user */
};


/**
* @enum FileListStoreCols
* contains the column names of the GtkTree model
*/
enum FileListStoreCols{
	COL_TITLE, /**< @var COL_TITLE @see entry_t */
	COL_USERNAME, /**< @var COL_USERNAME @see entry_t */
	COL_PASSWORD, /**< @var COL_PASSWORD @see entry_t */
	COL_URL, /**< @var COL_URL @see entry_t */
	COL_NOTE /**< @var COL_NOTE @see entry_t */
};

/**
* Parameter structure:
* @struct parameters_t
* data structure used for the parameters in the generated password.
* @see generate_numbers
*/
struct parameters_t {
  unsigned short lowercase; /**< @var lowercase unsigned short that stores the number of the lowercase in the generated password */
  unsigned short uppercase; /**< @var uppercase unsigned short that stores the number of the uppercase in the generated password */
  unsigned short digits; /**< @var digits unsigned short that stores the number of the digits in the generated password */
  unsigned short special; /**< @var special unsigned short that stores the number of the special characters in the generated password */
};


#endif

/* end data structure header file */
