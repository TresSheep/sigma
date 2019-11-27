#pragma once

#include "Expression.h"

namespace Backend::CodeGen::Asm::AST
{
    class Number : public Expression
    {
    public:
        Number(std::string number);
        ~Number();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        std::string m_number;
    };
}