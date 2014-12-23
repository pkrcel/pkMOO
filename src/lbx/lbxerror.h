#ifndef ERROR_H
#define ERROR_H

#include <stdexcept>
#include <string>
#include <map>

enum LBXExceptionType {
LBX_ERR_NOACCESS = 0,     // Target file unaccessible on the filesystem.
LBX_ERR_BAD_SIGNATURE,    // LBX container has bad signature
LBX_ERR_WRONG_SIZE,       // LBX container fails the last offset size check
LBX_ERR_MAX_TYPES
};

static std::map<LBXExceptionType , std::string> LBXExceptionMap = {
  { LBX_ERR_NOACCESS        , "Cannot Open specificed file"                },
  { LBX_ERR_BAD_SIGNATURE   , "LBX Container has bad signature"            },
  { LBX_ERR_WRONG_SIZE      , "LBX Container fails size check"             }
};


class LBXException : public std::exception
{
private:
  LBXExceptionType      ex_ID;
  std::string           sourceFile;
  unsigned int          sourceLine;
  std::string           oFilename;
  unsigned int          signature;
  unsigned int          file_size;
  unsigned int          last_offset;
  std::string           cFullDescriptor;
  std::string           cLogMessage;
protected:

public:
  LBXException(LBXExceptionType _ID,
               std::string _sourceFile,
               unsigned int _sourceLine,
               std::string _filename,
               unsigned int _signature,
               unsigned int _size,
               unsigned int _loff
               );
  virtual ~LBXException(){}

  unsigned int getID(){ return ex_ID; }

  std::string fullDescription(){ return cFullDescriptor;}

  const char *what(){return cLogMessage.c_str();}

};

#endif // ERROR_H

