#include "file.h"


bool salva_credenziali(std::string filename, std::string username, std::string password, size_t salt){
    std::ofstream f;
    if (f.good()) {
      if (g_slist_length(lista_utenti) != 0) {
        f.open((filename.c_str()), std::fstream::app);
        // username.size() + 1 per aggiungere il terminatore alla stringa '/0'
        f.write(username.c_str(), username.size() + 1);
        f.write(password.c_str(), password.size() + 1);

        f.write(reinterpret_cast<const char *>(&salt), sizeof(salt));
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
  std::ifstream f(nome.c_str(), std::ios::out | std::ios::binary);

  size_t salt;

  f >> salt;

  return salt;
}

bool login_check(std::string nome_file, std::string username, std::string password){

  /**
  * Controllo l'esistenza del file
  */
  std::ifstream f(nome_file.c_str(), std::ios_base::binary);
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

  std::getline(f, saved_username, '\0');
  DBG(std::cout << "Ho letto dal file l'username: " << saved_username << std::endl;)

  std::getline(f, saved_password, '\0');
  DBG(std::cout << "Ho letto dal file la password: " << saved_password << std::endl;)

  f.read(reinterpret_cast<char *>(&saved_salt), sizeof(saved_salt));
  DBG(std::cout << "Ho letto dal file il sale: " << saved_salt << std::endl;)

  if(!openssl_decrypt(username, password, saved_salt, saved_username, saved_password))
    DBG( std::cout << "Le credenziali coincidono, accesso effettuato" << std::endl;)
  else
    DBG(std::cout << "Le credenziali non coincidono, acesso fallito" << std::endl;)


  /**
  * Calcolo lo sha512 delle credenziali nuove con quelle salvate sul file
  */


  return f;
}
