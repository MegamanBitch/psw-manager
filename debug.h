#ifndef DEBUG_H
#define DEBUG_H

#include <cassert>

#ifndef NDEBUG
  #define DBG(a) {a;}
#else
  #define DBG(a)
#endif




#endif
