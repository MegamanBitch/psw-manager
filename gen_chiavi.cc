#include "gen_chiavi.h"
#include <cstdlib>


void genera_chiave(utente_t *utente){

  do {
    utente->chiave.p = genera_primo();
    utente->chiave.q = genera_primo();

    utente->chiave.r = utente->chiave.p * utente->chiave.q;
    utente->chiave.fr = (utente->chiave.p - 1) * (utente->chiave.q - 1);

    utente->chiave.e = genera_e();
    utente->chiave.d = genera_d(utente->chiave.fr, utente->chiave.e);
  } while(utente->chiave.d == 0);

}

size_t genera_primo(){
  size_t numero;
  do
  {
    numero = rand() % 100000; // genera un numero casuale
  }while(!is_prime(numero));

  return numero;
}

bool is_prime(size_t n){
    if (modpower(2, n - 1, n) == 1) {
      return true;
    }
    return false;
}

unsigned short modpower(int x, size_t y, size_t m){
  unsigned short p = 1;
  while (y != 0) {
    size_t temp = y % 2;
    if (temp == 1) {
      temp = (temp * x) % m;
    }
    x = (x * x) % m;
    y = y / 2;
  }
  return p;
}

unsigned short genera_e(){
  size_t numero;
	do
	{
		numero = rand() % 100; // genera un numero casuale
	}while(!is_prime(numero));

  return numero;
}

size_t genera_d(size_t &a, size_t &b){
  for (size_t i = 2; i < a; ++i)
	{
		if (((i * b) % a) == 1)
		{
			return i;
		}

	}
	return 0;
}

int cripta(utente_t *utente, unsigned short ascii){
  int cifratura = 1;
  for (size_t i = 1; i <= utente->chiave.e; i++){
    cifratura = (ascii * cifratura) % utente->chiave.r;
  }
  return cifratura;
}
