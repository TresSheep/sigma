#include "Array.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>

namespace Backend::CodeGen::Asm
{
    Array::Array(size_t position, size_t size) :
        m_position(position), m_size(size)
    {
    }

    Array::~Array()
    {
    }

    ValueType Array::GetType()
    {
        return ValueType::ARRAY;
    }

    std::unique_ptr<Command::AsmValue> Array::Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        std::vector<uint8_t> bytes;
        std::string debug;
        std::unique_ptr<Command::AsmValue> b(new Command::AsmValue());

        b->offset = m_position;
        b->size = m_size;

        return std::move(b);
    }
}

