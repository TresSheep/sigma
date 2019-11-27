#include "AutoAssign.h"

namespace Frontend::AST
{
    AutoAssign::AutoAssign(std::vector<std::pair<std::string, std::string>> lhs, std::vector<std::pair<std::string, std::string>> rhs) :
        m_lhs(lhs), m_rhs(rhs)
    {
    }

    AutoAssign::AutoAssign(std::vector<std::pair<std::string, std::string>> lhs, std::unique_ptr<Expression> rhs) :
        m_lhs(lhs)
    {
    }

    AutoAssign::~AutoAssign()
    {
    }

    std::unique_ptr<Expression> AutoAssign::CheckLHS(std::shared_ptr<Backend::CodeGen::IR::IRContext> context)
    {
        std::unique_ptr<Expression> lhs;
        if (m_lhs.size() == 1)
        {
            if (m_lhs[0].first.compare("id") == 0)
            {
                std::unique_ptr<Variable> var(new Variable(m_lhs[0].second, m_currentType));
                lhs = std::move(var);
            }
        }
        else
        {
            printf("ERROR: Unexpected error");
        }

        return std::move(lhs);
    }

    std::unique_ptr<Expression> AutoAssign::CheckRHS(std::shared_ptr<Backend::CodeGen::IR::IRContext> context)
    {
        std::unique_ptr<Expression> rhs;
        if (m_rhs.size() == 1)
        {
            if (m_rhs[0].first.compare("id") == 0)
            {
                // Variable
                std::shared_ptr<Backend::CodeGen::IR::Variable> v = context->GetLocalVariable(m_rhs[0].second);
                if (!v)
                {
                    std::string str = "ERROR: Unexpected variable: " + m_rhs[0].second + "!\n";
                    printf(str.c_str());
                    exit(1);
                }

                std::unique_ptr<Variable> var(new Variable(m_rhs[0].second));
                var->SetType(v->GetType());

                m_currentType = var->GetType();

                rhs = std::move(var);
            }
            else if (m_rhs[0].first.compare("num") == 0)
            {
                // Number
                std::unique_ptr<Number> num(new Number(m_rhs[0].second));

                rhs = std::move(num);
                m_currentType = "int";
            }
            else if (m_rhs[0].first.compare("str") == 0)
            {
                std::unique_ptr<String> str(new String(m_rhs[0].second));
                rhs = std::move(str);
                m_currentType = "string";
            }
        }
        else if (m_rhs.size() == 2)
        {
            //else if (m_rhs[0].first.compare("id") == 0 && m_rhs[1].first.compare("index") == 0)
            //{
            //    std::unique_ptr<Index> index(new Index(m_rhs[0].second, m_rhs[1].second));

            //    rhs = std::move(index->GenerateCode(con, irGenerator));
            //}
        }
        else if (m_rhs.size() == 3)
        {
        }

        return std::move(rhs);
    }

    std::unique_ptr<Backend::CodeGen::IR::Value> AutoAssign::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
    {
        // TODO: INDEX
        std::unique_ptr<Backend::CodeGen::IR::Value> rhs = std::move(CheckRHS(context)->GenerateCode(context, irGenerator));
        std::unique_ptr<Backend::CodeGen::IR::Value> lhs = std::move(CheckLHS(context)->GenerateCode(context, irGenerator));

        std::unique_ptr<Backend::CodeGen::IR::Assign> assign(new Backend::CodeGen::IR::Assign(irGenerator, std::move(lhs), std::move(rhs)));

        return std::move(assign);
    }
}