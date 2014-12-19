
#include "lbxerror.h"

using namespace std;

LBXException::LBXException(unsigned int _ID, string _message):
  excID(_ID),
  std::runtime_error(_message){}


