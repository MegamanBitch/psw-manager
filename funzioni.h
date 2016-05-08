/*
 * Header file contenente l'interfaccia del modulo delle funzioni
 */

 /* Funzione per l'inizializzazione del contenitore */

#ifndef FUNZIONI_H
#define FUNZIONI_H


#include <iostream>
#include <cstring>
#include <gtk/gtk.h>
<<<<<<< HEAD
=======
#include <glib.h>
>>>>>>> 8a1bc59a4216be727978adc6db9a5abfed9a1c2c
#include "struttura_dati.h"

using namespace std;

static GList *lista_utenti;

void inizializza();
bool aggiungi_utente();
void leggi_password(istream &is, password_t &riga);
unsigned short genera_password(utente_t *utente);

#endif
