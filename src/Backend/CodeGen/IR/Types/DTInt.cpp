#include "DTInt.h"

namespace Backend::CodeGen::IR
{
    DTInt::DTInt(int bytes, bool ptr) :
        m_bytes(bytes), m_val("0")
    {
        _ptr = ptr;
        _identifier = "i";
        _byteCount = bytes;
        if (bytes == 1)
            _enum = Int8;
        else if (bytes == 2)
            _enum = Int16;
        else if (bytes == 4)
            _enum = Int32;
        else
            _enum = Int64;

        _identifier = "i" + std::to_string(m_bytes * 8);
        //if (_ptr)
        //    _identifier += "*";
    }

    DTInt::~DTInt()
    {
    }

    void DTInt::SetValue(std::string_view val)
    {
        m_val = val;
    }

    std::string_view DTInt::GetValue()
    {
        return m_val;
    }

    const std::string DTInt::IR()
    {
        return "i" + std::to_string(m_bytes * 8) + " " + m_val;
    }
}