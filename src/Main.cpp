#include "Driver/Driver.h"
#include <cstring>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    // Command line interface

    uint32_t flags = 0;
    std::string file = "sproj.build";
    std::string out;

    // Parse command line arguments
    for (int i = 0; i < argc; i++)
    {
	if (strcmp(argv[i], "-v") == 0)
	{
	    // Verbose
	    // Print Immediate code output
	    flags |= VERBOSE;
	}
    else if (strcmp(argv[i], "-t") == 0)
    {
        // Verbose
        // Print Immediate code output
        flags |= TIME;
    }
    else if (strcmp(argv[i], "-o") == 0)
    {
        // Executable name
        out = argv[i + 1];
        if (out.find(".exe") == 0)
            out.erase(out.find(".exe"), 4);
    }
    else if (strcmp(argv[i], "-l") == 0)
    {
    }
    else if (strcmp(argv[i], "-h") == 0)
    {
        // Help
        // Print help

        std::cout << "eplus [file to compile] [options] -out [executable]" << std::endl << std::endl;
        std::cout << "-v\tOutput the immediate code" << std::endl;
        std::cout << "-t\tOutput the compilation time" << std::endl;
        std::cout << "-o\tName of the executable" << std::endl;
        std::cout << "-l\tExternal libraries to link to" << std::endl;

        return 0;
    }
	else
	{
        std::string s = argv[i];
        if (s.find(".build") != std::string::npos)
        {
            // The file to compile
            file = argv[i];
        }
	}
    }
    if (!file.empty())
    {
#ifdef DEBUG
        file = "b:/sigma/test/sproj.build";
#endif
        Driver::Driver driver;

        if (driver.ParseFile(file, flags, out))
        {
            std::cout << "Build succeeded -> ";
#ifdef WINDOWS
            std::cout << out << ".exe";
#elif LINUX
            std::cout << out << std::endl;
#endif
        }
        else
        {
            std::cout << "Build failed" << std::endl;
        }
    }

    // Link

    return 0;
}
