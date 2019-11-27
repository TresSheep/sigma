#include "Modulo.h"

namespace Backend::CodeGen::Asm::AST
{
    Modulo::Modulo(syntax_args lhs, syntax_args rhs) :
        m_lhs(lhs), m_rhs(rhs)
    {
    }

    Modulo::Modulo(syntax_args lhs, std::unique_ptr<Expression> rhs) :
        m_lhs(lhs), m_exprRhs(std::move(rhs))
    {
    }

    Modulo::~Modulo()
    {
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Modulo::GenerateCode(Asm::AsmContext& context)
    {
        std::unique_ptr<Value> lhs = std::move(SyntaxToExpression(m_lhs, context)->GenerateCode(context));

        std::unique_ptr<Value> rhs;
        if (m_exprRhs)
            rhs = std::move(m_exprRhs->GenerateCode(context));
        else
            rhs = std::move(SyntaxToExpression(m_rhs, context)->GenerateCode(context));

        std::unique_ptr<Asm::Div> div(new Asm::Div(std::move(lhs), std::move(rhs), true));
        return std::move(div);
    }
}