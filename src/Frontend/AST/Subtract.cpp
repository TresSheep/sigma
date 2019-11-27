#include "Subtract.h"

namespace Frontend::AST
{
    Subtract::Subtract(std::vector<std::pair<std::string, std::string>> expr) :
        m_expr(expr)
    {
    }

    Subtract::Subtract(std::unique_ptr<Expression> lhs, std::vector<std::pair<std::string, std::string>> rhs) :
        m_lhs(std::move(lhs)), m_rhs(rhs)
    {
    }

    Subtract::~Subtract()
    {
    }

    std::unique_ptr<Backend::CodeGen::IR::Value> Subtract::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
    {
        if (m_lhs)
        {
        }
        else
        {
            std::unique_ptr<Backend::CodeGen::IR::Value> val = std::move(SyntaxToExpression(m_expr, context)->GenerateCode(context, irGenerator));
            std::unique_ptr<Backend::CodeGen::IR::Negative> negative(new Backend::CodeGen::IR::Negative(std::move(val)));
            return std::move(negative);
        }
    }
}