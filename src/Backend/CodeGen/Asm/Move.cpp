#include "Move.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>
#include <vector>
#include <memory>
#include <string>
#include <stdint.h>
#include "Registers.h"

namespace Backend::CodeGen::Asm
{
    Move::Move(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs, size_t size) :
        m_lhs(std::move(lhs)), m_rhs(std::move(rhs)), m_size(size)
    {
    }

    Move::~Move()
    {
    }

    ValueType Move::GetType()
    {
        return ValueType::MOV;
    }

    std::unique_ptr<Command::AsmValue> Move::Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        std::vector<uint8_t> bytes;
        std::vector<uint8_t> dataBytes;
        std::unique_ptr<Command::AsmValue> b(new Command::AsmValue());

        auto lhs = m_lhs->Asm(writer, textPosition, dataPosition);

        switch (lhs->size)
        {
        case 1:
        {
            // BYTE
            return std::move(ParseBYTE(std::move(lhs), writer, textPosition, dataPosition));
        } break;
        case 2:
        {
            // WORD
            return std::move(ParseWORD(std::move(lhs), writer, textPosition, dataPosition));
        } break;
        case 4:
        {
            // DWORD
            return std::move(ParseDWORD(std::move(lhs), writer, textPosition, dataPosition));
        } break;
        case 8:
        {
            // QWORD
            return std::move(ParseQWORD(std::move(lhs), writer, textPosition, dataPosition));
        } break;
        }

