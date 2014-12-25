#include <boost/format.hpp>

#include "lbxcontainer.h"

using namespace std;

LBXcontainer::LBXcontainer(const string _filename):
  type(LBX_CONTAINER_MAX_TYPES),
  filename(_filename)
{
  filebuffer.open(filename, ios::in|ios::binary|ios::ate);
  if (!filebuffer.is_open())
      throw LBXException(LBX_ERR_NOACCESS,
                         string(__FILE__).substr(
                           string(__FILE__).rfind("pkMOO\\")),
                         __LINE__,
                         filename,
                         0xDEADBEEF,
                         0x0,
                         0xFFFFFFFF);

  //before reading all info tellg() the filesize and seek back to file byte 0
  off_t filesize = filebuffer.tellg();
  filebuffer.seekg(0, ios::beg);

  //load all the Header Information
  filebuffer.read(reinterpret_cast<char*>(&filecount), 2);
  filebuffer.read(reinterpret_cast<char*>(&signature), 4);
  if (signature != 0x000FEAD)
    throw LBXException(LBX_ERR_BAD_SIGNATURE,
                       string(__FILE__).substr(
                         string(__FILE__).rfind("pkMOO\\")),
                       __LINE__,
                       filename,
                       signature,
                       0x0,
                       0xFFFFFFFF);
  filebuffer.read(reinterpret_cast<char*>(&type), 2);

  //chek all offsets and load them in the container
  for (int ii = 0; ii <= filecount; ++ii){
      unsigned int cur_off = 0;
      filebuffer.read(reinterpret_cast<char*>(&cur_off), 4);
      offsets.push_back(cur_off);
    }

  if (offsets.back() != filesize)
    throw LBXException(LBX_ERR_WRONG_SIZE,
                       string(__FILE__).substr(
                         string(__FILE__).rfind("pkMOO\\")),
                       __LINE__,
                       filename,
                       signature,
                       filesize,
                       offsets.back());

  //load filenames if GFX containers
  if ( type == LBX_GFX ) {
      filebuffer.seekg(0x200);
      for (int ii = 0; ii < filecount; ++ii) {
          char cName[9], cDesc[23];
          filebuffer.read(reinterpret_cast<char*>(&cName), 9 );
          filebuffer.read(reinterpret_cast<char*>(&cDesc), 23);
          subfilenames.push_back(make_pair(cName, cDesc));
        }
      subfilenames.push_back(make_pair("EOF", "End Of File"));
    }
}

LBXcontainer::~LBXcontainer(){
  filebuffer.close();
}

void LBXcontainer::LogTo(ostream &outstream){
  outstream << "Number of Files in " + filename + " container: "
            << filecount << "\n" ;

  outstream << boost::format("Signature is 0x%08X\n") % signature;
  outstream << "LBX Container Type is: ";
  outstream << LBXContainerMap[type] + "\n";

  outstream << "The file contains the following offsets\n";
  for (int ii = 0; ii <= filecount; ++ii ){
      outstream << boost::format("Offset n.%02d: 0x%08X")
                   % ii
                   % offsets[ii];
      if (type == LBX_GFX) {
          outstream << boost::format(" - Named%- 9s -%- 22s")
                       % subfilenames[ii].first
                       % subfilenames[ii].second;
        }
      outstream << "\n";
    }
  outstream.flush();   // needed to be sure to close the output.
}



