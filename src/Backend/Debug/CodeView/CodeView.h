#pragma once

#include "DebugSectionS.h"
#include "DebugSectionT.h"
#include <Backend/OutputFormats/PE/PE.h>

namespace Backend::Debug::CodeView
{
    class CodeView
    {
    public:
        CodeView(OutputFormats::PE::PE& pe);
        ~CodeView();

    private:
        OutputFormats::PE::PE& m_pe;
    };
}