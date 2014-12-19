

#include "lbxerror.h"
#include <boost/format.hpp>

using namespace std;

LBXException::LBXException(unsigned int _ID, string _message):
  excID(_ID),
  std::runtime_error("LBXhandler-thrown exception at line " + to_string(__LINE__) + " of " + __FILE__ + "\n"
             + _message){

}

