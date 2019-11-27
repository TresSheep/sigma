#pragma once

#include "DT.h"

namespace Backend::CodeGen::IR
{
    class DTInt : public DT
    {
    public:
        DTInt(int bytes, bool ptr = false);
        ~DTInt();

        void SetValue(std::string_view val);
        std::string_view GetValue();

        const std::string IR() override;

    private:
        int m_bytes;
        std::string m_val;
    };
}