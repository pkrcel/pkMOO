#ifndef ERROR_H
#define ERROR_H


#include <stdexcept>
#include <string>


class LBXException : public std::runtime_error
{
private:
  unsigned int excID;
protected:

public:
  LBXException(unsigned int _ID, std::string _message);
  virtual ~LBXException(){}

  unsigned int getID(){ return excID; }
};

#endif // ERROR_H

