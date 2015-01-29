#include <boost/format.hpp>

#include "lbxcontainer.h"
#include "utilities.h"

using namespace std;

LBXcontainer::LBXcontainer():
  type(LBX_CONTAINER_MAX_TYPES),
  signature(0xFFFFFFFF),  //this signature is invalid and means "uninitialized"
  filename()
{

}

LBXcontainer::LBXcontainer(const string _filename):
  type(LBX_CONTAINER_MAX_TYPES),
  filename(_filename)
{
  LoadArchiveFromFile(filename);
}

LBXcontainer::~LBXcontainer(){
  filebuffer.close();
}

void LBXcontainer::LogArchiveInfo(ostream &outstream)
{
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

void LBXcontainer::Reset()
{
  //clears and destroys all internal data, initializes paramters as in empty
  //constructor
  //let's hope to have implemented RAII correctly (!)
  type = LBX_CONTAINER_MAX_TYPES;
  signature = 0xFFFFFFFF;
  filename.clear();
  filebuffer.close();
  filecount = 0;
  subfilenames.clear();
  subfiles.clear();
  offsets.clear();
}

void LBXcontainer::LoadArchiveFromFile(string _filename)
{
  filename = _filename;
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
  //NOTE: filebuffer was open with ios::ate.
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

  //load filenames if GFX containers have it.
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

  //load subfiles in memory (might change this later if overkill)
  filebuffer.seekg(offsets[0]);                     //seek the first offset
  for (int ii = 0; ii < offsets.size()-1 ; ++ii){   // scour through offsets
      auto tSize = offsets[ii+1] - offsets[ii];
      vector<char> tBuffer (tSize);
      filebuffer.seekg(offsets[ii]);
      filebuffer.read(reinterpret_cast<char*>(&tBuffer[0]),tSize);
      subfiles.push_back(tBuffer);
    }
}

void LBXcontainer::DumpAllFiles()
{
  int ii = 0;
  for (vector<char> subfile : subfiles) {
      string subspecname;
      subspecname = ( ii < subfilenames.size()) ?
                              subfilenames[ii].first + "." : "";
      ofstream tmpOutFile;
      tmpOutFile.open(getFileName(filename) + "." + subspecname
                      + (boost::format("%03d") % ii).str() + ".moo1file",
                      ios::binary|ios::out);
      tmpOutFile.write(reinterpret_cast<char*>(&subfile[0]),
                       subfile.size() * sizeof(char));
      ii++;
    }
}


