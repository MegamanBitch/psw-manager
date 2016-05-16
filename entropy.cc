#include "entropy.h"

int get_entropy(const gchar *c) {
  unsigned short has_lowercase, has_uppercase, has_digit, has_specialCaracter = 0;
  unsigned short ris;
  switch (pool_of_character(c)) {
    case LOWERCASE:
      has_lowercase++;

      if (has_uppercase == 0 && has_digit > 0 && has_specialCaracter == 0) {
        ris *= log(36) / log(2);
      }
      else if (has_uppercase == 0 && has_digit == 0 && has_specialCaracter > 0) {
        ris *= log(59) / log(2);
      }
      else if (has_uppercase == 0 && has_digit > 0 && has_specialCaracter > 0) {
        ris *= log(99) / log(2);
      }

      else if (has_uppercase > 0 && has_digit == 0 && has_specialCaracter == 0) {
        ris *= log(52) / log(2);
      }
      else if (has_uppercase > 0 && has_digit > 0 && has_specialCaracter == 0) {
        ris *= log(72) / log(2);
      }
      else if (has_uppercase > 0 && has_digit == 0 && has_specialCaracter > 0) {
        ris *= log(85) / log (2);
      }
      else if (has_uppercase > 0 && has_digit > 0 && has_specialCaracter > 0) {
        ris *= log(95) / log(2);
      }

      else if (has_uppercase == 0 && has_digit == 0 && has_specialCaracter == 0) {
        ris *= log(26) / log(2);
      }
      break;
    case UPPERCASE:
      has_uppercase++;
      if (has_lowercase == 0 && has_digit > 0 && has_specialCaracter == 0) {
        ris *= log(36) / log(2);
      }
      else if (has_lowercase == 0 && has_digit == 0 && has_specialCaracter > 0) {
        ris *= log(59) / log(2);
      }
      else if (has_lowercase == 0 && has_digit > 0 && has_specialCaracter > 0) {
        ris *= log(99) / log(2);
      }

      else if (has_lowercase > 0 && has_digit == 0 && has_specialCaracter == 0) {
        ris *= log(52) / log(2);
      }
      else if (has_lowercase > 0 && has_digit > 0 && has_specialCaracter == 0) {
        ris *= log(72) / log(2);
      }
      else if (has_lowercase > 0 && has_digit == 0 && has_specialCaracter > 0) {
        ris *= log(85) / log (2);
      }
      else if (has_lowercase > 0 && has_digit > 0 && has_specialCaracter > 0) {
        ris *= log(95) / log(2);
      }

      else {
        ris *= log(26) / log(2);
      }
      break;
    case DIGIT:
      has_digit++;
      if (has_uppercase == 0 && has_lowercase > 0 && has_specialCaracter == 0) {
        ris *= log(36) / log(2);
      }
      else if (has_uppercase == 0 && has_lowercase == 0 && has_specialCaracter > 0) {
        ris *= log(59) / log(2);
      }
      else if (has_uppercase == 0 && has_lowercase > 0 && has_specialCaracter > 0) {
        ris *= log(99) / log(2);
      }

      else if (has_uppercase > 0 && has_lowercase == 0 && has_specialCaracter == 0) {
        ris *= log(52) / log(2);
      }
      else if (has_uppercase > 0 && has_lowercase > 0 && has_specialCaracter == 0) {
        ris *= log(72) / log(2);
      }
      else if (has_uppercase > 0 && has_lowercase == 0 && has_specialCaracter > 0) {
        ris *= log(85) / log (2);
      }
      else if (has_uppercase > 0 && has_lowercase > 0 && has_specialCaracter > 0) {
        ris *= log(95) / log(2);
      }

      else {
        ris *= log(10) / log(2);
      }
      break;
    case SPECIAL_CHARACTER:
      has_specialCaracter++;
      if (has_uppercase == 0 && has_digit > 0 && has_lowercase == 0) {
        ris *= log(36) / log(2);
      }
      else if (has_uppercase == 0 && has_digit == 0 && has_lowercase > 0) {
        ris *= log(59) / log(2);
      }
      else if (has_uppercase == 0 && has_digit > 0 && has_lowercase > 0) {
        ris *= log(99) / log(2);
      }

      else if (has_uppercase > 0 && has_digit == 0 && has_lowercase == 0) {
        ris *= log(52) / log(2);
      }
      else if (has_uppercase > 0 && has_digit > 0 && has_lowercase == 0) {
        ris *= log(72) / log(2);
      }
      else if (has_uppercase > 0 && has_digit == 0 && has_lowercase > 0) {
        ris *= log(85) / log (2);
      }
      else if (has_uppercase > 0 && has_digit > 0 && has_lowercase > 0) {
        ris *= log(95) / log(2);
      }

      else {
        ris *= log(33) / log(2);
      }
      break;
  }

  return ris;

}

int pool_of_character(const gchar *car){
  if (*car >= 'a' && *car <= 'z') {
    return LOWERCASE;
  }
  else if (*car >= 'A' && *car <= 'Z') {
    return UPPERCASE;
  }
  else if ((*car >= ' ' && *car <= '/') || (*car >= ':' && *car <= '@') || (*car >= '[' && *car <= '`') || (*car >= '{' && *car <= '~')) {
    return SPECIAL_CHARACTER;
  }
  else if (*car >= '0' && *car <= '9') {
    return DIGIT;
  }
}
