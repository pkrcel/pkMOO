#include <iostream>
#include <boost/format.hpp>
#include <cstring>

#include "lbxcontainer.h"


using std::cout;

std::string getAppName(const char* path){
  // sanitize application name - only windows for now
  // path separator is '\' even in MSYS2 (and since Cygwin 1.7 seems)
  // could be done in Boost::Filesystem but didn't want to carry over yet
  // another BINARY dependency (boost_filesystem-mt and boost_system-mt)
  static const char* pathsep = "/\\";
  std::string name(path);
  auto first = name.find_last_of(pathsep) +1;
  auto last = name.find_last_of('.');
  return name.substr(first, last-first);
}

int main(int argc, char* argv[])
{
  if (argc < 2) {
      cout << boost::format("\nIncorrect Number of arguments passed: %d\n")
           % (argc - 1) << boost::format("\nUsage: %s SOURCE [DEST] \n\n")
           % getAppName(argv[0])  << "\t SOURCE - source LBX Archive\n"
           << "\t DEST   - destination file (redirect to stdout if omitted)\n"
           << std::endl;
      return 1;
    }
  try{
    LBXcontainer myLBX(argv[1]);
    std::ostream *outstream;
    if (argv[2]) {
        outstream = new std::ofstream(argv[2]);
        if (!((std::ofstream*)outstream)->is_open()) outstream = &cout;
      } else {
        outstream = &cout;
      }
    myLBX.LogTo(*outstream);
  }
  catch(LBXException &e){
    cout << e.fullDescription();
    return (-e.getID());
  }
  catch(std::exception &e){
    cout << "Application terminated abnormally!\n";
    cout << e.what();
    return (-0xDEADDEAD);
  }
  return 0;
}

