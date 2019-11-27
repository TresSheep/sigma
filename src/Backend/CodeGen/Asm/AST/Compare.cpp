#include "Compare.h"

namespace Backend::CodeGen::Asm::AST
{
    Compare::Compare(syntax_args lhs, syntax_args rhs) :
        m_lhs(lhs), m_rhs(rhs)
    {
    }

    Compare::Compare(std::unique_ptr<Expression> lhs, syntax_args rhs) :
        m_exprLhs(std::move(lhs)), m_rhs(rhs)
    {
    }

    Compare::~Compare()
    {
    }

    std::unique_ptr<Value> Compare::CheckLHS(std::shared_ptr<Asm::AsmContext> context)
    {
        std::unique_ptr<Value> lhs;
        return std::move(lhs);
    }

    std::unique_ptr<Value> Compare::CheckRHS(Asm::AsmContext& context)
    {
        std::unique_ptr<Value> rhs;

        if (m_rhs.size() == 1)
        {
        }
        else if (m_rhs.size() == 2)
        {
            if (m_rhs[0].first.compare("type") == 0)
            {
                if (m_rhs[1].first.compare("num") == 0)
                {
                    std::unique_ptr<Asm::Constant> con(new Asm::Constant(m_rhs[1].second, m_rhs[0].second));

                    rhs = std::move(con);
                }
            }
        }

        return std::move(rhs);
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Compare::GenerateCode(Asm::AsmContext& context)
    {
        std::unique_ptr<Value> lhs;
        if (m_exprLhs)
        {
            lhs = std::move(m_exprLhs->GenerateCode(context));
        }
        else
        {
            lhs = std::move(SyntaxToExpression(m_lhs, context)->GenerateCode(context));
        }
        std::unique_ptr<Value> rhs = std::move(CheckRHS(context));

        std::unique_ptr<Asm::Compare> cmp(new Asm::Compare(std::move(lhs), std::move(rhs)));
        return std::move(cmp);
    }
}
