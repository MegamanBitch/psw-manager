#include "entropy.h"

unsigned short has_lowercase = 0;
unsigned short has_uppercase = 0;
unsigned short has_digit = 0;
unsigned short has_specialCaracter = 0;
double ris = 0;


void entropy_azzera(){
  has_lowercase = 0;
  has_uppercase = 0;
  has_digit = 0;
  has_specialCaracter = 0;
  ris = 0;
}


double get_entropy(const gchar *c) {

  switch (pool_of_character(c)) {
    case LOWERCASE:
      has_lowercase++;

      if (has_uppercase == 0 && has_digit > 0 && has_specialCaracter == 0) {
        ris += log(36) / log(2);
      }
      else if (has_uppercase == 0 && has_digit == 0 && has_specialCaracter > 0) {
        ris += log(59) / log(2);
      }
      else if (has_uppercase == 0 && has_digit > 0 && has_specialCaracter > 0) {
        ris += log(66) / log(2);
      }

      else if (has_uppercase > 0 && has_digit == 0 && has_specialCaracter == 0) {
        ris += log(52) / log(2);
      }
      else if (has_uppercase > 0 && has_digit > 0 && has_specialCaracter == 0) {
        ris += log(62) / log(2);
      }
      else if (has_uppercase > 0 && has_digit == 0 && has_specialCaracter > 0) {
        ris += log(85) / log (2);
      }
      else if (has_uppercase > 0 && has_digit > 0 && has_specialCaracter > 0) {
        ris += log(95) / log(2);
      }

      else if (has_uppercase == 0 && has_digit == 0 && has_specialCaracter == 0) {
        ris += log(26) / log(2);
      }
      break;
    case UPPERCASE:
      has_uppercase++;
      if (has_lowercase == 0 && has_digit > 0 && has_specialCaracter == 0) {
        ris += log(36) / log(2);
      }
      else if (has_lowercase == 0 && has_digit == 0 && has_specialCaracter > 0) {
        ris += log(59) / log(2);
      }
      else if (has_lowercase == 0 && has_digit > 0 && has_specialCaracter > 0) {
        ris += log(69) / log(2);
      }

      else if (has_lowercase > 0 && has_digit == 0 && has_specialCaracter == 0) {
        ris += log(52) / log(2);
      }
      else if (has_lowercase > 0 && has_digit > 0 && has_specialCaracter == 0) {
        ris += log(62) / log(2);
      }
      else if (has_lowercase > 0 && has_digit == 0 && has_specialCaracter > 0) {
        ris += log(85) / log (2);
      }
      else if (has_lowercase > 0 && has_digit > 0 && has_specialCaracter > 0) {
        ris += log(95) / log(2);
      }

      else {
        ris += log(26) / log(2);
      }
      break;
    case DIGIT:
      has_digit++;
      if (has_uppercase == 0 && has_lowercase > 0 && has_specialCaracter == 0) {
        ris += log(36) / log(2);
      }
      else if (has_uppercase == 0 && has_lowercase == 0 && has_specialCaracter > 0) {
        ris += log(59) / log(2);
      }
      else if (has_uppercase == 0 && has_lowercase > 0 && has_specialCaracter > 0) {
        ris += log(69) / log(2);
      }

      else if (has_uppercase > 0 && has_lowercase == 0 && has_specialCaracter == 0) {
        ris += log(52) / log(2);
      }
      else if (has_uppercase > 0 && has_lowercase > 0 && has_specialCaracter == 0) {
        ris += log(62) / log(2);
      }
      else if (has_uppercase > 0 && has_lowercase == 0 && has_specialCaracter > 0) {
        ris += log(85) / log (2);
      }
      else if (has_uppercase > 0 && has_lowercase > 0 && has_specialCaracter > 0) {
        ris += log(95) / log(2);
      }

      else {
        ris += log(10) / log(2);
      }
      break;
    case SPECIAL_CHARACTER:
      has_specialCaracter++;
      if (has_uppercase == 0 && has_digit > 0 && has_lowercase == 0) {
        ris += log(36) / log(2);
      }
      else if (has_uppercase == 0 && has_digit == 0 && has_lowercase > 0) {
        ris += log(59) / log(2);
      }
      else if (has_uppercase == 0 && has_digit > 0 && has_lowercase > 0) {
        ris += log(69) / log(2);
      }

      else if (has_uppercase > 0 && has_digit == 0 && has_lowercase == 0) {
        ris += log(52) / log(2);
      }
      else if (has_uppercase > 0 && has_digit > 0 && has_lowercase == 0) {
        ris += log(62) / log(2);
      }
      else if (has_uppercase > 0 && has_digit == 0 && has_lowercase > 0) {
        ris += log(85) / log (2);
      }
      else if (has_uppercase > 0 && has_digit > 0 && has_lowercase > 0) {
        ris += log(95) / log(2);
      }

      else {
        ris += log(33) / log(2);
      }
      break;
  }

  DBG(std::cout << "Ris funzione entropy: " << ris << std::endl;);
  return ris;

}

int pool_of_character(const gchar *car){
  if (*car >= 'a' && *car <= 'z') {
    DBG(std::cout << "lowercase" << std::endl;)
    return LOWERCASE;
  }
  else if (*car >= 'A' && *car <= 'Z') {
    DBG(std::cout << "uppercase" << std::endl;)
    return UPPERCASE;
  }
  else if ((*car >= ' ' && *car <= '/') || (*car >= ':' && *car <= '@') || (*car >= '[' && *car <= '`') || (*car >= '{' && *car <= '~')) {
    DBG(std::cout << "special character" << std::endl;)
    return SPECIAL_CHARACTER;
  }
  else if (*car >= '0' && *car <= '9') {
    DBG(std::cout << "digit" << std::endl;)
    return DIGIT;
  }
  return -1;
}
