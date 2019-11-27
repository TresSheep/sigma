#pragma once

#include <vector>
#include <memory>
#include <stdint.h>
#include "Value.h"
#include "Constant.h"

namespace Backend::CodeGen::Asm
{
    class Call : public Value
    {
    public:
        Call(std::string_view identifier, std::vector<std::unique_ptr<Value>> args, bool extrn, bool forward, size_t offset);
        ~Call();

        ValueType GetType() override;
        std::unique_ptr<Command::AsmValue> Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition) override;
        std::string_view GetIdentifier();

    private:
        std::string m_dText;
        std::vector<uint8_t> m_bytes;
        std::string m_identifier;
        std::vector<std::unique_ptr<Value>> m_args;
        bool m_extrn;
        bool m_forward;
        size_t m_offset;
    };
}
