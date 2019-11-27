#include "Return.h"

namespace Frontend::AST
{
    Return::Return(std::vector<std::pair<std::string, std::string>> expr) :
        m_expr(expr)
    {
    }

    Return::Return(std::unique_ptr<Expression> expr) :
        m_ptrExpr(std::move(expr))
    {
    }

    Return::~Return()
    {
    }

    std::unique_ptr<Backend::CodeGen::IR::Value> Return::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
    {
        if (m_ptrExpr)
        {
            return m_ptrExpr->GenerateCode(context, irGenerator);
        }

        std::unique_ptr<Backend::CodeGen::IR::Value> val = std::move(SyntaxToExpression(m_expr, context)->GenerateCode(context, irGenerator));
        std::unique_ptr<Backend::CodeGen::IR::Return> ret(new Backend::CodeGen::IR::Return(std::move(val)));
        return std::move(ret);
    }
}
