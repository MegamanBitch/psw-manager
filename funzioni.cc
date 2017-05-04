#include "funzioni.h"
#include <locale>
#include <cstdlib>

void print_list(){
  GSList *utenti = user_list;
  GSList *entry;
  user_t *my_user;
  entry_t *my_entry;

  DBG(std::cout << "Numero di utenti: " << g_slist_length(user_list) << std::endl;)
  while (utenti != NULL) {
    my_user = (user_t *)utenti->data;

    entry = my_user->entries;
    DBG(std::cout << "Nome utente: " << my_user->name << std::endl;)
    DBG(std::cout << "Password: " << my_user->master_password << std::endl;)

    while (entry != NULL) {
      my_entry = (entry_t *)entry->data;
      DBG(std::cout << "Title: " << my_entry->title << std::endl;)
      DBG(std::cout << "Username: " << my_entry->username << std::endl;)
      DBG(std::cout << "Password: " << my_entry->password << std::endl;)
      DBG(std::cout << "URL: " << my_entry->url << std::endl;)
      DBG(std::cout << "Note: " << my_entry->note << std::endl;)
      entry = g_slist_next(entry);
    }
    utenti = utenti->next;
  }

  g_slist_free (entry);

}

bool add_user(std::string name, std::string password){

  if (name.length() == 0 || password.length() == 0)
    return false;

  user_t *utente = new user_t;

  utente->name = name;
  utente->master_password = password;
  utente->entries = NULL;

  user_list = g_slist_append(user_list, utente);
  DBG(print_list();)

  return true;

}

bool add_entry(std::string nome_utente, std::string title, std::string username, std::string password, std::string url, std::string note){
  GSList *utenti = user_list;
  user_t *my_user;

  while (utenti != NULL) {
    my_user = (user_t *)utenti->data;
    DBG(std::cout << "Comparo " << my_user->name << " con " << nome_utente << std::endl;)

    if (my_user->name == nome_utente) {
      DBG(std::cout << "utente trovato" << std::endl;)

      entry_t *entry = new entry_t;

      entry->title = title;
      entry->username = username;
      entry->password = password;
      entry->url = url;
      entry->note = note;

      my_user->entries = g_slist_append(my_user->entries, entry);

      return true;
    }
    utenti = g_slist_next(utenti);
  }
  return false;
}
