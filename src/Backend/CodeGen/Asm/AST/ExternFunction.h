#pragma once

#include "Expression.h"
#include "Prototype.h"
#include <memory>
#include "Call.h"

namespace Backend::CodeGen::Asm::AST
{
    class ExternFunction : public Expression
    {
    public:
        ExternFunction(std::unique_ptr<Prototype> proto);
        ~ExternFunction();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        std::unique_ptr<Prototype> m_proto;
    };
}