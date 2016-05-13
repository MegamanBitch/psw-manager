#include "crittografia.h"

void cripta_file(std::string nome_file, const std::string password){
  byte pass[AES::BLOCKSIZE];
  byte iv[16];
  byte true_iv[16];

  AutoSeededRandomPool rng;

  //Digest password
  StringSource(password, true, new HashFilter(*(new SHA256), new ArraySink(pass, AES::BLOCKSIZE)));

  //random Initial Vector
  rng.GenerateBlock(iv, 16);
  memset(true_iv, 0, 16);

  //Create object for encrypting
  AES::Encryption aesEncryption(pass, AES::MAX_KEYLENGTH);
  CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, true_iv);

  StreamTransformationFilter *encryptor;
  encryptor = new StreamTransformationFilter(cbcEncryption, new FileSink("criptato.dat"));

  encryptor->Put(iv, 16);

  FileSource(((nome_file + ".dat").c_str()), true, encryptor);

}
