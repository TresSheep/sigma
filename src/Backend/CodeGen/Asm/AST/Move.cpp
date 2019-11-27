#include "Move.h"

namespace Backend::CodeGen::Asm::AST
{
    Move::Move(syntax_args lhs, syntax_args rhs) :
        m_lhs(lhs), m_rhs(rhs)
    {
    }

    Move::Move(syntax_args lhs, std::unique_ptr<Expression> rhs) :
        m_lhs(lhs), m_exprRhs(std::move(rhs))
    {
    }

    Move::Move(std::unique_ptr<Expression> lhs, syntax_args rhs) :
        m_exprLhs(std::move(lhs)), m_rhs(rhs)
    {
    }

    Move::Move(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) :
        m_exprLhs(std::move(lhs)), m_exprRhs(std::move(rhs))
    {
    }

    Move::~Move()
    {
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Move::GenerateCode(Asm::AsmContext& context)
    {
        // LHS decides type

        std::unique_ptr<Value> lhs;
        if (m_exprLhs)
        {
            lhs = m_exprLhs->GenerateCode(context);
        }
        else
        {
            lhs = std::move(SyntaxToExpression(m_lhs, context)->GenerateCode(context));
        }
        if (auto var = dynamic_cast<Asm::Variable*>(lhs.get()))
        {
            m_size = var->GetSize();
        }
        std::unique_ptr<Value> rhs;
        if (m_exprRhs)
        {
            rhs = m_exprRhs->GenerateCode(context);
        }
        else
        {
            rhs = std::move(SyntaxToExpression(m_rhs, context)->GenerateCode(context));
        }

        std::unique_ptr<Asm::Move> mov(new Asm::Move(std::move(lhs), std::move(rhs), m_size));
        return std::move(mov);
    }
}