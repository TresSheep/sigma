#pragma once

#include "Expression.h"
#include "Utility.h"
#include <Backend/CodeGen/IR/Operators/Div.h>

namespace Frontend::AST
{
    class Modulo : public Expression
    {
    public:
        Modulo(std::unique_ptr<Expression> lhs, syntax_args rhs);
        Modulo(syntax_args lhs, syntax_args rhs);
        ~Modulo();

        std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

    private:
        std::unique_ptr<Expression> m_exprLhs;
        syntax_args m_rhs;
        syntax_args m_lhs;
    };
}