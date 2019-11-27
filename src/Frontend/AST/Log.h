#pragma once

#include "Expression.h"
#include "Utility.h"

#include <Backend/CodeGen/IR/Logic/Compare.h>

namespace Frontend::AST
{
    enum class LogType
    {
        Equ,
        Neq
    };

    class Log : public Expression
    {
    public:
        Log(std::unique_ptr<Expression> lhs, syntax_args type, std::unique_ptr<Expression> rhs);
        Log(std::unique_ptr<Expression> lhs, syntax_args type, syntax_args rhs);
        Log(syntax_args lhs, syntax_args type, std::unique_ptr<Expression> rhs);
        Log(syntax_args lhs, syntax_args type, syntax_args rhs);
        ~Log();

        LogType GetType();

        std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

    private:
        syntax_args m_lhs;
        syntax_args m_rhs;
        syntax_args m_type;
        std::unique_ptr<Expression> m_exprLhs;
        std::unique_ptr<Expression> m_exprRhs;
    };
}
