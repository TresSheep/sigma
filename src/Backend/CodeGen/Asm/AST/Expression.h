#pragma once

#include <Backend/CodeGen/Asm/AsmWriter.h>
#include <Backend/CodeGen/Asm/AsmContext.h>
#include <Backend/CodeGen/Asm/Value.h>

#include <string>
#include <memory>

namespace Backend::CodeGen::Asm::AST
{
    typedef std::vector<std::pair<std::string, std::string>> syntax_args;

    class Expression
    {
    public:
        Expression()
        {
        }
        virtual std::unique_ptr<Asm::Value> GenerateCode(Asm::AsmContext& context) = 0;
    };

    typedef std::vector<std::pair<syntax_args, std::unique_ptr<Backend::CodeGen::Asm::AST::Expression>>> node_and_expr_args;
}
