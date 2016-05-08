#include "funzioni.h"
#include "gen_chiavi.h"
#include <locale>
#include <cstdlib>


void inizializza(){
  lista_utenti = NULL;
}

bool aggiungi_utente(){
  utente_t * utente = new utente_t;
  char carattere;
  unsigned short lun_psw;
  std::cout << "Inserisci nome utente: " << std::endl;
  std::cin >> utente->nome;

  std::cout << "Inserisci password: " << std::endl;
  std::cout << "Inserire (p)assword o (g)enerare casualmente? " << std::endl;
  std::cin >> carattere;
  if (!cin) {
    cin.clear();
    cin.ignore();
  }
  switch (tolower(carattere)) {
    case 'p':
      leggi_password(cin, utente->master_password);
      break;
    case 'g':
    {
      std::cout << "Inserisci lunghezza password" << std::endl;
      std::cin >> lun_psw;
      unsigned short ascii[lun_psw - 1];
      for (size_t i = 0; i < lun_psw; i++) {
        ascii[i] = genera_password(utente);
      }

      std::cout << "La tua password: " << std::endl;
      for (size_t i = 1; i < lun_psw; i++) {
        std::cout << ascii[i] << std::endl;
      }
    }

  }

  lista_utenti = g_list_append(lista_utenti, utente);

  return true;

}

void leggi_password(istream &is, password_t &riga){
  std::cout << "Inserisci password: " << std::endl;
  while (is.peek() == '\n') {
    is.get();
  }
  is.get(riga.stringa, MAXLUNNOME);
  is.get();
  riga.num_caratteri = strlen(riga.stringa);
}

unsigned short genera_password(utente_t *utente){

  srand(time(0));
  genera_chiave(utente);

  return cripta(utente, 33 + rand() % 126 - 33); // generate numbers
}
