#include "lbxfile.h"
#include <boost/format.hpp>

LBXcontainer::LBXcontainer(const string _filename):
  type(LBX_CONTAINER_MAX_TYPES),
  filename(_filename)
{
  filebuffer.open(filename, std::ios_base::in|std::ios_base::binary);
  if (!filebuffer.is_open())
      throw runtime_error("Cannot Open Specified LBX File: " + filename);

  //load all the Header Information
  filebuffer.read(reinterpret_cast<char*>(&filecount), 2);
  filebuffer.read(reinterpret_cast<char*>(&signature), 4);
  filebuffer.read(reinterpret_cast<char*>(&type), 2);

  //chek all offsets and load them in the container
  for (int ii = 0; ii <= filecount; ++ii){
      unsigned int cur_off = 0;
      filebuffer.read(reinterpret_cast<char*>(&cur_off), 4);
      offsets.push_back(cur_off);
    }

  //load filenames if GFX containers
  if ( type == LBX_GFX ) {
      filebuffer.seekg(0x200);
      for (int ii = 0; ii < filecount; ++ii) {
          char cName[9], cDesc[23];
          filebuffer.read(reinterpret_cast<char*>(&cName), 9 );
          filebuffer.read(reinterpret_cast<char*>(&cDesc), 23);
          pair<string, string> dsc(cName, cDesc);
          subfilenames.push_back(dsc);
        }
      subfilenames.push_back(make_pair("EOF", "End Of File"));
    }
}

LBXcontainer::~LBXcontainer(){
  filebuffer.close();
}

void LBXcontainer::LogToConsole(){
  cout << "Number of Files in " + filename + " container: "
            << filecount << "\n" ;

  cout << boost::format("Signature is 0x%08X\n") % signature;
  cout << "LBX Container Type is: ";
  cout << LBXContainerMap[type] + "\n";

  cout << "The file contains the following offsets\n";
  for (int ii = 0; ii <= filecount; ++ii ){
      cout << boost::format("Offset n.%02d: 0x%08X")
              % ii
              % offsets[ii];
      if (type == LBX_GFX) {

      cout << boost::format(" - Named%- 9s -%- 22s\n")
              % subfilenames[ii].first
              % subfilenames[ii].second;
      } else {
          cout << "\n";
      }
    }

}

