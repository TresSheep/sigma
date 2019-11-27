#include "Add.h"

namespace Frontend::AST
{
    Add::Add(std::unique_ptr<Expression> lhs, syntax_args rhs) :
        m_exprLhs(std::move(lhs)), m_rhs(rhs)
    {
    }

    Add::Add(syntax_args lhs, syntax_args rhs) :
        m_lhs(std::move(lhs)), m_rhs(rhs)
    {
    }

    Add::~Add()
    {
    }

    std::unique_ptr<Backend::CodeGen::IR::Value> Add::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
    {
        std::unique_ptr<Backend::CodeGen::IR::Value> lhs;
        if (m_exprLhs)
        {
            lhs = std::move(m_exprLhs->GenerateCode(context, irGenerator));
        }
        else
        {
            lhs = std::move(SyntaxToExpression(m_lhs, context)->GenerateCode(context, irGenerator));
        }

        std::unique_ptr<Backend::CodeGen::IR::Value> rhs = std::move(SyntaxToExpression(m_rhs, context)->GenerateCode(context, irGenerator));

        std::unique_ptr<Backend::CodeGen::IR::Add> add(new Backend::CodeGen::IR::Add(std::move(lhs), std::move(rhs)));
        return add;
    }
}