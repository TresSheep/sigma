#pragma once

#include "Value.h"

namespace Backend::CodeGen::Asm
{
    class Div : public Value
    {
    public:
        Div(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs, bool modulo = false);
        ~Div();

        ValueType GetType() override;
        std::unique_ptr<Command::AsmValue> Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition) override;

    private:
        std::unique_ptr<Value> m_lhs;
        std::unique_ptr<Value> m_rhs;
        bool m_modulo;
    };
}
