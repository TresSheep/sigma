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
    class Element : public Value
    {
    public:
        Element(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs, bool strct = false);
        ~Element();

        ValueType GetType() override;
        std::unique_ptr<Command::AsmValue> Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition) override;

    private:
        std::unique_ptr<Value> m_lhs;
        std::unique_ptr<Value> m_rhs;
        bool m_strct;
    };
}
