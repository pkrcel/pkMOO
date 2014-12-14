#include "lbxfile.h"

LBXcontainer::LBXcontainer(const std::string _filename)
{
  filename = _filename;
  filebuffer.open(filename, std::ios_base::in|std::ios_base::binary);
  if (!filebuffer.is_open())
      throw std::invalid_argument("Cannot Open Specified LBX File: " + filename);

  //do sect all the Header Information
  filebuffer.read(reinterpret_cast<char*>(&filecount), 2);
  filebuffer.read(reinterpret_cast<char*>(&signature), 4);
}

LBXcontainer::~LBXcontainer(){
  filebuffer.close();
}

void LBXcontainer::LogToConsole()
{
  std::cout << " Number of Files in " + filename + " container: " << filecount << "\n" ;
  std::cout << " Signature is " << std::hex << "0x" <<
               std::setfill('0') << std::setw(2*sizeof(signature)) <<signature << "\n" ;
}

