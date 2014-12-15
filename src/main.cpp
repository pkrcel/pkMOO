#include <iostream>
#include "lbxfile.h"


int main(int argc, char* argv[])
{
  try{
    const char* toopen ="moo/BACKGRND.LBX";
    if (argv[1]) {
        toopen = argv[1];
      }
    LBXcontainer myLBX(toopen);
    myLBX.LogToConsole();
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

