#pragma once

#include <string>
#include "Value.h"
#include "Types/DT.h"

namespace Backend::CodeGen::IR
{
    class Array : public Value
    {
    public:
        Array(std::string_view id, const DT& type, const size_t numberOfElements);
        ~Array();

        const std::string IR() override;

    private:
        std::string_view m_id;
        DT m_type;
        size_t m_numberOfElements;
    };
}
