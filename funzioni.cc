#include "funzioni.h"
#include <locale>
#include <cstdlib>


void inizializza(){
  lista_utenti = NULL;
}

bool aggiungi_utente(std::string nome, std::string password){
  utente_t * utente = new utente_t;

  utente->nome = nome;
  utente->master_password = password;

  lista_utenti = g_list_append(lista_utenti, utente);

  return true;

}

void leggi_password(istream &is, string s){
  getline(is, s);
}

bool leggi_master_password(istream &is, string s){
  getline(is, s);
  get_entropy(s);
  return true;
}

unsigned short genera_password(utente_t *utente){

  srand(time(0));
  genera_chiave(utente);

  return cripta(utente, 33 + rand() % 126 - 33); // generate numbers
}
