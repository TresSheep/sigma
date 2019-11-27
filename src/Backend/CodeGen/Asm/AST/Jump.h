#pragma once

#include "Expression.h"
#include "../AsmWriter.h"

#include "../Jump.h"

namespace Backend::CodeGen::Asm::AST
{
    class Jump : public Expression
    {
    public:
        Jump(std::string type, std::string name);
        ~Jump();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        std::string m_type;
        std::string m_name;
    };
}
