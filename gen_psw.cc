#include "gen_psw.h"


int getRandom_char(flag_parameters_t &PARAMETERS){
  srand(time(0));
  int random_char;

  if (PARAMETERS.uppercase) {
    random_char = 65 + rand() % RANGE_UPPERCASE;
    DBG(std::cout << random_char << std::endl;)
    return random_char;
  }

  if (PARAMETERS.lowercase) {
    random_char = 97 + rand() % RANGE_LOWERCASE;
    return random_char;
  }

  if (PARAMETERS.digits) {
    random_char = 48 + rand() % RANGE_DIGITS;
    return random_char;
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

  if (PARAMETERS.special) {
    random_char = rand() % RANGE_SPECIAL_CHARACTERS;
    return SPECIAL_CHARACTERS[random_char];
  }

  if (PARAMETERS.brackets) {
    random_char = rand() % RANGE_BRACKETS;
    return BRACKETS[random_char];
  }
  return -1;
}
