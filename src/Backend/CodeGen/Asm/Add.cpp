#include "Add.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>

namespace Backend::CodeGen::Asm
{
    Add::Add(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs) :
        m_lhs(std::move(lhs)), m_rhs(std::move(rhs))
    {
    }
    
    Add::~Add()
    {
    }

    ValueType Add::GetType()
    {
        return ValueType::ADD;
    }

    std::unique_ptr<Command::AsmValue> Add::Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        std::vector<uint8_t> bytes;
        std::string debug;
        std::unique_ptr<Command::AsmValue> b(new Command::AsmValue());

        if (m_lhs->GetType() == ValueType::VAR && m_rhs->GetType() == ValueType::CONST)
        {
            auto lhs = m_lhs->Asm(writer, textPosition, dataPosition);
            auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);

            if (lhs->size == 4)
            {
                bytes = Command::AsmMov<4>::GetBytes<Reg32::EAX, Reg32::EBP>(lhs->offset);
                debug = Command::AsmMov<4>::GetDebug();

                std::vector<uint8_t> vec = Command::AsmAdd<Reg32>::GetBytes<Reg32::EAX>(rhs->offset);
                debug += Command::AsmAdd<Reg32>::GetDebug();
                bytes.insert(bytes.end(), vec.begin(), vec.end());

                vec = Command::AsmMov<4>::GetBytes<Reg32::EBP, Reg32::EAX, true>(lhs->offset);
                debug += Command::AsmMov<4>::GetDebug();
                bytes.insert(bytes.end(), vec.begin(), vec.end());
            }

            b->textBytes = bytes;
            b->textDebug = debug;
        }

        return std::move(b);
    }
}