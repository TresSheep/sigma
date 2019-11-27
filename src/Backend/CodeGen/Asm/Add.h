#pragma once

#include <vector>
#include <memory>
#include <stdint.h>
#include "Value.h"
#include "Constant.h"

namespace Backend::CodeGen::Asm
{
    class Add : public Value
    {
    public:
        Add(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs);
        ~Add();

        ValueType GetType() override;
        std::unique_ptr<Command::AsmValue> Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition) override;

    private:
        std::unique_ptr<Value> m_lhs;
        std::unique_ptr<Value> m_rhs;
    };
}
