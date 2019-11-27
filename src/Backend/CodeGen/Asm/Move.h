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
    class Move : public Value
    {
    public:
        Move(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs, size_t size);
        ~Move();

        ValueType GetType() override;
        std::unique_ptr<Command::AsmValue> Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition) override;

        size_t GetSize();

    private:
        std::unique_ptr<Command::AsmValue> ParseBYTE(std::unique_ptr<Command::AsmValue> lhs, AsmWriter& writer, size_t textPosition, size_t dataPosition);
        std::unique_ptr<Command::AsmValue> ParseWORD(std::unique_ptr<Command::AsmValue> lhs, AsmWriter& writer, size_t textPosition, size_t dataPosition);
        std::unique_ptr<Command::AsmValue> ParseDWORD(std::unique_ptr<Command::AsmValue> lhs, AsmWriter& writer, size_t textPosition, size_t dataPosition);
        std::unique_ptr<Command::AsmValue> ParseQWORD(std::unique_ptr<Command::AsmValue> lhs, AsmWriter& writer, size_t textPosition, size_t dataPosition);
        std::string m_dText;
        std::vector<uint8_t> m_bytes;

        std::unique_ptr<Value> m_lhs;
        std::unique_ptr<Value> m_rhs;
        size_t m_size;
    };
}
