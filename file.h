#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <string>
#include "debug.h"
#include "struttura_dati.h"

/*
* Funzione che dati in input il nome utente, la password e il sale li salva in
* un file binario
*/
bool crea_file(std::string nome, std::string password, size_t salt);

/*
* Funzione che dato in input un file controlla se il nome utente all'interno
* del file e' presente all'interno della lista
*/
bool apri_file(std::string nome_file);

/*
* Funzione che dato in input il nome di un file ritorna il valore
* del sale salvato in quel file
*/
size_t get_salt(std::string nome);





#endif
