#include "Jump.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>

namespace Backend::CodeGen::Asm
{
    Jump::Jump(std::string_view name, std::string_view type) :
        m_name(name), m_type(type), m_position(0)
    {
    }

    Jump::~Jump()
    {
    }

    ValueType Jump::GetType()
    {
        return ValueType::JMP;
    }

    std::string_view Jump::GetIdentifier()
    {
        return m_name;
    }

    std::unique_ptr<Command::AsmValue> Jump::Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        std::unique_ptr<Command::AsmValue> b(new Command::AsmValue());
        if (m_type.compare("jmp") == 0)
        {
            std::vector<uint8_t> bytes;
            std::string debug;
            bytes = Command::jmp(m_name, m_position - 2, debug);

            b->textBytes = bytes;
            b->textDebug = debug;
        }
        else if (m_type.compare("je") == 0)
        {
            std::vector<uint8_t> bytes;
            std::string debug;
            bytes = Command::je(m_name, m_position - 2, debug);

            b->textBytes = bytes;
            b->textDebug = debug;
        }
        else if (m_type.compare("jne") == 0)
        {
            std::vector<uint8_t> bytes;
            std::string debug;
            bytes = Command::jne(m_name, m_position - 2, debug);

            b->textBytes = bytes;
            b->textDebug = debug;
        }
    	return std::move(b);
    }

    void Jump::SetPosition(size_t position)
    {
        m_position = position;
    }
}
