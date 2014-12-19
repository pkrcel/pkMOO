#include <iostream>
#include "lbxfile.h"
#include <boost/format.hpp>

using std::cout;

int main(int argc, char* argv[])
{
  try{
    const char* toopen ="moo/BACKGRND.LBX";
    std::ostream *outstream;
    if (argv[1]) {
        toopen = argv[1];
      }
    LBXcontainer myLBX(toopen);
    if (argv[2]) {
        outstream = new std::ofstream(argv[2]);
        if (!((std::ofstream*)outstream)->is_open()) outstream = &cout;
      } else {
        outstream = &cout;
      }
    myLBX.LogTo(*outstream);
  }
  catch(LBXException &e){
    cout << boost::format("LBXhandler-thrown exception with id %d\n")
                          % e.getID();
    cout << e.what();
  }
  catch(...){
    cout << "Application terminated abnormally due to unknown causes\n";
  }
  return 0;
}

