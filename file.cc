#include "file.h"


bool salva_credenziali(std::string filename, std::string username, std::string password, size_t salt){
    std::ofstream f(filename.c_str(), std::ios::app);
    if (f.good()) {
      if (g_slist_length(lista_utenti) != 0) {
        // username.size() + 1 per aggiungere il terminatore alla stringa '/0'
        f << username << std::endl;
        f << password << std::endl;

        f << salt << std::endl;
        //salva numero entries come int
        //scorri lista entries
        //  per ogni entry salva
      }
      f.close();
    }
    return f;
  }

  // salva entries


  bool crea_file(std::string nome){
      std::ofstream f((nome).c_str());
      return f;
    }


size_t get_salt(std::string nome){
  std::ifstream f(nome.c_str(), std::ios::out);

  size_t salt;

  f >> salt;

  return salt;
}

bool login_check(std::string nome_file, std::string username, std::string password){

  /**
  * Controllo l'esistenza del file
  */
  std::ifstream f(nome_file.c_str());
  if (!f.good()) {
    DBG(std::cout << "Non riconosce il nome del file" << std::endl;)
    return f;
  }

  /**
  * Se il file esiste devo controllare se le credenziali che mi ha passato
  * l'utente corrispondono
  */


  std::string saved_username;
  std::string saved_password;
  size_t saved_salt;

  std::getline(f, saved_username);
  DBG(std::cout << "Ho letto dal file l'username: " << saved_username << std::endl;)

  std::getline(f, saved_password);
  DBG(std::cout << "Ho letto dal file la password: " << saved_password << std::endl;)

  f >> saved_salt;
  DBG(std::cout << "Ho letto dal file il sale: " << saved_salt << std::endl;)

  /**
  * Controllo se le credenziali coincidono
  */
  if(openssl_decrypt(username, password, saved_salt, saved_username, saved_password)){
    DBG( std::cout << "Le credenziali coincidono, accesso effettuato" << std::endl;)
    /**
    * Se coincidono distruggo la lista e carico in memoria tutte le entries dell'utente
    */
    //g_slist_free(lista_utenti);
    load_entries(nome_file, username, password);
    return true;
  }
  else{
    DBG(std::cout << "Le credenziali non coincidono, acesso fallito" << std::endl;)
    return false;
  }

}


bool save_entries(std::string nome_file, std::string nome_utente){
  std::ofstream f;
  if (f.good()) {
    f.open((nome_file.c_str()), std::ios::app);

    /**
    * Uso una GSList temporanea @utenti e @entry
    */
    GSList *utenti = lista_utenti;
    GSList *entry;
    utente_t *my_user;
    entry_t *my_entry;

    DBG(std::cout << "Numero di utenti: " << g_slist_length(lista_utenti) << std::endl;)
    while (utenti != NULL) {
      /**
      * Faccio un cast @utenti->data per poter leggerne il contenuto
      */
      my_user = (utente_t *)utenti->data;
      DBG(std::cout << "Comparo " << my_user->nome << " con " << nome_utente << std::endl;)

      if (my_user->nome == nome_utente) {

        /**
        * Assegno alla GSList temporanea @entry la lista dell'user corrente.
        */
        entry = my_user->entries;

        /**
        * Questa funzione viene richiamata ogni volta che una nuova entry viene
        * aggiunta, pertanto e' necessario salvare soltanto l'ultimo elemento
        * della lista entry.
        */
        GSList * last_entry = g_slist_last(entry);


        my_entry = (entry_t *)last_entry->data;
        DBG(std::cout << "Title: " << my_entry->title << std::endl;)
        f << my_entry->title << std::endl;

        DBG(std::cout << "Username: " << my_entry->username << std::endl;)
        f << my_entry->username << std::endl;

        DBG(std::cout << "Password: " << my_entry->password << std::endl;)
        f << my_entry->password << std::endl;

        DBG(std::cout << "URL: " << my_entry->url << std::endl;)
        f << my_entry->url << std::endl;

        DBG(std::cout << "Note: " << my_entry->note << std::endl;)
        f << my_entry->note << std::endl;

        entry = entry->next;

      }
      utenti = utenti->next;
    }
    g_slist_free(utenti);
    g_slist_free(entry);
    return true;
  }
  return false;
}



bool load_entries(std::string nome_file, std::string username, std::string password){

  std::ifstream f;
  if(f.good()){

    g_slist_free(lista_utenti);
    inizializza();

    utente_t *utente = new utente_t;

    utente->nome = username;
    utente->master_password = password;
    utente->entries = NULL;

    lista_utenti = g_slist_append(lista_utenti, utente);


    f.open((nome_file.c_str()), std::ifstream::in);
    // Get and drop a line
    f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    DBG(std::cout << "Ho saltato le prime 3 righe" << std::endl;)

    unsigned int line_number = 0;
    std::string line;

    /**
    * Uso una GSList temporanea @utenti e @entry
    */
    GSList *utenti = lista_utenti;
    utente_t *my_user;
    my_user = (utente_t *)utenti->data;
    entry_t *entry = new entry_t;

    while(f && std::getline(f, line)){
    // Loop only entered if reading a line from f is OK.
    // Note: getline() returns a stream reference. This is automatically cast
    // to boolean for the test. streams have a cast to bool operator that checks
    // good()
    DBG(std::cout << std::getline(f, line) << std::endl;)
    line_number = (line_number + 1) % 5;

    switch (line_number) {
      case 1:
        f >> entry->title;
        break;
      case 2:
        f >> entry->username;
        break;
      case 3:
        f >> entry->password;
        break;
      case 4:
        f >> entry->url;
        break;
      case 0:
        f >> entry->note;
        break;
      }

      if (line_number == 0)
        my_user->entries = g_slist_append(my_user->entries, entry);

    }
  }
  stampa_lista();
  return f;

}
