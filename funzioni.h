/*
 * Header file contenente l'interfaccia del modulo delle funzioni
 */

 /* Funzione per l'inizializzazione del contenitore */

#ifndef FUNZIONI_H
#define FUNZIONI_H

using namespace std;

#include <iostream>
#include <cstring>
#include "entropy.h"
#include "struttura_dati.h"
#include "crittografia.h"
#include "debug.h"



bool aggiungi_utente(std::string nome, std::string password);
bool aggiungi_entry(std::string nome_utente, std::string entry, std::string password, std::string url, std::string note);
void stampa_lista();

#endif
