#include <iostream>
#include "crittografia.h"

void openssl_inizializza(){
  /* Load the human readable error strings for libcrypto */
  ERR_load_crypto_strings();

  /* Load all digest and cipher algorithms */
  OpenSSL_add_all_algorithms();

  /* Load config file, and other important initialisation */
  OPENSSL_config(NULL);
}

void openssl_quit(){
  /* Removes all digests and ciphers */
  EVP_cleanup();

  /* if you omit the next, a small leak may be left when you make use of the BIO (low level API) for e.g. base64 transformations */
  CRYPTO_cleanup_all_ex_data();

  /* Remove error strings */
  ERR_free_strings();
}


int get_ascii_code(const char carattere){
  unsigned short ascii;
  ascii = int(carattere);
  return ascii;
}


bool openssl_encrypt(std::string filename, std::string nome, std::string password){
  /*
  if(g_slist_find(lista_utenti, nome) == NULL){
    DBG(std::cout << "Utente non esiste" << std::endl;);
    return false;
  }
  */

  srand(time(NULL));
  size_t salt = rand();
  DBG(std::cout << "Salt: " << salt << std::endl;)

  std::ostringstream concat_password;
  std::ostringstream concat_user;

  concat_password << password << salt;
  concat_user << nome << salt;
  DBG(std::cout << concat_password.str() << std::endl;)
  DBG(std::cout << concat_user.str() << std::endl;)

  std::string concat_password_hash = concat_password.str();
  std::string concat_user_hash = concat_user.str();

  concat_password_hash = sha512(concat_password_hash);
  concat_user_hash = sha512(concat_user_hash);
  DBG(std::cout << "Hash password: " << concat_password_hash << std::endl;)
  DBG(std::cout << "Hash user: " << concat_user_hash << std::endl;)

  DBG(std::cout << "Nome file: " << filename << std::endl;)
  if (!salva_credenziali(filename, concat_user_hash, concat_password_hash, salt)) {
    DBG(std::cout << "Errore apertura file" << std::endl;)
  }

  return true;
}

std::string sha512(const std::string stringa){
  unsigned char hash[SHA512_DIGEST_LENGTH];
  SHA512_CTX sha512;

  //SHA512_Init() initializes a SHA_CTX structure.
  SHA512_Init(&sha512);

  /*SHA512_Update() can be called repeatedly with chunks of the message to
  * be hashed (len bytes at data).
  */
  SHA512_Update(&sha512, stringa.c_str(), stringa.size());

  /* SHA1_Final() places the message digest in md, which must have
  * space for SHA_DIGEST_LENGTH == 20 bytes of output, and erases the SHA_CTX.
  */
  SHA512_Final(hash, &sha512);

  std::stringstream string_hash;
  for (size_t i = 0; i < SHA512_DIGEST_LENGTH; i++){
    string_hash << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
  }
  return string_hash.str();
}



bool openssl_decrypt(std::string username, std::string password, size_t salt, std::string saved_username, std::string saved_password){

  std::ostringstream concat_password;
  std::ostringstream concat_user;

  concat_password << password << salt;
  concat_user << username << salt;
  DBG(std::cout << concat_password.str() << std::endl;)
  DBG(std::cout << concat_user.str() << std::endl;)

  std::string concat_password_hash = concat_password.str();
  std::string concat_user_hash = concat_user.str();

  concat_password_hash = sha512(concat_password_hash);
  concat_user_hash = sha512(concat_user_hash);
  DBG(std::cout << "Hash password: " << concat_password_hash << std::endl;)
  DBG(std::cout << "Hash user: " << concat_user_hash << std::endl;)

  /*
  username = sha512(username);
  DBG(std::cout << "sha512 dell'username inserito: " << username << std::endl;)
  password = sha512(password);
  DBG(std::cout << "sha512 della password inserita: " << password << std::endl;)
  */

  if ((strcmp(username.c_str(), saved_username.c_str()) == 0) && (strcmp(password.c_str(), saved_password.c_str()) == 0)) {
    return true;
  }
  else{
    return false;
  }























}
