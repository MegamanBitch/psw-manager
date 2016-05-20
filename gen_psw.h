#ifndef GEN_PSW_H
#define GEN_PSW_H

#include <iostream>
#include <cstdlib>
#include "struttura_dati.h"
#include "debug.h"


const int RANGE_UPPERCASE = 25;
const int RANGE_LOWERCASE = 25;
const int RANGE_DIGITS = 9;
const int RANGE_SPECIAL_CHARACTERS = 22;
const int RANGE_BRACKETS = 8;


static const int BRACKETS[8] = {40, 41, 60, 62, 91, 93, 123, 125};
static const int SPECIAL_CHARACTERS[22] = {33, 34, 35, 36, 37, 38, 39, 42, 43, 44, 46, 47, 58, 59, 61, 63, 64,
                                            92, 94, 96, 124, 126};

int getRandom_char(flag_parameters_t &PARAMETERS);






#endif
