#include "Div.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>

namespace Backend::CodeGen::Asm
{
    Div::Div(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs, bool modulo) :
        m_lhs(std::move(lhs)), m_rhs(std::move(rhs)), m_modulo(modulo)
    {
    }

    Div::~Div()
    {
    }

    ValueType Div::GetType()
    {
        return ValueType::DIV;
    }

    std::unique_ptr<Command::AsmValue> Div::Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition)
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
                bytes = Command::AsmMov<4>::GetBytes<Reg32::EDX>(0);
                debug = Command::AsmMov<4>::GetDebug();

                std::vector<uint8_t> vec = Command::AsmMov<4>::GetBytes<Reg32::EAX, Reg32::EBP>(lhs->offset);
                debug += Command::AsmMov<4>::GetDebug();
                bytes.insert(bytes.end(), vec.begin(), vec.end());

                vec = Command::AsmMov<4>::GetBytes<Reg32::EBX>(rhs->offset);
                debug += Command::AsmMov<4>::GetDebug();
                bytes.insert(bytes.end(), vec.begin(), vec.end());

                vec = Command::AsmDiv<4>::GetBytes<Reg32::EBX>();
                debug += Command::AsmDiv<4>::GetDebug();
                bytes.insert(bytes.end(), vec.begin(), vec.end());

                if (m_modulo)
                {
                    // Move edx to eax

                    std::vector<uint8_t> vec = Command::AsmMov<4>::GetBytes<Reg32::EAX, Reg32::EBX, true>();
                    debug += Command::AsmMov<4>::GetDebug();
                    bytes.insert(bytes.end(), vec.begin(), vec.end());
                }
            }

            b->textBytes = bytes;
            b->textDebug = debug;
        }

        return std::move(b);
    }
}

