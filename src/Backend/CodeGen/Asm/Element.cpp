#include "Element.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>

namespace Backend::CodeGen::Asm
{
    Element::Element(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs, bool strct) :
        m_lhs(std::move(lhs)), m_rhs(std::move(rhs)), m_strct(strct)
    {
    }

    Element::~Element()
    {
    }

    ValueType Element::GetType()
    {
        return ValueType::ELEMENT;
    }

    std::unique_ptr<Command::AsmValue> Element::Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        // Set size to type

        std::vector<uint8_t> bytes;
        std::vector<uint8_t> dataBytes;
        std::unique_ptr<Command::AsmValue> b(new Command::AsmValue());

        auto lhs = m_lhs->Asm(writer, textPosition, dataPosition);
        auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);
        std::string debug;

        if (m_lhs->GetType() == ValueType::VAR && m_rhs->GetType() == ValueType::VAR)
        {
            if (lhs->size == 4)
            {
                bytes = Command::AsmMov<4>::GetBytes<Reg32::EAX, Reg32::EBP>(lhs->offset);
                debug += Command::AsmMov<4>::GetDebug();
            }
            else if (lhs->size == 8)
            {
                bytes = Command::AsmMov<8>::GetBytes<Reg64::RAX, Reg64::RBP>(lhs->offset);
                debug += Command::AsmMov<8>::GetDebug();
            }

            if (rhs->size == 4)
            {
                std::vector<uint8_t> vec = Command::AsmMov<4>::GetBytes<Reg32::EBX, Reg32::EBP>(rhs->offset);
                debug += Command::AsmMov<4>::GetDebug();
                bytes.insert(bytes.end(), vec.begin(), vec.end());
            }
            else if (rhs->size == 8)
            {
                std::vector<uint8_t> vec = Command::AsmMov<8>::GetBytes<Reg64::RBX, Reg64::RBP>(rhs->offset);
                debug += Command::AsmMov<8>::GetDebug();
                bytes.insert(bytes.end(), vec.begin(), vec.end());
            }
        }
        else if (m_lhs->GetType() == ValueType::VAR && m_rhs->GetType() == ValueType::CONST)
        {
            if (m_strct)
            {
                if (lhs->size <= 4)
                {
                    bytes = Command::AsmMov<4>::GetBytes<Reg32::ESI, Reg32::EBP, false>(lhs->offset);
                    debug += Command::AsmMov<4>::GetDebug();

                    //std::vector<uint8_t> vec = Command::AsmMov<4>::GetBytes<Reg32::EAX, Reg32::EDI>(-rhs->offset);
                    //debug += Command::AsmMov<4>::GetDebug();
                    //bytes.insert(bytes.end(), vec.begin(), vec.end());
                }
                else if (lhs->size >= 8)
                {
                    bytes = Command::AsmMov<8>::GetBytes<Reg64::RSI, Reg64::RBP, false>(lhs->offset);
                    debug += Command::AsmMov<8>::GetDebug();
                    b->offset = rhs->offset;
                    lhs->size = rhs->size;

                    //std::vector<uint8_t> vec = Command::AsmMov<8>::GetBytes<Reg64::RAX, Reg64::RDI>(-rhs->offset);
                    //debug += Command::AsmMov<8>::GetDebug();
                    //bytes.insert(bytes.end(), vec.begin(), vec.end());
                }
            }
            else
            {
                if (lhs->size <= 4)
                {
                    bytes = Command::AsmMov<4>::GetBytes<Reg32::EAX, Reg32::EBP>(lhs->offset);
                    debug += Command::AsmMov<4>::GetDebug();
                }
                else if (lhs->size >= 8)
                {
                    bytes = Command::AsmMov<8>::GetBytes<Reg64::RAX, Reg64::RBP>(lhs->offset);
                    debug += Command::AsmMov<8>::GetDebug();
                }
            }
        }
        else if (m_lhs->GetType() == ValueType::ARRAY && m_rhs->GetType() == ValueType::CONST)
        {
            if (lhs->size <= 4)
            {
                bytes = Command::AsmMov<4>::GetBytes<Reg32::EAX, Reg32::EBP>(lhs->offset - (rhs->offset * lhs->size));
                debug += Command::AsmMov<4>::GetDebug();
            }
            else if (lhs->size >= 8)
            {
                bytes = Command::AsmMov<8>::GetBytes<Reg64::RAX, Reg64::RBP>(lhs->offset);
                debug += Command::AsmMov<8>::GetDebug();
            }

            b->offset = lhs->offset - (rhs->offset * lhs->size);

            // move back
        }

        b->size = lhs->size;
        b->textBytes = bytes;
        b->textDebug = debug;

        return std::move(b);
    }
}
