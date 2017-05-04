#include "gen_psw.h"


unsigned short generate_lowercase(unsigned short end){
  if (end == 4)
    return 1;
  else if (end < 4)
    return end;
  else
    return 1 + (std::rand() % (end - 4));
}

unsigned short generate_uppercase(unsigned short end){
  if (end == 3)
    return 1;
  else if (end < 3)
    return 0;
  else
    return 1 + (std::rand() % (end - 3));
}

unsigned short generate_digits(unsigned short end){
  if (end == 2)
    return 1;
  else if (end < 2)
    return 0;
  else
    return 1 + (std::rand() % (end - 2));
}

unsigned short generate_special(unsigned short end){
  if (end == 1)
    return 1;
  else
    return end;
}

void generate_numbers(parameters_t &parameters, unsigned short lun_psw){
  parameters.lowercase = generate_lowercase(lun_psw);
  parameters.uppercase = generate_uppercase(lun_psw - parameters.lowercase);
  parameters.digits = generate_digits(lun_psw - parameters.lowercase - parameters.uppercase);
  parameters.special = generate_special(lun_psw - parameters.lowercase - parameters.uppercase - parameters.digits);
}
