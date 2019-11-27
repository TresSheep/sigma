#include "Constant.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>

namespace Backend::CodeGen::Asm
{
    Constant::Constant(std::string number, std::string type) :
        m_type(type), m_constant(number)
    {
    }

    Constant::~Constant()
    {
    }

    ValueType Constant::GetType()
    {
        return ValueType::CONST;
    }

    std::unique_ptr<Command::AsmValue> Constant::Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        int64_t byte = std::stoll(m_constant);

        // For now default to int

        std::unique_ptr<Command::AsmValue> bytes(new Command::AsmValue());
        bytes->offset = byte;

        if (m_type.compare("i32") == 0)
            bytes->size = 4;

        //bytes->textBytes.push_back((byte >> 0) & 0xFF);
        //bytes->textBytes.push_back((byte >> 8) & 0xFF);
        //bytes->textBytes.push_back((byte >> 16) & 0xFF);
        //bytes->textBytes.push_back((byte >> 24) & 0xFF);
        bytes->textDebug = std::to_string(byte);
        return std::move(bytes);
    }
}

