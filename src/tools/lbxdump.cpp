#include <iostream>
#include <boost/format.hpp>

#include "lbxfile.h"


using std::cout;

std::string getAppName(const char* path){
  // sanitize application name - only windows for now
  // path separator is '\' even in MSYS2 (and so Cygwin I suppose)
  // could be done in Boost::Filesystem but didnì't want to carry over yet
  // another dependency
  char pathsep = '\\';
  std::string name(path);
  return name.substr(name.find_last_of(pathsep)+1, name.find_last_of('.'));
}

int main(int argc, char* argv[])
{
  if (argc < 2) {
      cout << boost::format("\nIncorrect Number of arguments passed: %d\n")
              % (argc - 1)
           << boost::format("\nUsage: %s SOURCE [DEST] \n\n")
              % getAppName(argv[0])
           << "\t SOURCE - source LBX Archive\n"
           << "\t DEST   - destination text file (if omitted text is thrown to stdout)\n"
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
  }
  catch(std::exception &e){
    cout << "Application terminated abnormally due to unknown causes\n";
    cout << e.what() << std::endl;
  }
  return 0;
}

