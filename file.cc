#include "file.h"


bool salva_file(std::string filename, std::string username, std::string password, size_t salt){
    std::ofstream f((filename).c_str());
    if (f.is_open()) {
      if (g_slist_length(lista_utenti) != 0) {
        f.write(reinterpret_cast<const char *>(&username), sizeof(username));
        f.write(reinterpret_cast<const char *>(&password), sizeof(password));
        f.write(reinterpret_cast<const char *>(&salt), sizeof(salt));
      }
      f.close();
    }
    return f;
  }

  bool crea_file(std::string nome){
      std::ofstream f((nome).c_str());
      return f;
    }


size_t get_salt(std::string nome){
  std::ifstream f(nome.c_str());

  size_t salt;

  f >> salt;

  return salt;
}

bool login_check(std::string nome_file, std::string username, std::string password){

  /**
  * Controllo l'esistenza del file
  */
  std::ifstream f(nome_file.c_str());
  if (!f) {
    return f;
  }








  return f;
}
