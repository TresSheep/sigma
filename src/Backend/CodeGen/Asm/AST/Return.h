#pragma once

#include "Expression.h"
#include "Utility.h"
#include "../Return.h"

namespace Backend::CodeGen::Asm::AST
{
    class Return : public Expression
    {
    public:
        Return(syntax_args arg);
        Return(std::unique_ptr<Expression> arg);
        ~Return();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        syntax_args m_arg;
        std::unique_ptr<Expression> m_exprArg;
    };
}