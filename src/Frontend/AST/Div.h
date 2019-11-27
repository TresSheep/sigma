#pragma once

#include "Expression.h"
#include "Utility.h"
#include <Backend/CodeGen/IR/Operators/Div.h>

namespace Frontend::AST
{
    class Div : public Expression
    {
    public:
        Div(std::unique_ptr<Expression> lhs, syntax_args rhs);
        Div(syntax_args lhs, syntax_args rhs);
        ~Div();

        std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

    private:
        std::unique_ptr<Expression> m_exprLhs;
        syntax_args m_rhs;
        syntax_args m_lhs;
    };
}