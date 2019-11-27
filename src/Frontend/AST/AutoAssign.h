#pragma once

#include "Expression.h"

#include <Backend/CodeGen/IR/Constant.h>
#include <Backend/CodeGen/IR/Operators/Assign.h>
#include <Backend/CodeGen/IR/Types/DTNull.h>
#include "String.h"

#include "Variable.h"
#include "Index.h"

namespace Frontend::AST
{
    class AutoAssign : public Expression
    {
    public:
        AutoAssign(std::vector<std::pair<std::string, std::string>> lhs, std::vector<std::pair<std::string, std::string>> rhs);
        AutoAssign(std::vector<std::pair<std::string, std::string>> lhs, std::unique_ptr<Expression> rhs);
        ~AutoAssign();

        std::unique_ptr<Expression> CheckLHS(std::shared_ptr<Backend::CodeGen::IR::IRContext> context);
        std::unique_ptr<Expression> CheckRHS(std::shared_ptr<Backend::CodeGen::IR::IRContext> context);

        std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

    private:
        std::vector<std::pair<std::string, std::string>> m_lhs;
        std::vector<std::pair<std::string, std::string>> m_rhs;
        std::string m_currentType;
    };
}