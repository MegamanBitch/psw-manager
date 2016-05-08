#include <iostream>

using namespace std;

#include "struttura_dati.h"
#include "funzioni.h"
#include <glib.h>

int main(int argc, char const *argv[]) {


  inizializza();

  char menu[]=
  "\nOpzioni disponibili\n\n"
	"\t1) Inserisci nuovo utente\n"
	"\t2) Cifra un messaggio\n"
	"\t3) Decifra un mesasggio\n"
	"\t4) Salva chiavi\n"
	"\t5) Carica chiavi\n"
	"\t6) Stampa lista utenti\n"
	"\t0) Esci\n"
	"Scelta: " ;

  while(true) {
    std::cout << menu << std::endl;

    int scelta;
    std::cin >> scelta;
    if (!cin) {
      cin.clear();
      cin.ignore();
      continue;
    }

    switch (scelta) {
      case 1:
        aggiungi_utente();
        break;
      case 2:
        break;
      case 0:
<<<<<<< HEAD
=======
        g_list_free(lista_utenti);
>>>>>>> 8a1bc59a4216be727978adc6db9a5abfed9a1c2c
        return 0;
      }


  }


  return 0;
}
