#pragma once

#include <string>
#include "Expression.h"

namespace Frontend::AST
{
    class Union : public Expression
    {
    public:
        Union(std::string id, std::vector<std::unique_ptr<Expression>> body);
        ~Union();

        std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

    private:
        std::string m_id;
        std::vector<std::unique_ptr<Expression>> m_body;
    };
}