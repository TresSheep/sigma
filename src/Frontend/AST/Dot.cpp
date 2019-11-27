#include "Dot.h"

namespace Frontend::AST
{
    Dot::Dot(std::string lhs, std::string  rhs) :
        m_textLhs(lhs), m_textRhs(rhs)
    {
    }

    Dot::Dot(std::unique_ptr<Expression> lhs, std::string  rhs) :
        m_exprLhs(std::move(lhs)), m_textRhs(rhs)
    {
    }

    Dot::Dot(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression>  rhs) :
        m_exprLhs(std::move(lhs)), m_exprRhs(std::move(rhs))
    {
    }

    Dot::~Dot()
    {
    }

    std::unique_ptr<Backend::CodeGen::IR::Value> Dot::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
    {
        std::unique_ptr<Backend::CodeGen::IR::Value> lhs;
        std::unique_ptr<Backend::CodeGen::IR::Value> rhs;

        if (m_exprLhs)
        {
            // Continue
        }
        else
        {
            // Check if lhs is really a struct
            std::shared_ptr<Backend::CodeGen::IR::Variable> v = context->GetLocalVariable(m_textLhs);
            if (!v)
            {
                std::string str = "ERROR: Unexpected name: " + m_textLhs + "!\n";
                printf(str.c_str());
                exit(1);
            }

            if (!irGenerator.IsStructureType(v->GetType().GetIdentifier()))
            {
                std::string str = "ERROR: " + m_textLhs + " is not a struct!\n";
                printf(str.c_str());
                exit(1);
            }

            auto id = v->GetIdentifier();
            auto type = v->GetType();
            lhs = std::make_unique<Backend::CodeGen::IR::Variable>(id, type, false);
        }

        if (m_exprRhs)
        {
            // Continue, chain dot
        }
        else
        {
            // Check if rhs is a member
            bool found = false;
            for (auto& strct : irGenerator.GetStructures())
            {
                for (auto& part : strct->GetBody())
                {
                    if (part->GetIdentifier().compare(m_textRhs) == 0)
                    {
                        rhs = std::make_unique<Backend::CodeGen::IR::Variable>(false);
                        rhs->SetIdentifier(part->GetIdentifier());
                        found = true;
                    }
                }
            }

            if (!found)
            {
                std::string str = "ERROR: " + m_textRhs + " is not a member of " + m_textLhs + "!\n";
                printf(str.c_str());
                exit(1);
            }
        }

        std::unique_ptr<Backend::CodeGen::IR::Element> el(new Backend::CodeGen::IR::Element(std::move(lhs), std::move(rhs)));

        return std::move(el);
    }
}