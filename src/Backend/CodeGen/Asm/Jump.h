#pragma once

#include <Backend/OutputFormats/PE/PE.h>
#include <Backend/OutputFormats/PE/Relocation.h>
#include <vector>
#include <memory>
#include <string>
#include <stdint.h>
#include "Value.h"

namespace Backend::CodeGen::Asm
{
    class Jump : public Value
    {
    public:
        Jump(std::string_view name, std::string_view type);
        ~Jump();

        ValueType GetType() override;
        std::string_view GetIdentifier();
        std::unique_ptr<Command::AsmValue> Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition) override;

        void SetPosition(size_t position);

    private:
        std::string m_name;
        std::string m_type;
        std::string m_dText;
        std::vector<uint8_t> m_bytes;
        size_t m_position;
    };
}
