#include <iostream>
#include <boost/format.hpp>
#include <cstring>

#include "lbxcontainer.h"
#include "utilities.h"

using std::cout;


int main(int argc, char* argv[])
{
  if (argc < 2) {
      cout << boost::format("\nIncorrect Number of arguments passed: %d\n")
           % (argc - 1) << boost::format("\nUsage: %s SOURCE \n\n")
           % getFileName(argv[0])  << "\t SOURCE - source LBX Archive\n"
           << "\t source LBX Archive must be of the GFX container type\n"
           << std::endl;
      return 1;
    }
  try{
    LBXcontainer myLBX(argv[1]);
    std::ostream *outstream;
  }
  catch(LBXException &e){
    cout << e.fullDescription() << std::endl;
    return (-e.getID());
  }
  catch(std::exception &e){
    cout << "Application terminated abnormally!\n";
    cout << e.what();
    return (-0xDEADDEAD);
  }
  return 0;
}


