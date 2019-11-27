#pragma once

#include <string>
#include "Expression.h"
#include <Backend/CodeGen/IR/Structure.h>
#include "ImplFunc.h"

namespace Frontend::AST
{
    class Struct : public Expression
    {
    public:
        Struct(std::string id, std::vector<std::unique_ptr<Expression>> body);
        ~Struct();

        std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

    private:
        std::string m_id;
        std::vector<std::unique_ptr<Expression>> m_body;
    };
}