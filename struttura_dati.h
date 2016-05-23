/*
 * Header file contenente le dichiarazioni della struttura dati comune.
 */


/* Inizio header del modulo Struttura Dati */

#ifndef STRUTTURA_DATI_H
#define STRUTTURA_DATI_H

#include <string>
#include <gtk/gtk.h>

extern GSList *lista_utenti;

void inizializza();

/* Password:
* Struttura dati per gestire le password.
* Puntatore di caratteri alla password. Si chiede
* all'utente quanto robusta deve essere la password
* e si alloca in base alla dimensione, la lunghezza
* della password viene salvata in num_caratteri
*/
struct password_t {
  std::string stringa_psw;
  unsigned short num_caratteri;
};


/* Entry:
* struttura dati per gestire le entry, ovvero le voci
* che un utente puo' inserire. Una voce e' un programma
* o un'applicazione che necessita una password.
* Ha un campo stringa di lunghezza massima MAXLUNNOME
* e un campo password_t.
*/
struct entry_t {
  std::string nome_entry;
  std::string password;
  std::string url;
  std::string note;
};



/* Utente:
* Struttura dati per gestire gli utenti.
* Un utente ha un campo stringa di lunghezza massima
* MAXLUNNOME e un campo password_t. La password
* in questo caso e' la master_password, ovvero la
* password con cui un utente accede al database, ogni
* utente ha una master_password personale
*/
struct utente_t {
  entry_t entry;
  std::string nome;
  std::string master_password;
};



struct flag_parameters_t {
  bool uppercase;
  bool lowercase;
  bool space;
  bool special;
  bool digits;
  bool minus;
  bool underscore;
  bool brackets;

};


#endif

/* Fine header modulo Struttura Dati */
