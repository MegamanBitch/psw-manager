#include "funzioni.h"
#include <locale>
#include <cstdlib>


void inizializza(){
  lista_utenti = NULL;
}

void stampa_lista(){
  while (lista_utenti != NULL) {
    std::cout << "Numero di utenti: " << g_slist_length(lista_utenti) << std::endl;
    char *nome = (char*) lista_utenti->data;
    std::cout << nome << std::endl;
    lista_utenti = lista_utenti->next;
  }
}

bool aggiungi_utente(std::string nome, std::string password){
  utente_t * utente = new utente_t;

  utente->nome = nome;
  utente->master_password = password;

  utente->ascii_code = new int [nome.length()];

  for (size_t i = 0; i < nome.length(); i++) {
    utente->ascii_code[i] = get_ascii_code(nome.at(i));
  }

  DBG(for (size_t i = 0; i < nome.length(); i++) {
    std::cout << utente->ascii_code[i] << std::endl;
  });

  lista_utenti = g_slist_append(lista_utenti, utente);
  DBG(stampa_lista(););

  return true;

}

unsigned short genera_password(utente_t *utente){

  srand(time(0));
  genera_chiave(utente);

  return cripta(utente, 33 + rand() % 126 - 33); // generate numbers
}