        return nullptr;
    }

    size_t Move::GetSize()
    {
        return m_size;
    }

    std::unique_ptr<Command::AsmValue> Move::ParseBYTE(std::unique_ptr<Command::AsmValue> lhs, AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        std::vector<uint8_t> bytes;
        std::vector<uint8_t> dataBytes;
        std::string textDebug;
        std::string dataDebug;
        std::unique_ptr<Command::AsmValue> b(new Command::AsmValue());

        if (m_lhs->GetType() == ValueType::ELEMENT && m_rhs->GetType() == ValueType::CONST)
        {
            // element is in rax

            textDebug = lhs->textDebug;
        }

        b->textBytes = bytes;
        b->dataBytes = dataBytes;
        b->textDebug = textDebug;
        b->dataDebug = dataDebug;
        return std::move(b);
    }

    std::unique_ptr<Command::AsmValue> Move::ParseWORD(std::unique_ptr<Command::AsmValue> lhs, AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        std::vector<uint8_t> bytes;
        std::vector<uint8_t> dataBytes;
        std::string textDebug;
        std::string dataDebug;
        std::unique_ptr<Command::AsmValue> b(new Command::AsmValue());

        if (m_lhs->GetType() == ValueType::VAR && m_rhs->GetType() == ValueType::CONST)
        {
            auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);
            if (lhs->size == 2)
            {
                if (lhs->offset != -1)
                {
                    bytes = Command::AsmMov<4>::GetBytes((Reg32)lhs->reg, rhs->size, lhs->offset);

                }
                else
                {
                    bytes = Command::AsmMov<4>::GetBytes((Reg32)lhs->reg, rhs->size);
                }
                textDebug = Command::AsmMov<4>::GetDebug();
            }
        }

        b->textBytes = bytes;
        b->dataBytes = dataBytes;
        b->textDebug = textDebug;
        b->dataDebug = dataDebug;
        return std::move(b);
    }

    std::unique_ptr<Command::AsmValue> Move::ParseDWORD(std::unique_ptr<Command::AsmValue> lhs, AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        std::vector<uint8_t> bytes;
        std::vector<uint8_t> dataBytes;
        std::string textDebug;
        std::string dataDebug;
        std::unique_ptr<Command::AsmValue> b(new Command::AsmValue());

        if (m_lhs->GetType() == ValueType::ELEMENT && m_rhs->GetType() == ValueType::CONST)
        {
            // element is in rsi + offset

            bytes = lhs->textBytes;
            textDebug = lhs->textDebug;

            auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);

            std::vector<uint8_t> vec = Command::AsmMov<4>::GetBytes<Reg32::ESI>(rhs->offset, -lhs->offset);
            textDebug += Command::AsmMov<4>::GetDebug();
            bytes.insert(bytes.end(), vec.begin(), vec.end());
        }
        else if (m_lhs->GetType() == ValueType::VAR && m_rhs->GetType() == ValueType::CONST)
        {
            auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);
            if (lhs->size == 4)
            {
                if (lhs->offset != -1)
                {
                    bytes = Command::AsmMov<4>::GetBytes((Reg32)lhs->reg, rhs->offset, lhs->offset);
                }
                else
                {
                    bytes = Command::AsmMov<4>::GetBytes((Reg32)lhs->reg, rhs->offset);
                }
                textDebug = Command::AsmMov<4>::GetDebug();
            }
        }
        else if (m_lhs->GetType() == ValueType::VAR && m_rhs->GetType() == ValueType::CALL)
        {
            auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);
            textDebug = rhs->textDebug;
            bytes = rhs->textBytes;

            std::vector<uint8_t> vec = Command::AsmMov<4>::GetBytes<Reg32::EBP, Reg32::EAX, true>(lhs->offset);
            textDebug += Command::AsmMov<4>::GetDebug();
            bytes.insert(bytes.end(), vec.begin(), vec.end());
        }
        else if (m_lhs->GetType() == ValueType::VAR && m_rhs->GetType() == ValueType::ELEMENT)
        {
            auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);
            textDebug = rhs->textDebug;
            bytes = rhs->textBytes;

            std::vector<uint8_t> vec = Command::AsmMov<4>::GetBytes<Reg32::EBP, Reg32::EAX, true>(lhs->offset);
            textDebug += Command::AsmMov<4>::GetDebug();
            bytes.insert(bytes.end(), vec.begin(), vec.end());
        }
        else if (m_lhs->GetType() == ValueType::ELEMENT && m_rhs->GetType() == ValueType::VAR)
        {
            // element is in rsi + offset

            bytes = lhs->textBytes;
            textDebug = lhs->textDebug;

            auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);

            std::vector<uint8_t> vec = Command::AsmMov<4>::GetBytes<Reg32::EAX, Reg32::EBP>(rhs->offset);
            textDebug += Command::AsmMov<4>::GetDebug();
            bytes.insert(bytes.end(), vec.begin(), vec.end());
            
            vec = Command::AsmMov<4>::GetBytes<Reg32::ESI, Reg32::EAX, true>(-lhs->offset);
            textDebug += Command::AsmMov<4>::GetDebug();
            bytes.insert(bytes.end(), vec.begin(), vec.end());
        }
        else if (m_lhs->GetType() == ValueType::VAR && m_rhs->GetType() == ValueType::DIV)
        {
            auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);
            textDebug = rhs->textDebug;
            bytes = rhs->textBytes;
        }

        else if (m_lhs->GetType() == ValueType::VAR && m_rhs->GetType() == ValueType::ADD)
        {
            auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);
            textDebug = rhs->textDebug;
            bytes = rhs->textBytes;
        }

        //else if (m_lhs->GetType() == ValueType::ELEMENT && m_rhs->GetType() == ValueType::CONST)
        //{
        //    auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);

        //    textDebug += lhs->textDebug;
        //    bytes = lhs->textBytes;

        //    std::vector<uint8_t> vec = Command::AsmMov<4>::GetBytes<Reg32::EDI>(rhs->offset, -lhs->offset);
        //    bytes.insert(bytes.end(), vec.begin(), vec.end());
        //    textDebug += Command::AsmMov<4>::GetDebug();
        //}

        b->textBytes = bytes;
        b->dataBytes = dataBytes;
        b->textDebug = textDebug;
        b->dataDebug = dataDebug;
        return std::move(b);
    }

    std::unique_ptr<Command::AsmValue> Move::ParseQWORD(std::unique_ptr<Command::AsmValue> lhs, AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        std::vector<uint8_t> bytes;
        std::vector<uint8_t> dataBytes;
        std::string textDebug;
        std::string dataDebug;
        std::unique_ptr<Command::AsmValue> b(new Command::AsmValue());

        if (m_lhs->GetType() == ValueType::VAR && m_rhs->GetType() == ValueType::STR)
        {
            auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);
            dataDebug = rhs->dataDebug;
            dataBytes = rhs->dataBytes;

            bytes = Command::AsmMov<8>::GetBytes<Reg64::RAX>(rhs->textDebug, rhs->offset);
            textDebug += Command::AsmMov<8>::GetDebug();
            textDebug.pop_back(); // \n
            textDebug.pop_back(); // 0
            textDebug.pop_back();
            textDebug.pop_back();
            textDebug.pop_back();
            textDebug += rhs->textDebug;
            textDebug += "\n";

            std::vector<uint8_t> vec = Command::AsmMov<8>::GetBytes<Reg64::RBP, Reg64::RAX, true>(lhs->offset);
            bytes.insert(bytes.end(), vec.begin(), vec.end());
            textDebug += Command::AsmMov<8>::GetDebug();

            writer.AddRelocation(textPosition + 2, ".data", ADDR64, TEXT);
        }
        else if (m_lhs->GetType() == ValueType::VAR && m_rhs->GetType() == ValueType::CALL)
        {
            auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);
            textDebug = rhs->textDebug;
            bytes = rhs->textBytes;

            dataBytes = rhs->dataBytes;
            dataDebug = rhs->dataDebug;

            std::vector<uint8_t> vec = Command::AsmMov<8>::GetBytes<Reg64::RBP, Reg64::RAX, true>(lhs->offset);
            bytes.insert(bytes.end(), vec.begin(), vec.end());
            textDebug += Command::AsmMov<8>::GetDebug();
        }
        else if (m_lhs->GetType() == ValueType::ELEMENT && m_rhs->GetType() == ValueType::CONST)
        {
            auto rhs = m_rhs->Asm(writer, textPosition, dataPosition);

            textDebug += lhs->textDebug;
            bytes = lhs->textBytes;

            std::vector<uint8_t> vec = Command::AsmMov<8>::GetBytes<Reg64::RDI>(rhs->offset, -lhs->offset);
            bytes.insert(bytes.end(), vec.begin(), vec.end());
            textDebug += Command::AsmMov<8>::GetDebug();
        }

        b->textBytes = bytes;
        b->dataBytes = dataBytes;
        b->textDebug = textDebug;
        b->dataDebug = dataDebug;
        return std::move(b);
    }
}

