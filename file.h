#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <string>
#include "debug.h"
#include "struttura_dati.h"

bool crea_file(std::string nome, std::string password, size_t salt);
size_t get_salt(std::string nome);





#endif
