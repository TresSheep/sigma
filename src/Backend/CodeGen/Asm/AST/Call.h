#pragma once

#include "Expression.h"
#include <string>
#include "Utility.h"

namespace Backend::CodeGen::Asm::AST
{
    class Call : public Expression
    {
    public:
        Call(std::string identifier, std::string type, node_and_expr_args args);
        ~Call();

        void SetCallee(std::string name);
        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        std::string m_identifier;
        node_and_expr_args m_args;
        std::string m_callee;
    };
}
