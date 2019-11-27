#pragma once

#include "Expression.h"
#include "Prototype.h"
#include <memory>
#include "Call.h"
#include "Block.h"

namespace Backend::CodeGen::Asm::AST
{
    class Function : public Expression
    {
    public:
        Function();
        Function(std::unique_ptr<Prototype> proto, std::vector<std::unique_ptr<Expression>> body);
        ~Function();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        std::unique_ptr<Prototype> m_proto;
        std::vector<std::unique_ptr<Expression>> m_body;
    };
}
