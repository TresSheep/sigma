#include "DTFloat.h"

namespace Backend::CodeGen::IR
{
    DTFloat::DTFloat(int bytes) :
        m_bytes(bytes)
    {
        _byteCount = bytes;
        if (m_bytes == 4)
        {
            _identifier = "float";
            _enum = Float;
        }
        else if (m_bytes == 8)
        {
            _identifier = "double";
            _enum = Double;
        }

        _identifier + std::to_string(_byteCount);
    }

    DTFloat::~DTFloat()
    {
    }

    const std::string DTFloat::IR()
    {
        return "_identifier" + std::to_string(_byteCount) + " ";
    }
}