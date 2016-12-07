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
    if (strcmp(my_data[i].nome.c_str(), nome_utente.c_str()) == 0) {
      DBG(std::cout << "utente trovato" << std::endl;)
    }
  }

  /**
  * Se l'utente e' stato trovato
  */

    /*
    my_data->entry->nome_entry = entry;
    my_data->entry->password = password;
    my_data->entry->url = url;
    my_data->entry->note = note;
    */

  return true;
}
