#ifndef CRITTOGRAFIA_H
#define CRITTOGRAFIA_H

#include <openssl/aes.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>


void openssl_inizializza();
int get_ascii_code(const char carattere);

















#endif
