#pragma once

#include "Expression.h"
#include "../Constant.h"

namespace Backend::CodeGen::Asm::AST
{
    class Negative : public Expression
    {
    public:
        Negative(syntax_args expr);
        Negative(std::string num);
        ~Negative();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        syntax_args m_expr;
        std::string m_num;
    };
}