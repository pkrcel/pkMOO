

#include <fmt/core.h>
#include <fmt/printf.h>

#include "lbxexception.h"

using namespace std;

LBXException::LBXException(LBXExceptionType _ID,
                           string _sourceFile,
                           unsigned int _sourceLine,
                           string _filename,
                           unsigned int _signature,
                           unsigned int _size,
                           unsigned int _loff) : ex_ID(_ID), sourceFile(_sourceFile), sourceLine(_sourceLine),
                                                 oFilename(_filename), signature(_signature), file_size(_size),
                                                 last_offset(_loff)
{
    cLogMessage = "LBXHandler Exception: " + LBXExceptionMap[ex_ID] + "\n";

    cFullDescriptor = "LBXHandler Exception: " + LBXExceptionMap[ex_ID] + "\n" +
                      "Thrown at line " + to_string(sourceLine) + " of " +
                      sourceFile + "\n";
    switch (ex_ID)
    {
    case LBX_ERR_NOACCESS:
        cFullDescriptor += "Could not open: " + oFilename + "\n";
        break;
    case LBX_ERR_BAD_SIGNATURE:
        cFullDescriptor += "Requested archive has signature: " +
                           (fmt::sprintf("0x%08X\n", signature));
        break;
    case LBX_ERR_WRONG_SIZE:
        cFullDescriptor += "Size check fails! Last Offset in file is: " +
                           (fmt::sprintf("0x%08X against a fize size of 0x%08X\n",
                                         last_offset, file_size));
        break;
    default:
        break;
    }
}
