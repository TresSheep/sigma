#pragma once

#include "Expression.h"
#include "../String.h"

namespace Backend::CodeGen::Asm::AST
{
    class String : public Expression
    {
    public:
        String(std::string str);
        ~String();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        std::string m_str;
    };
}