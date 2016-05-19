#include "gen_psw.h"


int getRandom_char(flag_parameters_t &PARAMETERS){
  srand(time(0));

  int random_char;

  if (PARAMETERS.uppercase) {
    random_char = 65 + rand() % RANGE_UPPERCASE;
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
    /* code */
  }
}
