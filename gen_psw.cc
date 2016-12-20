#include "gen_psw.h"


int getRandom_char(flag_parameters_t &PARAMETERS, unsigned short random_char){

  if (random_char >= 'a' && random_char <= 'z') {
    DBG(std::cout << "lowercase" << std::endl;)
    if (PARAMETERS.lowercase) {
      random_char = 97 + (rand() % RANGE_LOWERCASE);
      return random_char;
    }
  }

  else if (random_char >= 'A' && random_char <= 'Z') {
    DBG(std::cout << "uppercase" << std::endl;)
    if (PARAMETERS.uppercase) {
      random_char = 65 + (rand() % RANGE_UPPERCASE);
      return random_char;
    }
  }

  else if ((random_char >= ' ' && random_char <= '/') || (random_char >= ':' && random_char <= '@') ||
           (random_char >= '[' && random_char <= '`') || (random_char >= '{' && random_char <= '~')) {
    DBG(std::cout << "special character" << std::endl;)
    if (PARAMETERS.special) {
      random_char = rand() % RANGE_SPECIAL_CHARACTERS;
      return SPECIAL_CHARACTERS[random_char];
    }
    if (PARAMETERS.space) {
      return 32;
    }
    if (PARAMETERS.minus) {
      return 45;
    }
    if (PARAMETERS.underscore) {
      return 95;
    }
    if (PARAMETERS.brackets) {
      random_char = rand() % RANGE_BRACKETS;
      return BRACKETS[random_char];
    }

  }

  else if (random_char >= '0' && random_char <= '9') {
    DBG(std::cout << "digit" << std::endl;)
    if (PARAMETERS.digits) {
      random_char = 48 + (rand() % RANGE_DIGITS);
      return random_char;
    }
  }
  DBG(std::cout << "-1 " << random_char << std::endl;)
  return -1;
}
