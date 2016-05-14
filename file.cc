#include "file.h"


bool crea_file(std::string nome, std::string password, size_t salt){
  std::ofstream f(nome.c_str());

  f << "Username: " << nome << " Password: " <<password << " Salt: " <<salt << std::endl;

  return f;
}


size_t get_salt(std::string nome){
  std::ifstream f(nome.c_str());

  size_t salt;

  f >> salt;

  return salt;
}
