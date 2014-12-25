#ifndef _LBX_LBXEXCEPTION_H
#define _LBX_LBXEXCEPTION_H

#include <stdexcept>
#include <string>
#include <map>

enum LBXExceptionType : unsigned int {
LBX_ERR_NOACCESS = 1,     // Target file unaccessible on the filesystem.
LBX_ERR_BAD_SIGNATURE,    // LBX container has bad signature
LBX_ERR_WRONG_SIZE,       // LBX container fails the last offset size check
LBX_ERR_MAX_TYPES
};

static std::map<LBXExceptionType , std::string> LBXExceptionMap = {
  { LBX_ERR_NOACCESS        , "Cannot Open specified file"                 },
  { LBX_ERR_BAD_SIGNATURE   , "LBX Container has bad signature"            },
  { LBX_ERR_WRONG_SIZE      , "LBX Container fails size check"             }
};

class LBXException : public std::exception
{
public:
  LBXException(LBXExceptionType _ID,
               std::string _sourceFile,
               unsigned int _sourceLine,
               std::string _filename,
               unsigned int _signature,
               unsigned int _size,
               unsigned int _loff
               );
  virtual ~LBXException() throw() {}

  unsigned int getID(){ return ex_ID; }

  std::string fullDescription(){ return cFullDescriptor;}

  virtual const char *what() const throw(){return cLogMessage.c_str();}

protected:

private:
  LBXExceptionType    ex_ID;
  std::string         sourceFile;
  unsigned int        sourceLine;
  std::string         oFilename;
  unsigned int        signature;
  unsigned int        file_size;
  unsigned int        last_offset;
  std::string         cFullDescriptor;
  std::string         cLogMessage;
};

#endif // _LBX_LBXEXCEPTION_H

