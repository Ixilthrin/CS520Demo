#include "util.h"
#include <iostream>
using namespace std;
#include "sys/timeb.h"

// Convert a hex value to an integer base 10.
int hexStringToInt(string hexString)
{
    int decimalValue = 0;
    
    sscanf(hexString.c_str(), "%x", &decimalValue);
    //cout<<decimalValue<<endl;
    return decimalValue;
}

struct timeb theTime;
int getMilliseconds()
{
    ftime(&theTime);
    static int initial = theTime.time;
    int t = theTime.time - initial;
    int milliseconds = t * 1000 + theTime.millitm;
    return milliseconds;
}
