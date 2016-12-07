#include "funzioni.h"
#include <locale>
#include <cstdlib>

void stampa_lista(){
  GSList *tmp = lista_utenti;
  while (tmp != NULL) {
    std::cout << "Numero di utenti: " << g_slist_length(lista_utenti) << std::endl;
    utente_t *my_data = (utente_t *)tmp->data;
    std::cout << "Nome utente: " << my_data->nome << std::endl;
    std::cout << "Password: " << my_data->master_password << std::endl;
    tmp = g_slist_next(tmp);
  }
}

bool aggiungi_utente(std::string nome, std::string password){
  utente_t *utente = new utente_t;

  utente->nome = nome;
  utente->master_password = password;
  utente->num_entry = 0;
  utente->dim = 0;

  lista_utenti = g_slist_append(lista_utenti, utente);
  DBG(stampa_lista();)

  return true;

}

bool aggiungi_entry(std::string nome_utente, std::string entry, std::string password, std::string url, std::string note){

  /**
  * Cerco se il nome utente esiste nella lista
  */
  DBG(std::cout << "Cerco l'utente " << nome_utente << " all'interno della lista" << std::endl;)
  utente_t *my_data = (utente_t *)lista_utenti->data;

  for (size_t i = 0; i < g_slist_length(lista_utenti); i++) {
    if (strcmp(my_data[i].nome.c_str(), nome_utente.c_str()) != 0) {
      /**
      * Se l'utente e' stato trovato aggiungo i campi delle entry
      */
      DBG(std::cout << "utente trovato" << std::endl;)

      /**
      * Devo controllare l'array dinamico @entry_t prima di assegnare i valori
      * alle variabili
      */

      /**
      * Se il numero delle entry e' 0 alloco l'array aggiorno il numero delle
      * variabili @num_entry e @dim
      */
      if (my_data[i].num_entry == 0) {
        my_data[i].entry = new entry_t [1];
        my_data[i].num_entry = 1;
        my_data[i].dim = 2;
      }

      /**
      * Se il numero delle entry e' diverso da 0 controllo se @num_entry e' diverso
      * da @dim
      * Se i valori sono uguali devo deallocare l'array, raddoppiare @dim e copiare
      * il vecchio array nel nuovo array doppio
      */
      if (my_data[i].num_entry == my_data[i].dim) {
        utente_t *tmp = new utente_t [my_data[i].dim * 2];
        for (size_t i = 0; i < my_data[i].num_entry; i++) {
          tmp[i].entry->nome_entry = my_data[i].entry->nome_entry;
          tmp[i].entry->password = my_data[i].entry->password;
          tmp[i].entry->url = my_data[i].entry->url;
          tmp[i].entry->note = my_data[i].entry->note;
        }
        tmp[i].num_entry = my_data[i].num_entry;
        tmp[i].dim = my_data[i].dim * 2;

        delete [] my_data[i].entry;
        entry * my_data = new utente_t [tmp[i].dim];
        my_data
        utente = tmp;
      }

      my_data[i].entry->nome_entry = entry;
      my_data[i].entry->password = password;
      my_data[i].entry->url = url;
      my_data[i].entry->note = note;

      return true;
    }
  }

  DBG(std::cout << "utente non trovato" << std::endl;)
  return false;
}
