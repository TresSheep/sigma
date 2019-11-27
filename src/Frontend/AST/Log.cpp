#include "Log.h"

namespace Frontend::AST
{
    Log::Log(std::unique_ptr<Expression> lhs, syntax_args type, std::unique_ptr<Expression> rhs) :
        m_exprLhs(std::move(lhs)), m_exprRhs(std::move(rhs)), m_type(type)
    {
    }

    Log::Log(std::unique_ptr<Expression> lhs, syntax_args type, syntax_args rhs) :
        m_exprLhs(std::move(lhs)), m_rhs(rhs), m_type(type)
    {
    }

    Log::Log(syntax_args lhs, syntax_args type, std::unique_ptr<Expression> rhs) :
        m_lhs(lhs), m_exprRhs(std::move(rhs)), m_type(type)
    {
    }

    Log::Log(syntax_args lhs, syntax_args type, syntax_args rhs) :
        m_lhs(lhs), m_rhs(rhs), m_type(type)
    {
    }

    Log::~Log()
    {
    }

    LogType Log::GetType()
    {
        if (m_type[0].second.compare("==") == 0) return LogType::Equ;
        else if (m_type[0].second.compare("/=") == 0) return LogType::Neq;
    }

    std::unique_ptr<Backend::CodeGen::IR::Value> Log::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
    {
        std::unique_ptr<Backend::CodeGen::IR::Value> lhs;
        std::unique_ptr<Backend::CodeGen::IR::Value> rhs;
        if (m_exprLhs)
        {
            lhs = std::move(m_exprLhs->GenerateCode(context, irGenerator));
        }
        else
        {
            lhs = std::move(SyntaxToExpression(m_lhs, context)->GenerateCode(context, irGenerator));
        }

        if (m_exprRhs)
        {
            rhs = std::move(m_exprRhs->GenerateCode(context, irGenerator));
        }
        else
        {
            rhs = std::move(SyntaxToExpression(m_rhs, context)->GenerateCode(context, irGenerator));
        }

        std::unique_ptr<Backend::CodeGen::IR::Logic::Compare> compare(new Backend::CodeGen::IR::Logic::Compare(std::move(lhs), std::move(rhs)));
        return std::move(compare);
    }
}