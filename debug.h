#ifndef DEBUG_H
#define DEBUG_H

#include <cassert>

/**
* @file
* A Debugging Message Library for the console.
* Debugging features can be disabled by defining NDEBUG.
*
*/

#ifndef NDEBUG
  #define DBG(a) {a;}
#else
  #define DBG(a)
#endif




#endif
