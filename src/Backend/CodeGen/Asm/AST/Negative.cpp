#include "Negative.h"

namespace Backend::CodeGen::Asm::AST
{
    Negative::Negative(syntax_args expr) :
        m_expr(expr)
    {
    }

    Negative::Negative(std::string num) :
        m_num(num)
    {
    }

    Negative::~Negative()
    {
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Negative::GenerateCode(Asm::AsmContext& context)
    {
        if (m_expr.empty())
        {
            std::unique_ptr<Constant> constant(new Constant("-" + m_num, "i32"));
            return std::move(constant);
        }
        else
        {
        }
        return nullptr;
    }
}