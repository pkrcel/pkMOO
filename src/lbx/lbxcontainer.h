/*
 * Based on LBX Moo1 File descriptor at
 * https://web.archive.org/web/20060225030719/http://cronel.mube.net/moo/lbx.html
 *
 */

#ifndef _LBX_LBXCONTAINER_H
#define _LBX_LBXCONTAINER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <map>



#include "lbxexception.h"

enum LBXContainerType : unsigned short {
LBX_GFX = 0,
LBX_SOUND,
LBX_FONT,
LBX_INGAMEHELP,
LBX_UNUSED,
LBX_REQD,
LBX_CONTAINER_MAX_TYPES
};

static std::map<LBXContainerType , std::string> LBXContainerMap = {
  { LBX_GFX        , "LBX Graphics Container"     },
  { LBX_SOUND      , "LBX Sound Container"        },
  { LBX_FONT       , "LBX Font/Palette Container" },
  { LBX_INGAMEHELP , "LBX In-Game Help Container" },
  { LBX_UNUSED     , "LBX UNUSED Container"       },
  { LBX_REQD       , "LBX REQD Container"         }
};

class LBXcontainer
{
public:
  //constructors
  LBXcontainer ();                            // empty constructor for obj init
  LBXcontainer (const std::string _filename); // from file constructor.
  ~LBXcontainer();

  //no copy constructors!
  LBXcontainer& operator=(LBXcontainer& ) = delete;
  LBXcontainer(LBXcontainer& ) = delete;
  //no copy constructors!

  void LogArchiveInfo(std::ostream &outstream);
  void Reset();
  void LoadArchiveFromFile(std::string _filename);
  void DumpAllFiles();
  void DumpFile(unsigned int _filenum);
  LBXContainerType getType(void) {return type;}

protected:

private:
  std::string                                       filename;
  std::ifstream                                     filebuffer;
  unsigned short                                    filecount;
  unsigned int                                      signature;
  LBXContainerType                                  type;
  std::vector<off_t>                                offsets;
  std::vector<std::vector<char>>                    subfiles;
  std::vector<std::pair<std::string, std::string>>  subfilenames;
                                                    // in MOO1 only GFX files
                                                    // get subnamed in the
                                                    // container
};

#endif // _LBX_LBXCONTAINER_H
