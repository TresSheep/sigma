#pragma once

#include "Expression.h"
#include "../CodeBlock.h"
#include "Utility.h"
#include "../Element.h"

namespace Backend::CodeGen::Asm::AST
{
    class Element : public Expression
    {
    public:
        Element(std::vector<std::pair<std::string, std::string>> lhs, std::vector<std::pair<std::string, std::string>> rhs);
        ~Element();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        std::vector<std::pair<std::string, std::string>> m_lhs;
        std::vector<std::pair<std::string, std::string>> m_rhs;
    };
}