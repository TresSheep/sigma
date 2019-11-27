#pragma once

#include "Variable.h"
#include <Backend/OutputFormats/PE/PE.h>
#include <Backend/OutputFormats/PE/Relocation.h>
#include <vector>
#include <memory>
#include "Value.h"
#include "CodeBlock.h"
#include "Jump.h"
#include "AsmWriter.h"
#include "Registers.h"
#include "Types.h"

namespace Backend::CodeGen::Asm
{
    class Function
    {
    public:
        Function(std::string_view identifier);
        ~Function();

        void AddVariableTable(std::vector<std::shared_ptr<Variable>> vars);
        void SetPosition(uint32_t pos);

        std::string_view AsmToStringText();
        std::string_view AsmToStringData();
        std::string_view AsmToStringGlobal();
        std::unique_ptr<Command::AsmValue> Asm(AsmWriter& asmWriter);
        std::vector<uint8_t> GetDataBytes();
        std::vector<std::unique_ptr<OutputFormats::PE::Relocation>> GetRelocs();

        void SetArgs(std::vector<std::shared_ptr<Variable>> args);

        std::vector<std::unique_ptr<Value>> Body;

        std::string_view GetIdentifier();
        size_t GetOffset()
        {
            return m_offset;
        }

        void SetExternal(bool extrn);
        bool IsExternal();
        void SetForward(bool forward)
        {
            m_forward = forward;
        }
        bool IsForward()
        {
            return m_forward;
        }

        void SetVariableSize(size_t size);

    private:
        std::vector<std::shared_ptr<Variable>> m_variableTable;
        size_t m_position;
        std::vector<std::unique_ptr<OutputFormats::PE::Relocation>> m_relocs;
        std::string m_identifier;
        bool m_extrn;
        bool m_forward;
        std::vector<CodeBlock> m_blocks;
        std::vector<std::shared_ptr<Variable>> m_args;
        std::vector<std::pair<std::string, size_t>> m_labels;
        size_t m_size;
        size_t m_offset;
    };
}
