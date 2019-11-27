#pragma once

#include "DT.h"
#include "../IRContext.h"

namespace Backend::CodeGen::IR
{
    class DTString : public DT
    {
    public:
        DTString(std::string_view content);
        ~DTString();

        const std::string IR() override;

    private:
        std::string m_content;
    };
}