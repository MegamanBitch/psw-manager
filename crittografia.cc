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


bool openssl_encrypt(std::string nome, std::string password){
  /*
  if(g_slist_find(lista_utenti, nome) == NULL){
    DBG(std::cout << "Utente non esiste" << std::endl;);
    return false;
  }
  */

  srand(time(NULL));
  size_t salt = rand();
  DBG(std::cout << "Salt: " << salt << std::endl;)

  std::ostringstream stringa_concatenata;
  stringa_concatenata << password << salt;
  DBG(std::cout << stringa_concatenata.str() << std::endl;)

  std::string stringa_concatenata_hash = stringa_concatenata.str();

  stringa_concatenata_hash = sha512(stringa_concatenata_hash);
  DBG(std::cout << "Hash stringa: " << stringa_concatenata_hash << std::endl;);

  if (!crea_file(nome, stringa_concatenata_hash, salt)) {
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



void openssl_decrypt(std::string nome){
  size_t salt = get_salt(nome);
  DBG(std::cout << "Salt: " << salt << std::endl;)
}
