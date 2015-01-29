#ifndef _UTILS_UTILITIES_H
#define _UTILS_UTILITIES_H

#include <string>


//Utility function prototypes

//Swap endianess of several commmon formats
void endian_swap(unsigned short &x);
void endian_swap(unsigned int &x);
void endian_swap(unsigned long long &x);

std::string getFileName(const char *_path);
std::string getFileName(const std::string _path);

#endif // _UTILS_UTILITIES_H
