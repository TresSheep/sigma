#pragma once

#include <Backend/OutputFormats/PE/PE.h>
#include <Backend/OutputFormats/PE/Relocation.h>
#include <vector>
#include <memory>
#include <string>
#include <stdint.h>
#include "Value.h"
#include "Variable.h"

namespace Backend::CodeGen::Asm
{
    class String : public Value
    {
    public:
        String(std::string_view str);
        ~String();

        ValueType GetType() override;
        std::unique_ptr<Command::AsmValue> Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition) override;

    private:
        std::string m_str;
    };
}
