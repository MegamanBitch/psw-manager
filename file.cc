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
    * Se coincidono devo caricare in memoria tutte le entries
    */
    load_entries(nome_file, saved_username, saved_password);
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
        * Assegno alla GSList temporanea @entry la lista dell'user corrente. Faccio
        * l'assegnazione dentro al while per assegnare un vettore diverso ad ogni ciclo
        */
        entry = my_user->entries;

        while (entry != NULL) {
          my_entry = (entry_t *)entry->data;
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
      }
      utenti = utenti->next;
    }
    g_slist_free (utenti);
    g_slist_free (entry);
    return true;
  }
  return false;
}



bool load_entries(std::string nome_file, std::string username, std::string password){

  std::ifstream f;
  if(f.good()){
    f.open((nome_file.c_str()), std::ifstream::in);

    std::string result;
    while (std::getline(f, result, '\0')) {
      DBG(std::cout << result << std::endl;)
    }

  }

  /*
  std::streampos size;
  char * memblock;

  std::ifstream f (nome_file.c_str(), std::ios::in | std::ios::ate);
  if (f.is_open()){
    size = f.tellg();
    memblock = new char [size];
    f.seekg (0, std::ios::beg);
    f.read (memblock, size);
    f.close();

    DBG(std::cout << "the entire f content is in memory" << std::endl;)

    char ch;
    std::string result = "";
    for (int i = 0; i < size; i++) {
      while ((ch = memblock[i]) != '\0') {
        result += ch;
      }
      DBG(std::cout << result << std::endl;)
    }



    delete[] memblock;
  }
  else
    DBG(std::cout << "Unable to open f" << std::endl;)

    */

  return true;











}
