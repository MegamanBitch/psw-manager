#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include "debug.h"
#include "struttura_dati.h"
#include "crittografia.h"
#include "funzioni.h"
#include "main.h"

/*
* Funzione che dato in input il nome del file lo crea
*/
bool crea_file(const std::string nome);

/*
* Funzione che dati in input il nome utente, la password e il sale li salva
* in un file binario
*/
bool salva_credenziali(const std::string filename, const std::string username, const std::string password, const size_t salt);


/*
* Funzione che dato in input un file controlla se il nome utente all'interno
* del file e' presente all'interno della lista
*/
bool login_check(const std::string nome_file, const std::string username, const std::string password);

/*
* Funzione che dato in input il nome di un file ritorna il valore
* del sale salvato in quel file
*/
size_t get_salt(std::string nome);

/**
* Funzione che salva in memoria le entries su file binario
*/
bool save_entries(const std::string nome_file, const std::string nome_utente);


/**
* Funzione che carica in memoria le entries da file binario
*/
bool load_entries(std::string nome_file, std::string username, std::string password);




#endif
