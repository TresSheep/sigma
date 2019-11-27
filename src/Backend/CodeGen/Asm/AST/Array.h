#pragma once

#include "Expression.h"
#include "../AsmWriter.h"
#include "../Array.h"

namespace Backend::CodeGen::Asm::AST
{
    class Array : public Expression
    {
    public:
        Array(const std::string& type, const std::string& id, const std::string& size);
        ~Array();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        std::string m_type;
        std::string m_id;
        std::string m_size;
    };
}