#include "file.h"


bool crea_file(std::string nome, std::string password, size_t salt){
    std::ofstream f((nome).c_str());
    if (f.is_open()) {
      if (g_slist_length(lista_utenti) != 0) {
        f.write(reinterpret_cast<const char *>(&lista_utenti), sizeof(lista_utenti));
      }
      f.close();
    }
    return f;
  }



size_t get_salt(std::string nome){
  std::ifstream f(nome.c_str());

  size_t salt;

  f >> salt;

  return salt;
}

bool apri_file(std::string nome_file){
  std::ifstream f(nome_file.c_str());
  f.read(reinterpret_cast<char *>(&lista_utenti), sizeof(lista_utenti));

  return f;
}
