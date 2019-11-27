#pragma once

#include "Expression.h"
#include "../AsmWriter.h"
#include "../Variable.h"

namespace Backend::CodeGen::Asm::AST
{
    class Variable : public Expression
    {
    public:
        Variable(std::string id, std::string type, bool ptr, bool lval);
        virtual ~Variable();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

        void SetOfffset(size_t offset);

    private:
        std::string m_id;
        std::string m_type;
        bool m_ptr;
        size_t m_offset;
        bool m_lval;
    };
}
