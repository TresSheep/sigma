#pragma once

#include "Expression.h"
#include "Prototype.h"

namespace Backend::CodeGen::Asm::AST
{
    class ForwardFunction : public Expression
    {
    public:
        ForwardFunction(std::unique_ptr<Prototype> proto);
        ~ForwardFunction();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        std::unique_ptr<Prototype> m_proto;
    };
}