#pragma once

#include "DT.h"

namespace Backend::CodeGen::IR
{
    class DTCustom : public DT
    {
    public:
        DTCustom(std::string_view id, bool ptr = false);
        ~DTCustom();

        const std::string IR() override;

    private:
        std::string m_id;
        std::string m_val;
    };
}