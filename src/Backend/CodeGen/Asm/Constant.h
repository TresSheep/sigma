#pragma once

#include <Backend/OutputFormats/PE/PE.h>
#include <Backend/OutputFormats/PE/Relocation.h>
#include <vector>
#include <memory>
#include <stdint.h>
#include "Value.h"

namespace Backend::CodeGen::Asm
{
    class Constant : public Value
    {
    public:
        Constant(std::string number, std::string type);
        ~Constant();

        ValueType GetType() override;
        std::unique_ptr<Command::AsmValue> Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition) override;

    private:
        std::string m_dText;
        std::vector<uint8_t> m_bytes;
        std::string m_type;
        std::string m_constant;
    };
}
