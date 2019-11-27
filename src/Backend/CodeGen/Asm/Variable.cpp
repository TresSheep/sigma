#include "Variable.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>
#include "Types.h"

namespace Backend::CodeGen::Asm
{
    Variable::Variable(std::string_view identifier, std::string_view type, bool ptr, bool lvalue) :
        m_identifier(identifier), m_offset(0), m_type(type), m_size(0), m_value(""), m_used(false), m_global(false),
        m_reloc(nullptr), m_ptr(ptr), m_lvalue(lvalue)
    {
        if (!type.empty())
            m_size = AsmStringToType(type);
    }

    Variable::~Variable()
    {
    }

    void Variable::SetSize(int32_t size)
    {
        m_size = size;
    }

    std::string_view Variable::ToString()
    {
        return m_dText;
    }
    std::string_view Variable::GetIdentifier()
    {
        return m_identifier;
    }

    void Variable::SetIdentifier(std::string_view identifier)
    {
        m_identifier = identifier;
    }

    void Variable::SetPointer(bool ptr)
    {
        m_ptr = ptr;
    }

    void Variable::SetOffset(int32_t offset)
    {
        m_offset = offset;
    }

    void Variable::SetValue(std::string_view val)
    {
        m_value = val;
    }

    std::string_view Variable::GetValue()
    {
        return m_value;
    }

    bool Variable::HasBeenUsed()
    {
        return m_used;
    }

    ValueType Variable::GetType()
    {
        return ValueType::VAR;
    }

    void Variable::SetType(std::string_view type)
    {
        // Set size
        m_size = AsmStringToType(type);
        m_type = type;
    }

    void Variable::SetGlobal(bool global)
    {
        m_global = global;
    }

    bool Variable::IsGlobal()
    {
        return m_global;
    }

    std::unique_ptr<OutputFormats::PE::Relocation> Variable::GetReloc()
    {
        return std::move(m_reloc);
    }

    std::unique_ptr<Command::AsmValue> Variable::Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        if (m_global)
        {
            //m_reloc = std::make_unique<OutputFormats::PE::Relocation>();
            //m_reloc->SetVirtualAddress(textPosition + 2);
            //m_reloc->SetSymbolTableIndex(pe.GetRelocIndex(".data"));
            //m_reloc->SetType(OutputFormats::PE::ADDR64);

            writer.AddRelocation(textPosition + 2, ".data", ADDR64, TEXT);

            //std::unique_ptr<Command::AsmGlobal> g(new Command::AsmGlobal());
            //return std::move(g);
            return nullptr;
        }

        std::unique_ptr<Command::AsmValue> var(new Command::AsmValue());
        var->reg = (size_t)Reg64::RBP;

        if ((m_offset % 8) != 0) // Was 16
        {
            if (m_size == 8)
            {
                while ((m_offset % 8) != 0)
                {
                    m_offset++;
                }

                var->offset = m_offset;
            }
            else
            {
                var->offset = m_offset;
            }
        }
        else
        {
            var->offset = m_offset;
        }
        var->size = m_size;

        if (m_lvalue)
        {
            var->textDebug = "lval";
        }

        return std::move(var);
    }
}

