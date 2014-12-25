#ifndef _UTILS_UTILITIES_H
#define _UTILS_UTILITIES_H

//Utility function prototypes

//Swap endianess of several commmon formats
void endian_swap(unsigned short &x);
void endian_swap(unsigned int &x);
void endian_swap(unsigned long long &x);

#endif // _UTILS_UTILITIES_H
