#pragma once

#include "Expression.h"
#include "../CodeBlock.h"
#include "../Move.h"
#include "../Constant.h"
#include "../String.h"
#include "Utility.h"

namespace Backend::CodeGen::Asm::AST
{
    class Move : public Expression
    {
    public:
        Move(syntax_args lhs, syntax_args rhs);
        Move(std::unique_ptr<Expression> lhs, syntax_args rhs);
        Move(syntax_args lhs, std::unique_ptr<Expression> rhs);
        Move(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
        ~Move();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        syntax_args m_lhs;
        syntax_args m_rhs;
        std::unique_ptr<Expression> m_exprLhs;
        std::unique_ptr<Expression> m_exprRhs;
        size_t m_size;
    };
}