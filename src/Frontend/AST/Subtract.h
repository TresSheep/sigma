#pragma once

#include "Expression.h"

#include <Backend/CodeGen/IR/Constant.h>
#include <Backend/CodeGen/IR/Operators/Assign.h>
#include <Backend/CodeGen/IR/Negative.h>

#include "Utility.h"

namespace Frontend::AST
{
    class Subtract : public Expression
    {
    public:
        Subtract(std::vector<std::pair<std::string, std::string>> expr);
        Subtract(std::unique_ptr<Expression> lhs, std::vector<std::pair<std::string, std::string>> rhs);
        ~Subtract();

        std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

    private:
        std::unique_ptr<Expression> m_lhs;
        std::vector<std::pair<std::string, std::string>> m_rhs;
        std::vector<std::pair<std::string, std::string>> m_expr;
    };
}