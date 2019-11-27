#pragma once

#include "Expression.h"
#include "Decl.h"
#include "Array.h"

namespace Backend::CodeGen::Asm::AST
{
    class Union : public Expression
    {
    public:
        Union(std::string id, std::vector<std::unique_ptr<Expression>> body);
        ~Union();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        std::string m_id;
        std::vector<std::unique_ptr<Expression>> m_body;
    };
}
