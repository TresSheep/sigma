#pragma once

#include "DT.h"

namespace Backend::CodeGen::IR
{
    class DTNull : public DT
    {
    public:
        DTNull();
        ~DTNull();

        const std::string IR() override;
    };
}