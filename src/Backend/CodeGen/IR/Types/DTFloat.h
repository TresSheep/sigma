#pragma once

#include "DT.h"

namespace Backend::CodeGen::IR
{
    class DTFloat : public DT
    {
    public:
        DTFloat(int bytes);
        ~DTFloat();

        const std::string IR() override;

    private:
        int m_bytes;
    };
}