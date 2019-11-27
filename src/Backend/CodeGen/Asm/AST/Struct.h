#pragma once

#include "Expression.h"
#include "Decl.h"
#include "Array.h"

namespace Backend::CodeGen::Asm::AST
{
    class Struct : public Expression
    {
    public:
        Struct(std::string id, std::vector<std::unique_ptr<Expression>> body);
        ~Struct();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        std::string m_id;
        std::vector<std::unique_ptr<Expression>> m_body;
    };
}
