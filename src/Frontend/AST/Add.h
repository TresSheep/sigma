#pragma once

#include "Expression.h"

#include <Backend/CodeGen/IR/Constant.h>
#include <Backend/CodeGen/IR/Operators/Assign.h>
#include "Utility.h"

namespace Frontend::AST
{
    class Add : public Expression
    {
    public:
        Add(std::unique_ptr<Expression> lhs, syntax_args rhs);
        Add(syntax_args lhs, syntax_args rhs);
        ~Add();

        std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

    private:
        std::unique_ptr<Expression> m_exprLhs;
        syntax_args m_rhs;
        syntax_args m_lhs;
    };
}