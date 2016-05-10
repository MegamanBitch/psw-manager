/*
 * Header file contenente l'interfaccia del modulo per la generazione delle chiavi
 */

#ifndef GEN_CHIAVI_H
#define GEN_CHIAVI_H


#include <iostream>
#include "struttura_dati.h"


void genera_chiave(utente_t *utente);
size_t genera_primo();
bool is_prime(size_t n);
unsigned short modpower(int x, size_t y, size_t m);
unsigned short genera_e();
size_t genera_d(size_t &a, size_t &b);
int cripta(utente_t *utente, unsigned short ascii);






#endif
