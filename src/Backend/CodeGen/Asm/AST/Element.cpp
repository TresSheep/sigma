#include "Element.h"

namespace Backend::CodeGen::Asm::AST
{
    Element::Element(std::vector<std::pair<std::string, std::string>> lhs, std::vector<std::pair<std::string, std::string>> rhs) :
        m_lhs(lhs), m_rhs(rhs)
    {
    }

    Element::~Element()
    {
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Element::GenerateCode(Asm::AsmContext& context)
    {
        std::unique_ptr<Value> lhs = std::move(SyntaxToExpression(m_lhs, context)->GenerateCode(context));
        std::unique_ptr<Expression> rhs = std::move(SyntaxToExpression(m_rhs, context));

        bool strct = false;
        if (!rhs)
        {
            if (m_rhs[0].first.compare("id") == 0)
            {
                Var v = context.GetVar(m_lhs[0].second);
                if (v.size == -1)
                {
                    std::string s = "ERROR: Unexpected element: " + m_rhs[0].second + "!\n";
                    printf(s.c_str());
                    exit(1);
                }

                Type type = context.GetType(v.type);
                if (type.size == -1)
                {
                    // Fall back to standard
                    rhs = std::move(SyntaxToExpression(m_rhs, context));
                }

                size_t offset = 0;
                for (auto member : type.members)
                {
                    offset += member.size;

                    if (member.id.compare(m_rhs[0].second) == 0)
                    {
                        break;
                    }
                }

                strct = true;
                rhs = std::make_unique<Number>(std::to_string(offset));

                // Add offset [rdi+offset]
            }
        }

        std::unique_ptr<Asm::Element> element(new Asm::Element(std::move(lhs), std::move(rhs->GenerateCode(context)), strct));
        return std::move(element);
    }
}