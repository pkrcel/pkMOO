/*
 * Based on LBX Moo1 File descritpor at
 * https://web.archive.org/web/20060225030719/http://cronel.mube.net/moo/lbx.html
 *
 */

#ifndef LBXFILE_H
#define LBXFILE_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <utility>
#include <stdexcept>

using namespace std;

enum LBXContainerType {
LBX_GFX = (unsigned short)0,
LBX_SOUND,
LBX_FONT,
LBX_INGAMEHELP,
LBX_UNUSED,
LBX_REQD,           // in MOO1 REQD.LBX is the only file of this type
LBX_CONTAINER_MAX_TYPES
};
static map<LBXContainerType , string> LBXContainerMap = {
  { LBX_GFX        , "LBX Graphics Container"     },
  { LBX_SOUND      , "LBX Sound Container"        },
  { LBX_FONT       , "LBX Font/Palette Container" },
  { LBX_INGAMEHELP , "LBX In-Game Help Container" },
  { LBX_UNUSED     , "LBX UNUSED Container"       },
  { LBX_REQD       , "LBX REQD Container"         }   // in MOO1 'REQD.LBX' is the is the only file of this type
};

class LBXcontainer
{
private:
  string                        filename;
  ifstream                      filebuffer;
  unsigned short                filecount;
  unsigned int                  signature;
  LBXContainerType              type;
  vector<unsigned int>          offsets;
  vector<streambuf>             subfiles;
  vector<pair<string, string>>  subfilenames;   // in MOO1 only GFX files get subnamed
protected:

public:
  LBXcontainer(const string _filename);
  ~LBXcontainer();

  //no copy constructors!
  LBXcontainer& operator=(LBXcontainer& ) = delete;
  LBXcontainer(LBXcontainer& ) = delete;

  void LogTo(ostream &outstream);

};



#endif // LBXFILE_H
