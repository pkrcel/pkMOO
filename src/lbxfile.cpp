#include "lbxfile.h"
#include <boost/format.hpp>

LBXcontainer::LBXcontainer(const std::string _filename):
  type(LBX_CONTAINER_MAX_TYPES),
  filename(_filename)
{
  filebuffer.open(filename, std::ios_base::in|std::ios_base::binary);
  if (!filebuffer.is_open())
      throw std::runtime_error("Cannot Open Specified LBX File: " + filename);

  //do sect all the Header Information
  filebuffer.read(reinterpret_cast<char*>(&filecount), 2);
  filebuffer.read(reinterpret_cast<char*>(&signature), 4);
  filebuffer.read(reinterpret_cast<char*>(&type), 2);

  //chek all offsets and load them in the container
  for (int ii = 0; ii <= filecount; ++ii){
      unsigned int cur_off = 0;
      filebuffer.read(reinterpret_cast<char*>(&cur_off), 4);
      offsets.push_back(cur_off);
    }

}

LBXcontainer::~LBXcontainer(){
  filebuffer.close();
}

void LBXcontainer::LogToConsole()
{
  std::cout << "Number of Files in " + filename + " container: "
            << filecount << "\n" ;
  std::cout << boost::format("Signature is 0x%08X\n") % signature;
  std::cout << "LBX Container Type is: ";
  std::cout << LBXContainerMap[type] + "\n";
//  switch (type) {
//    case LBX_gfx:
//      std::cout << "LBX Graphics Container File\n";
//      break;
//    default:
//      std::cout << "UNKNOWN!\n";
//      break;
//    }
  std::cout << "The file contains the following offsets\n";
  for (int ii = 0; ii <= filecount; ++ii ){
      std::cout << boost::format("Offset n.%02d: 0x%08X\n")
                   % ii
                   % offsets[ii];
    }
}

