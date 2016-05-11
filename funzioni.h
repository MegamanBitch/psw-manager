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


using namespace std;

static GList *lista_utenti;

void inizializza();
bool aggiungi_utente();
unsigned short genera_password(utente_t *utente);
void leggi_password(istream &is, string s);
bool leggi_master_password(istream &is, string s);

#endif
