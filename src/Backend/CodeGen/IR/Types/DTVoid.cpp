#include "DTVoid.h"

namespace Backend::CodeGen::IR
{
    DTVoid::DTVoid(bool ptr)
    {
        _identifier = "void";
        _enum = Void;
        _ptr = ptr;
        if (ptr)
            _identifier = "[void]";
    }

    DTVoid::~DTVoid()
    {
    }

    const std::string DTVoid::IR()
    {
        return _identifier + " ";
    }
}