#pragma once

#include "Expression.h"
#include "Utility.h"
#include "../Add.h"

namespace Backend::CodeGen::Asm::AST
{
    class Add : public Expression
    {
    public:
        Add(syntax_args lhs, syntax_args rhs);
        Add(syntax_args lhs, std::unique_ptr<Expression> rhs);
        ~Add();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        syntax_args m_lhs;
        syntax_args m_rhs;
        std::unique_ptr<Expression> m_exprRhs;
    };
}