#pragma once

#include "Value.h"

namespace Backend::CodeGen::Asm
{
    class Array : public Value
    {
    public:
        Array(size_t position, size_t size);
        ~Array();

        ValueType GetType() override;
        std::unique_ptr<Command::AsmValue> Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition) override;

    private:
        size_t m_position;
        size_t m_size;
    };
}
