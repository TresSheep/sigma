#include "Assign.h"

namespace Frontend::AST
{
    Assign::Assign(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) :
        m_exprLhs(std::move(lhs)), m_exprRhs(std::move(rhs))
    {
    }

    Assign::Assign(std::unique_ptr<Expression> lhs, syntax_args rhs) :
        m_exprLhs(std::move(lhs)), m_rhs(rhs)
    {
    }

    Assign::Assign(syntax_args lhs, std::unique_ptr<Expression> rhs) :
        m_lhs(lhs), m_exprRhs(std::move(rhs))
    {
    }

    Assign::Assign(syntax_args lhs, syntax_args rhs) :
        m_lhs(lhs), m_rhs(rhs)
    {
    }

    Assign::~Assign()
    {
    }

    std::unique_ptr<Expression> Assign::CheckLHS(std::shared_ptr<Backend::CodeGen::IR::IRContext> con)
    {
        return std::move(SyntaxToExpression(m_lhs, con));
    }

    std::unique_ptr<Expression> Assign::CheckRHS(std::shared_ptr<Backend::CodeGen::IR::IRContext> con)
    {
        return std::move(SyntaxToExpression(m_rhs, con));
    }

    std::unique_ptr<Backend::CodeGen::IR::Value> Assign::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
    {
        std::unique_ptr<Backend::CodeGen::IR::Value> rhs;
        std::unique_ptr<Backend::CodeGen::IR::Value> lhs;
        if (m_exprRhs)
        {
            rhs = std::move(m_exprRhs->GenerateCode(context, irGenerator));
        }
        else
        {
            rhs = std::move(CheckRHS(context)->GenerateCode(context, irGenerator));
        }
        if (m_exprLhs)
        {
            lhs = std::move(m_exprLhs->GenerateCode(context, irGenerator));
        }
        else
        {
            if (m_lhs[0].first.compare("id") == 0)
            {
                if (m_lhs.size() == 2 && m_lhs[1].first.compare("type") == 0)
                {
                    // Variable
                    Backend::CodeGen::IR::DT dt;
                    // Check if type exists
                    if (m_lhs[1].second.compare("int") == 0)
                        dt = Backend::CodeGen::IR::Constant::GetInt32();
                    else if (m_lhs[1].second.compare("short") == 0)
                        dt = Backend::CodeGen::IR::DTInt(2);
                    else if (m_lhs[1].second.compare("long") == 0)
                        dt = Backend::CodeGen::IR::DTInt(8);
                    else if (m_lhs[1].second.compare("byte") == 0)
                        dt = Backend::CodeGen::IR::DTInt(1);
                    else if (m_lhs[1].second.compare("string") == 0)
                        dt = Backend::CodeGen::IR::DTString("");
                    else
                    {
                        // Check if the type exist
                        size_t byteCount = irGenerator.IsType(m_lhs[1].second);
                        if (byteCount == 0)
                        {
                            std::string s = "ERROR: Variable type: ";
                            s += m_lhs[1].second;
                            s += " does not exist!\n";
                            printf(s.c_str());
                            exit(1);
                        }

                        dt = irGenerator.GetType(m_lhs[1].second);
                    }

                    std::unique_ptr<Frontend::AST::Variable> var(new Frontend::AST::Variable(m_lhs[0].second, dt));

                    // Check if type implements "oper_equ"

                    lhs = std::move(var)->GenerateCode(context, irGenerator);
                }
                else
                    lhs = std::move(CheckLHS(context)->GenerateCode(context, irGenerator));
            }
            else
                lhs = std::move(CheckLHS(context)->GenerateCode(context, irGenerator));
        }

        std::unique_ptr<Backend::CodeGen::IR::Assign> assign(new Backend::CodeGen::IR::Assign(irGenerator, std::move(lhs), std::move(rhs)));

        return std::move(assign);
    }
}