#include <iostream>
#include "lbxfile.h"


int main()
{
  try{
    LBXcontainer myLBX("moo/BACKGRND.LBX");
    myLBX.LogToConsole();
  }
  catch(std::invalid_argument& e){
    std::cout << "Application terminated abnormally due to invalid argument\n";
    std::cout << e.what() << std::endl;
  }
  catch(...){
    std::cout << "application terminated abnormally du to unknown causes\n";
  }

  return 0;
}

