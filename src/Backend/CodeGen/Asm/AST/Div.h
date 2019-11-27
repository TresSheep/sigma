#pragma once

#include "Expression.h"
#include "Utility.h"
#include "../Div.h"

namespace Backend::CodeGen::Asm::AST
{
    class Div : public Expression
    {
    public:
        Div(syntax_args lhs, syntax_args rhs);
        Div(syntax_args lhs, std::unique_ptr<Expression> rhs);
        ~Div();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        syntax_args m_lhs;
        syntax_args m_rhs;
        std::unique_ptr<Expression> m_exprRhs;
    };
}