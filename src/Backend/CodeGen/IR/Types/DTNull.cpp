#include "DTNull.h"

namespace Backend::CodeGen::IR
{
    DTNull::DTNull()
    {
        _identifier = "null";
    }

    DTNull::~DTNull()
    {
    }

    const std::string DTNull::IR()
    {
        return "null";
    }
}