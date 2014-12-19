#include <boost/format.hpp>

#include "lbxfile.h"
#include "lbxerror.h"


LBXcontainer::LBXcontainer(const string _filename):
  type(LBX_CONTAINER_MAX_TYPES),
  filename(_filename)
{
  filebuffer.open(filename, std::ios_base::in|std::ios_base::binary);
  if (!filebuffer.is_open())
      throw LBXException(1, "LBXhandler-thrown exception at line "
                         + to_string(__LINE__) + " of " + __FILE__ + "\n"
                         + "Cannot Open Specified LBX File: " + filename
                         + "\n");

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
          outstream << boost::format(" - Named%- 9s -%- 22s\n")
                       % subfilenames[ii].first
                       % subfilenames[ii].second;
        } else {
          outstream << "\n";
        }
    }
  outstream.flush();   // needed to be sure to close the output.
}



