#pragma once

#include "DT.h"

namespace Backend::CodeGen::IR
{
    class DTVoid : public DT
    {
    public:
        DTVoid(bool ptr = false);
        ~DTVoid();

        const std::string IR() override;
    };
}