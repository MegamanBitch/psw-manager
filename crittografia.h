#ifndef CRITTOGRAFIA_H
#define CRITTOGRAFIA_H

#include <openssl/sha.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <sstream>
#include <string.h>
#include <iomanip>
#include "struttura_dati.h"
#include "debug.h"
#include "file.h"


void openssl_inizializza();
void openssl_quit();


/*
* Funzione che dato un carattere restituisce il codice ASCII
*/
int get_ascii_code(const char carattere);
std::string sha512(std::string stringa);

/*
* Funzione che cripta username e password
* 1) Genera un sale https://it.wikipedia.org/wiki/Sale_(crittografia)
* 2) Concatena il sale alla password dell'utente
* 3) Fa un Hash alla combinazione password-sale usando SHA512
* 4) Salva l'username, il valore hash e il sale nel database
*/
bool openssl_encrypt(const std::string nome, std::string password);


/*
* Funzione che decripta username e password
* 1) Carica il sale associato all'username
* 2) Concatena il sale alla password inserita
* 3) Fa un Hash alla combinazione e la confronta al valore hash salvato
*/
void openssl_decrypt(std::string nome);
















#endif
