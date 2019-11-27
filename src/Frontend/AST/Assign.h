#pragma once

#include "Expression.h"

#include <Backend/CodeGen/IR/Constant.h>
#include <Backend/CodeGen/IR/Operators/Assign.h>
#include <Backend/CodeGen/IR/Types/DTNull.h>

#include "Variable.h"
#include "Index.h"
#include "String.h"
#include "Utility.h"

namespace Frontend::AST
{
    class Assign : public Expression
    {
    public:
        Assign(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
        Assign(std::unique_ptr<Expression> lhs, syntax_args rhs);
        Assign(syntax_args lhs, std::unique_ptr<Expression> rhs);
        Assign(syntax_args lhs, syntax_args rhs);
        ~Assign();

        std::unique_ptr<Expression> CheckLHS(std::shared_ptr<Backend::CodeGen::IR::IRContext> con);
        std::unique_ptr<Expression> CheckRHS(std::shared_ptr<Backend::CodeGen::IR::IRContext> con);
        
        std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

    private:
        syntax_args m_lhs;
        syntax_args m_rhs;
        std::unique_ptr<Expression> m_exprLhs;
        std::unique_ptr<Expression> m_exprRhs;
    };
}