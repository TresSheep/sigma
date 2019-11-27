#pragma once

#include <Backend/CodeGen/IR/IRGenerator.h>
#include <Backend/CodeGen/IR/Constant.h>
#include <Backend/CodeGen/IR/Return.h>
#include "Expression.h"
#include "Utility.h"

namespace Frontend::AST
{
    class Return : public Expression
    {
    public:
        Return(std::vector<std::pair<std::string, std::string>> expr);
        Return(std::unique_ptr<Expression> expr);
        ~Return();

        std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

    private:
        std::vector<std::pair<std::string, std::string>> m_expr;
        std::unique_ptr<Expression> m_ptrExpr;
    };
}