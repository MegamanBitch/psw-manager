#ifndef GEN_PSW_H
#define GEN_PSW_H

#include <iostream>
#include <cstdlib>
#include "struttura_dati.h"


const int RANGE_UPPERCASE = 25;
const int RANGE_LOWERCASE = 25;
const int RANGE_DIGITS = 9;

static const int SPECIAL_CHARACTERS[] = {33, 34, 35, 36, 37, 38, 39, 42, 43, 44, 46, 47, 58, 59, 61, 63, 64
                                          92, 94, 96, 124, 126};

int getRandom_char(flag_parameters_t &PARAMETERS);






#endif
