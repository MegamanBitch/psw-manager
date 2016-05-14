/*
 * Header file contenente l'interfaccia del modulo delle funzioni
 */

 /* Funzione per l'inizializzazione del contenitore */

#ifndef FUNZIONI_H
#define FUNZIONI_H

using namespace std;

#include <iostream>
#include <cstring>
#include <gtk/gtk.h>
#include "entropy.h"
#include "struttura_dati.h"
#include "gen_chiavi.h"
#include "crittografia.h"
#include "debug.h"



using namespace std;

static GSList *lista_utenti;

void inizializza();
bool aggiungi_utente(std::string nome, std::string password);
unsigned short genera_password(utente_t *utente);
void leggi_password(istream &is, string s);
bool leggi_master_password(istream &is, string s);
void stampa_lista();

#endif
