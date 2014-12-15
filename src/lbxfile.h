/*
 * Based on LB Moo1 File descritpor at
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
#include <stdexcept>

enum LBXContainerType {
LBX_GFX = (unsigned short)0,
LBX_SOUND,
LBX_FONT,
LBX_INGAMEHELP,
LBX_UNUSED,
LBX_REQD,           // in MOO1 REQD.LBX is the only file of this type
LBX_CONTAINER_MAX_TYPES
};
static std::map<LBXContainerType , std::string> LBXContainerMap = {
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
  std::string                   filename;
  std::ifstream                 filebuffer;
  unsigned short                filecount;
  unsigned int                  signature;
  LBXContainerType              type;
  std::vector<unsigned int>     offsets;
  std::vector<std::streambuf>   subfiles;
protected:

public:
  LBXcontainer(const std::string  _filename);
  ~LBXcontainer();

  //no copy constructors!
  LBXcontainer& operator=(LBXcontainer& ) = delete;
  LBXcontainer(LBXcontainer& ) = delete;

  void LogToConsole();

};

#endif // LBXFILE_H
