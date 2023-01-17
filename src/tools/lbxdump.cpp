#include <iostream>
#include <fmt/core.h>
#include <fmt/printf.h>
#include <string>
#include <filesystem>

#include "lbxcontainer.h"
#include "utilities.h"

using std::cout;
using std::filesystem::path;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << fmt::sprintf("\nIncorrect Number of arguments passed: %d\n", (argc - 1))
             << fmt::sprintf("\nUsage: %s SOURCE [DEST] \n\n", std::string(path(argv[0]).filename()))
             << "\t SOURCE - source LBX Archive\n"
             << "\t DEST   - destination file (redirect to stdout if omitted)\n"
             << std::endl;
        return 1;
    }
    try
    {
        LBXcontainer myLBX(argv[1]);
        std::ostream *outstream;
        if (argv[2])
        {
            outstream = new std::ofstream(argv[2]);
            if (!((std::ofstream *)outstream)->is_open())
                outstream = &cout;
        }
        else
        {
            outstream = &cout;
        }
        myLBX.LogArchiveInfo(*outstream);
        myLBX.DumpAllFiles();
    }
    catch (LBXException &e)
    {
        cout << e.fullDescription();
        return (-e.getID());
    }
    catch (std::exception &e)
    {
        cout << "Application terminated abnormally!\n";
        cout << e.what();
        return (-0xDEADDEAD);
    }
    return 0;
}
