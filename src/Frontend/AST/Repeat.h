#pragma once

#include "Expression.h"
#include "If.h"

namespace Frontend::AST
{
    class Repeat : public Expression
    {
    public:
        Repeat(std::unique_ptr<Expression> exprIf);
        ~Repeat();

        std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

    private:
        std::unique_ptr<Expression> m_exprIf;
    };
}
