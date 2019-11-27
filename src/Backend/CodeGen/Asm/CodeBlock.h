#pragma once

#include <Backend/OutputFormats/PE/PE.h>
#include <Backend/OutputFormats/PE/Relocation.h>
#include <vector>
#include <memory>
#include <stdint.h>
#include "Value.h"

namespace Backend::CodeGen::Asm
{
    class CodeBlock : public Value
    {
    public:
        CodeBlock(std::string_view identifier, std::string_view parent);
        ~CodeBlock();

        ValueType GetType() override;
        std::unique_ptr<Command::AsmValue> Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition) override;
        std::string_view GetIdentifier();

    private:
        std::vector<uint8_t> m_bytes;
        std::string m_identifier;
        std::string m_parent;
    };
}
