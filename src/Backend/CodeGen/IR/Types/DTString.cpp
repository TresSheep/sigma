#include "DTString.h"

namespace Backend::CodeGen::IR
{
    DTString::DTString(std::string_view content) :
        m_content(content)
    {
        _byteCount = 0;
        _ptr = false;
        _enum = String;

        _identifier = "i8*";
    }

    DTString::~DTString()
    {
    }

    const std::string DTString::IR()
    {
        return "i8* \"" + m_content + "\"";
    }
}