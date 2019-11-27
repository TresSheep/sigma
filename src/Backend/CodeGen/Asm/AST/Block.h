#pragma once

#include "Expression.h"
#include "../CodeBlock.h"

namespace Backend::CodeGen::Asm::AST
{
    class Block : public Expression
    {
    public:
        Block(std::string name);
        ~Block();

        void SetParent(std::string parent);

        std::string GetName();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        std::string m_name;
        std::string m_parent;
    };
}