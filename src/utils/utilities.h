#ifndef UTILITIES_H
#define UTILITIES_H

//Utility function prototypes

//Swap endianess of several commmon formats
void endian_swap(unsigned short &x);
void endian_swap(unsigned int &x);
void endian_swap(unsigned long long &x);

#endif // UTILITIES_H
