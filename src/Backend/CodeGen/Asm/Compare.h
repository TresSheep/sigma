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
    class Compare : public Value
    {
    public:
        Compare(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs);
        ~Compare();

        ValueType GetType() override;
        std::unique_ptr<Command::AsmValue> Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition) override;

    private:
        std::string m_dText;
        std::vector<uint8_t> m_bytes;

        std::unique_ptr<Value> m_lhs;
        std::unique_ptr<Value> m_rhs;
    };
}
