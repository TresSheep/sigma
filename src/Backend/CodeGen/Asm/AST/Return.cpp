#include "Return.h"

namespace Backend::CodeGen::Asm::AST
{
    Return::Return(syntax_args arg) :
        m_arg(arg)
    {
    }

    Return::Return(std::unique_ptr<Expression> arg) :
        m_exprArg(std::move(arg))
    {
    }

    Return::~Return()
    {
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Return::GenerateCode(Asm::AsmContext& context)
    {
        std::unique_ptr<Value> val = nullptr;
        if (m_exprArg)
        {
            val = std::move(m_exprArg->GenerateCode(context));
        }
        else
        {
            val = std::move(SyntaxToExpression(m_arg, context)->GenerateCode(context));
        }

        std::unique_ptr<Asm::Return> ret(new Asm::Return(std::move(val)));
        return std::move(ret);
    }
}