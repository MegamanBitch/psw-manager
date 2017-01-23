#include "funzioni.h"
#include <locale>
#include <cstdlib>

void stampa_lista(){
  GSList *tmp = lista_utenti;
  while (tmp != NULL) {
    std::cout << "Numero di utenti: " << g_slist_length(lista_utenti) << std::endl;
    utente_t *my_data = (utente_t *)tmp->data;
    std::cout << "Nome utente: " << my_data->nome << std::endl;
    std::cout << "Password: " << my_data->master_password << std::endl;
    tmp = g_slist_next(tmp);
  }
}

bool aggiungi_utente(std::string nome, std::string password){
  utente_t *utente = new utente_t;

  utente->nome = nome;
  utente->master_password = password;
  utente->num_entry = 0;
  utente->dim = 0;

  lista_utenti = g_slist_append(lista_utenti, utente);
  DBG(stampa_lista();)

  return true;

}

bool aggiungi_entry(std::string nome_utente, std::string title, std::string username, std::string password, std::string url, std::string note){

  /**
  * Cerco se il nome utente esiste nella lista
  */
  DBG(std::cout << "Cerco l'utente " << nome_utente << " all'interno della lista" << std::endl;)
  utente_t *my_data = (utente_t *)lista_utenti->data;

  for (size_t i = 0; i < g_slist_length(lista_utenti); i++) {
    DBG(std::cout << "Comparo " << my_data[i].nome << " con " << nome_utente << std::endl;)
    if (strcmp(my_data[i].nome.c_str(), nome_utente.c_str()) == 0) {
      /**
      * Se l'utente e' stato trovato aggiungo i campi delle entry
      */
      DBG(std::cout << "utente trovato" << std::endl;)

      /**
      * Devo controllare l'array dinamico @entry_t prima di assegnare i valori
      * alle variabili
      */

      /**
      * Se il numero delle entry e' 0 alloco l'array e aggiorno il numero delle
      * variabili @num_entry e @dim
      */
      DBG(std::cout << "Numero entry: " << my_data[i].num_entry << std::endl;)
      if (my_data[i].num_entry == 0) {
        my_data[i].entry = new entry_t [1];
        my_data[i].num_entry = 0;
        my_data[i].dim = 1;
      }
      DBG(std::cout << "num_entry e dim: " << my_data[i].num_entry << " " << my_data[i].dim << std::endl;)

      /**
      * Se il numero delle entry e' diverso da 0 controllo se @num_entry e' diverso
      * da @dim
      * Se i valori sono uguali devo deallocare l'array, raddoppiare @dim e copiare
      * il vecchio array nel nuovo array doppio
      */
      if (my_data[i].num_entry == my_data[i].dim) {
        /**
        * Creazione array doppio di tipo @entry_t
        */
        DBG(std::cout << "Creazione array doppio di tipo entry_t" << std::endl;)
        entry_t *tmp = new entry_t [my_data[i].dim * 2];
        DBG(std::cout << "num_entry e dim: " << my_data[i].num_entry << " " << my_data[i].dim << std::endl;)
        /**
        * Copia di tutti i campi presenti nel vettore dinamico entry
        * @title
        * @username
        * @password
        * @url
        * @note
        */
        DBG(std::cout << "Copia di tutti i campi presenti nel vettore dinamico entry" << std::endl;)
        for (size_t j = 0; j < my_data[i].num_entry; j++) {
          tmp[j].title = my_data[i].entry[j].title;
          tmp[j].username = my_data[i].entry[j].username;
          tmp[j].password = my_data[i].entry[j].password;
          tmp[j].url = my_data[i].entry[j].url;
          tmp[j].note = my_data[i].entry[j].note;
        }

        /**
        * Salvo @dim e @num_entry in variabili locali temporanee
        */
        DBG(std::cout << "Salvo dim e num_entry in variabili locali temporanee" << std::endl;)
        unsigned short num_entry = my_data[i].num_entry;
        unsigned short dim = my_data[i].dim * 2;

        /**
        * Elimino il vecchio vettore @my_data[i].entry con dimensione obsoleta
        */
        DBG(std::cout << "Elimino il vecchio vettore my_data[i].entry con dimensione obsoleta" << std::endl;)
        delete [] my_data[i].entry;

        /**
        * Alloco il nuovo vettore @my_data[i].entry con dimensione @dim
        */
        DBG(std::cout << "Alloco il nuovo vettore my_data[i].entry con dimensione dim" << std::endl;)
        my_data[i].entry = new entry_t [dim];

        /**
        * Aggiorno i valori di @my_data[i].dim e @my_data[i].num_entry
        */
        DBG(std::cout << "Aggiorno i valori di my_data[i].dim e my_data[i].num_entry" << std::endl;)
        my_data[i].dim = dim;
        my_data[i].num_entry = num_entry;

        /**
        * Faccio puntare il vettore dinamico @my_data[i].entry a @tmp[i]
        */
        DBG(std::cout << "Faccio puntare il vettore dinamico my_data[i].entry a tmp[i]" << std::endl;)
        my_data[i].entry = tmp;


        /**
        * Dealloco il vettore @tmp
        */
        DBG(std::cout << "Dealloco il vettore tmp" << std::endl;)
        delete [] tmp;

        /**
        * Adesso che il vettore e' della giusta dimensione assegno le variabili
        */
        DBG(std::cout << "Assegnazione" << std::endl;)
        my_data[i].entry[my_data[i].num_entry].title = title;
        my_data[i].entry[my_data[i].num_entry].username = nome_utente;
        my_data[i].entry[my_data[i].num_entry].password = password;
        my_data[i].entry[my_data[i].num_entry].url = url;
        my_data[i].entry[my_data[i].num_entry].note = note;

        my_data[i].num_entry++;

        /**
        * Se il numero delle entry e' diverso da 0 controllo se @num_entry e' diverso
        * da @dim
        * Se i valori sono diversi vuol dire che ho lo spazio per inserire le nuove
        * entry. Una volta inserite devo aumentare il numero delle entry
        */

      }
      else {
          DBG(std::cout << "Assegnazione" << std::endl;)
          my_data[i].entry[my_data[i].num_entry].title = title;
          my_data[i].entry[my_data[i].num_entry].username = nome_utente;
          my_data[i].entry[my_data[i].num_entry].password = password;
          my_data[i].entry[my_data[i].num_entry].url = url;
          my_data[i].entry[my_data[i].num_entry].note = note;

          my_data[i].num_entry++;
      }


      // stampa di prova

      DBG(std::cout << "Utente connesso: " << my_data[i].nome << std::endl;)
      DBG(std::cout << "Password utente connesso: " << my_data[i].master_password << std::endl;)
      DBG(std::cout << "Numero entry dell'utente: " << my_data[i].num_entry << std::endl;)
      DBG(std::cout << "Dimensione vettore entry: " << my_data[i].dim << std::endl;)
      DBG(std::cout << "Titolo entry: " << my_data[i].entry[my_data[i].num_entry-1].title << std::endl;)
      DBG(std::cout << "Username entry: " << my_data[i].entry[my_data[i].num_entry-1].username << std::endl;)
      DBG(std::cout << "Password entry: " << my_data[i].entry[my_data[i].num_entry-1].password << std::endl;)
      DBG(std::cout << "Url entry: " << my_data[i].entry[my_data[i].num_entry-1].url << std::endl;)
      DBG(std::cout << "Note entry: " << my_data[i].entry[my_data[i].num_entry-1].note << std::endl;)
      DBG(std::cout << "--------------------------------------------------------------------------" << std::endl;)

      return true;
      }

    }

    DBG(std::cout << "utente non trovato" << std::endl;)
    return false;
}
