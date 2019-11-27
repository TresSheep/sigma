#pragma once

#include "Expression.h"
#include "../AsmWriter.h"
#include "../Compare.h"
#include "../Constant.h"
#include "Utility.h"

namespace Backend::CodeGen::Asm::AST
{
    class Compare : public Expression
    {
    public:
        Compare(syntax_args lhs, syntax_args rhs);
        Compare(std::unique_ptr<Expression> lhs, syntax_args rhs);
        ~Compare();

        std::unique_ptr<Value> CheckLHS(std::shared_ptr<Asm::AsmContext> context);
        std::unique_ptr<Value> CheckRHS(Asm::AsmContext& context);

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        syntax_args m_lhs;
        syntax_args m_rhs;
        std::unique_ptr<Expression> m_exprLhs;
    };
}
