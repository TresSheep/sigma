#pragma once

#include "../AsmWriter.h"
#include "../AsmContext.h"
#include "../Function.h"
#include "Utility.h"

namespace Backend::CodeGen::Asm::AST
{
    class Prototype
    {
    public:
        Prototype(std::string identifier, syntax_args args, std::string type);
        ~Prototype();

        std::string GetIdentifier();

        std::unique_ptr<Asm::Function> GenerateCode(Asm::AsmContext& context);

    private:
        std::string m_identifier;
        syntax_args m_args;
    };
}
