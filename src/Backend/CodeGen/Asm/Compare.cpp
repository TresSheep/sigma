#include "Compare.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>

namespace Backend::CodeGen::Asm
{
    Compare::Compare(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs) :
        m_lhs(std::move(lhs)), m_rhs(std::move(rhs))
    {
    }

    Compare::~Compare()
    {
    }

    ValueType Compare::GetType()
    {
        return ValueType::CMP;
    }

    std::unique_ptr<Command::AsmValue> Compare::Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        std::vector<uint8_t> bytes;
        std::unique_ptr<Command::AsmValue> b(new Command::AsmValue());

        if (m_lhs->GetType() == ValueType::VAR && m_rhs->GetType() == ValueType::CONST)
        {
            // TODO
            auto lhs = m_lhs->Asm(writer, textPosition, dataPosition);
            auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);
            std::string debug = lhs->textDebug;
            bytes = lhs->textBytes;

            std::vector<uint8_t> vec = Command::AsmMov<8>::GetBytes<Reg64::RAX, Reg64::RBP>(lhs->offset);
            bytes.insert(bytes.end(), vec.begin(), vec.end());

            debug += Command::AsmMov<8>::GetDebug();

            vec = Command::AsmCmp<4>::GetBytes<Reg32::EAX, int32_t>(rhs->offset);
            bytes.insert(bytes.end(), vec.begin(), vec.end());

            debug += Command::AsmCmp<4>::GetDebug();

            b->textBytes = bytes;
            b->textDebug = debug;
        }

        if (m_lhs->GetType() == ValueType::ELEMENT && m_rhs->GetType() == ValueType::CONST)
        {
            auto lhs = m_lhs->Asm(writer, textPosition, dataPosition);
            auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);
            std::string debug = lhs->textDebug;
            bytes = lhs->textBytes;

            std::vector<uint8_t> vec = Command::AsmCmp<8>::GetBytes<Reg64::RAX, Reg64::RBX>(rhs->offset);
            bytes.insert(bytes.end(), vec.begin(), vec.end());

            debug += Command::AsmCmp<8>::GetDebug();

            b->textBytes = bytes;
            b->textDebug = debug;
        }



        return std::move(b);
    }
}

