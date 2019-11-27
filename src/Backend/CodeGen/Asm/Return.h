#pragma once

#include "Variable.h"
#include <Backend/OutputFormats/PE/PE.h>
#include <Backend/OutputFormats/PE/Relocation.h>
#include <vector>
#include <memory>
#include <stdint.h>
#include "Value.h"

namespace Backend::CodeGen::Asm
{
    class Return : public Value
    {
    public:
        Return(std::unique_ptr<Value> val);
        ~Return();

        ValueType GetType() override;
        std::unique_ptr<Command::AsmValue> Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition) override;

    private:
        std::string m_dText;
        std::vector<uint8_t> m_bytes;
        std::unique_ptr<Value> m_val;
    };
}
