#include "CodeBlock.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>
#include <vector>
#include <memory>
#include <string>

namespace Backend::CodeGen::Asm
{
    CodeBlock::CodeBlock(std::string_view identifier, std::string_view parent) :
        m_identifier(identifier), m_parent(parent)
    {
    }

    CodeBlock::~CodeBlock()
    {
    }

    std::string_view CodeBlock::GetIdentifier()
    {
        return m_identifier;
    }

    ValueType CodeBlock::GetType()
    {
        return ValueType::BLOCK;
    }

    std::unique_ptr<Command::AsmValue> CodeBlock::Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        std::unique_ptr<Command::AsmValue> b(new Command::AsmValue());
        b->textDebug += "." + m_identifier + ":\n";

        std::string s = m_parent + "." + m_identifier;

        //std::shared_ptr<OutputFormats::PE::Symbol> symbol(new OutputFormats::PE::Symbol());
        //symbol->SetSectionNumber(2);
        //symbol->SetStorageClass((uint16_t)OutputFormats::PE::ImageSymbolClass::STATIC);
        //symbol->SetSymbolName(s.c_str());
        //symbol->SetSymbolValue(textPosition);

        //pe.AddSymbol(symbol);

        writer.AddSymbol(s.c_str(), textPosition, TEXT);

        return std::move(b);
    }
}

