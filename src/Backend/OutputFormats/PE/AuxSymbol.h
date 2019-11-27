#pragma once

#include <fstream>

namespace Backend::OutputFormats::PE
{
    class AuxSymbol
    {
    public:
        AuxSymbol()
        {
        }

        ~AuxSymbol()
        {
        }

        virtual void Write(std::ofstream& stream)
        {
        }
    };
}