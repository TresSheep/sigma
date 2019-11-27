#pragma once

#include "Expression.h"
#include "../AsmWriter.h"

namespace Backend::CodeGen::Asm::AST
{
    class Decl : public Expression
    {
    public:
        Decl(std::string id, std::string type, std::string ptr);
        virtual ~Decl();

        std::unique_ptr<Backend::CodeGen::Asm::Value> GenerateCode(Asm::AsmContext& context) override;

    private:
        std::string m_id;
        std::string m_type;
        bool m_ptr;
    };
}
