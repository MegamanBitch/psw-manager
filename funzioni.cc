#include "funzioni.h"
#include <locale>
#include <cstdlib>

void stampa_lista(){

  /**
  * Uso una GSList temporanea @utenti e @entry
  */
  GSList *utenti = user_list;
  GSList *entry;
  user_t *my_user;
  entry_t *my_entry;

  DBG(std::cout << "Numero di utenti: " << g_slist_length(user_list) << std::endl;)
  while (utenti != NULL) {
    /**
    * Faccio un cast @utenti->data per poter leggerne il contenuto
    */
    my_user = (user_t *)utenti->data;

    /**
    * Assegno alla GSList temporanea @entry la lista dell'user corrente. Faccio
    * l'assegnazione dentro al while per assegnare un vettore diverso ad ogni ciclo
    */
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

bool aggiungi_utente(std::string nome, std::string password){
  user_t *utente = new user_t;

  utente->name = nome;
  utente->master_password = password;
  utente->entries = NULL;

  user_list = g_slist_append(user_list, utente);
  DBG(stampa_lista();)

  return true;

}

bool aggiungi_entry(std::string nome_utente, std::string title, std::string username, std::string password, std::string url, std::string note){

  /**
  * Uso una GSList temporanea @utenti e @entry
  */
  GSList *utenti = user_list;
  user_t *my_user;

  while (utenti != NULL) {
    my_user = (user_t *)utenti->data;
    DBG(std::cout << "Comparo " << my_user->name << " con " << nome_utente << std::endl;)

    if (my_user->name == nome_utente) {
      /**
      * Se l'utente e' stato trovato aggiungo i campi delle entry
      */
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

  /*

  for (size_t i = 0; i < g_slist_length(user_list); i++) {
    DBG(std::cout << "Comparo " << my_data[i].nome << " con " << nome_utente << std::endl;)
    if (strcmp(my_data[i].nome.c_str(), nome_utente.c_str()) == 0) {

       Se l'utente e' stato trovato aggiungo i campi delle entry

      DBG(std::cout << "utente trovato" << std::endl;)

      entry_t *entry = new entry_t;

      entry->title = title;
      entry->username = username;
      entry->password = password;
      entry->url = url;
      entry->note = note;

      my_data[i].entries = g_slist_append(my_data[i].entries, entry);

      DBG(stampa_lista());

      return true;
    }

  }

  return false;

  */
}
