#include "Return.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>
#include <stdint.h>

namespace Backend::CodeGen::Asm
{
    Return::Return(std::unique_ptr<Value> val) :
        m_val(std::move(val))
    {
    }

    Return::~Return()
    {
    }

    ValueType Return::GetType()
    {
        return ValueType::RET;
    }

    std::unique_ptr<Command::AsmValue> Return::Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        std::vector<uint8_t> bytes;
        std::string debug;
        std::unique_ptr<Command::AsmValue> b(new Command::AsmValue());

        if (m_val->GetType() == ValueType::VAR)
        {
            auto val = m_val->Asm(writer, textPosition, dataPosition);
            if (val->size >= 8)
            {
                bytes = Command::AsmMov<8>::GetBytes<Reg64::RAX, Reg64::RBP>(val->offset);
                debug = Command::AsmMov<8>::GetDebug();
            }
            else if (val->size <= 4)
            {
                bytes = Command::AsmMov<4>::GetBytes<Reg32::EAX, Reg32::EBP>(val->offset);
                debug = Command::AsmMov<4>::GetDebug();
            }

            b->textBytes = bytes;
            b->textDebug = debug;
        }
        return std::move(b);
    }
}

