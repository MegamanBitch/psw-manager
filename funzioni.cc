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

  if(g_slist_find(lista_utenti, "michele") == NULL){
    return false;
  }




  utente_t *utente = new utente_t;

  utente->entry.nome_entry = entry;
  utente->entry.password = password;
  utente->entry.url = url;
  utente->entry.note = note;

  lista_utenti = g_slist_append(lista_utenti, utente);
  DBG(stampa_lista();)

  return true;
}
