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
#include <stdexcept>

enum LBXfiletype {
  LBX_gfx = (unsigned short)0,
  LBX_sound,
  LBX_font,
  LBX_ingamehelp,
  LBX_unused,
  LBX_reqd,           // in MOO1 REQD.LBX is the only file of this type
  LBX_MAX_TYPES
};

class LBXcontainer
{
private:
  std::string                   filename;
  std::ifstream                 filebuffer;
  unsigned short                filecount;
  unsigned int                  signature;
  LBXfiletype                   type;
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
