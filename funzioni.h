/*
 * Header file contenente l'interfaccia del modulo delle funzioni
 */

 /* Funzione per l'user_list_initzione del contenitore */

#ifndef FUNZIONI_H
#define FUNZIONI_H

using namespace std;

#include <iostream>
#include <cstring>
#include "entropy.h"
#include "struttura_dati.h"
#include "crittografia.h"
#include "debug.h"

/*
* Funzione che appende alla lista il nome e la password
*/
bool aggiungi_utente(std::string nome, std::string password);

/*
* Funzione che appende alla lista una entry
*/
bool aggiungi_entry(std::string nome_utente, std::string title, std::string username, std::string password, std::string url, std::string note);

/*
* Funzione che stampa l'intera lista
*/
void stampa_lista();

#endif
