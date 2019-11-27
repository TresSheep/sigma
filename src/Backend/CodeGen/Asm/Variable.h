#pragma once

#include "Variable.h"
#include <Backend/OutputFormats/PE/PE.h>
#include <Backend/OutputFormats/PE/Relocation.h>
#include <vector>
#include <memory>
#include <string>
#include "Value.h"

namespace Backend::CodeGen::Asm
{
    class Variable : public Value
    {
    public:
        Variable(std::string_view identifier, std::string_view type, bool ptr = false, bool lvalue = false);
        ~Variable();

        void SetSize(int32_t size);
        void SetIdentifier(std::string_view identifier);
        void SetPointer(bool ptr);

        void SetOffset(int32_t offset);
        std::string_view ToString();
        void SetValue(std::string_view val);
        std::unique_ptr<Command::AsmValue> Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition) override;
        std::string_view GetIdentifier();
        int32_t GetOffset()
        {
            return m_offset;
        }
        void SetSize(size_t size)
        {
            m_size = size;
        }
        int32_t GetSize()
        {
            return m_size;
        }
        std::string_view GetValue();
        ValueType GetType() override;
        void SetType(std::string_view type);

        bool HasBeenUsed();

        void SetGlobal(bool global);
        bool IsGlobal();

        void SetOffset(size_t offset)
        {
            m_offset += offset;
        }

        std::unique_ptr<OutputFormats::PE::Relocation> GetReloc();

    private:
        std::string m_dText;
        std::vector<uint8_t> m_bytes;
        int32_t m_offset;
        std::string m_identifier;
        std::string m_type;
        bool m_decl;
        size_t m_size;
        std::string m_value;
        bool m_used;
        bool m_global;
        std::unique_ptr<OutputFormats::PE::Relocation> m_reloc;
        bool m_ptr;
        bool m_lvalue;
    };
}
