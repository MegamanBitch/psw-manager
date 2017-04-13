#include "gen_psw.h"


unsigned short generate_lowercase(unsigned short start, unsigned short end){
  // Se la lunghezza della psw e' 4 decido di restituire 1 lowercase, 1 uppercase
  // 1 digit, 1 special. E' il best case nel worst case
  if (end == 4)
    return 1;

  // Se la lunghezza e' minore di 4 restituisco tutte lowercase
  else if (end < 4)
    return end;

  // Se la lunghezza e' maggiore di 4 restituisco un numero random di lowercase
  // nel range [1,...,N-4]
  else
    return 1 + (std::rand() % (end - 4));
}

unsigned short generate_uppercase(const unsigned short start, const unsigned short end){
  if (end == 3)
    return 1;

  else if (end < 3)
    return 0;

  else
    return 1 + (std::rand() % (end - 3));
}

unsigned short generate_digits(const unsigned short start, const unsigned short end){
  if (end == 2)
    return 1;

  else if (end < 2)
    return 0;

  else
    return 1 + (std::rand() % (end - 2));
}

unsigned short generate_special(const unsigned short start, const unsigned short end){
  if (end == 1)
    return 1;
  else
    return end;
}

void generate_numbers(parameters_t &parameters, const unsigned short lun_psw){
  parameters.lowercase = generate_lowercase(1, lun_psw);
  parameters.uppercase = generate_uppercase(1, lun_psw - parameters.lowercase);
  parameters.digits = generate_digits(1, lun_psw - parameters.lowercase - parameters.uppercase);
  parameters.special = generate_special(1, lun_psw - parameters.lowercase - parameters.uppercase - parameters.digits);
}
