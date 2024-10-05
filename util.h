#ifndef __util_h__
#define __util_h__

#include "main.h"
#include <string>

// Convert a hex value to an integer base 10.
int hexStringToInt(string hexString);

// Get milliseconds since first call to this function
int getMilliseconds();
#endif
