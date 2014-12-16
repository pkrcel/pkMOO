#include <iostream>
#include "lbxfile.h"


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
        if (!((std::ofstream*)outstream)->is_open()) outstream = &std::cout;
      } else {
        outstream = &std::cout;
      }
    myLBX.LogTo(*outstream);
  }
  catch(std::runtime_error& e){
    std::cout << "Application terminated abnormally due to invalid argument\n";
    std::cout << e.what() << std::endl;
  }
  catch(...){
    std::cout << "Application terminated abnormally due to unknown causes\n";
  }

  return 0;
}

