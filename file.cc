#include "file.h"


bool salva_credenziali(std::string filename, std::string username, std::string password, size_t salt){
    std::ofstream f;
    if (f.good()) {
      if (g_slist_length(lista_utenti) != 0) {
        f.open((filename.c_str()), std::fstream::app);
        f.write(username.c_str(), username.size());
        f.write("\0",sizeof(char));

        f.write(password.c_str(), password.size());
        f.write("\0",sizeof(char));

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
  * Se il file esiste devo controllare che l'username che mi ha passato
  * l'utente corrisponde
  */
  std::string new_username;
  std::string new_password;

  std::getline(f, new_username, '\0');
  DBG(std::cout << "Ho letto dal file l'username: " << new_username << std::endl;)

  std::getline(f, new_password, '\0');
  DBG(std::cout << "Ho letto dal file la password: " << new_password << std::endl;)

  /**
  * 
  */


  return f;
}
