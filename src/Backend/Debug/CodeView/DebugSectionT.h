#pragma once

#include <vector>
#include <fstream>
#include <Backend/OutputFormats/PE/PE.h>

namespace Backend::Debug::CodeView
{
    class DebugSectionT
    {
    public:
        DebugSectionT();
        ~DebugSectionT();

        OutputFormats::PE::Section GetSection();

    private:
        std::vector<uint8_t> m_bytes;
    };
}