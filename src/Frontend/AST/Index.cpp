#include "Index.h"

namespace Frontend::AST
{
    Index::Index(std::string dst, std::string value) :
        m_dst(dst), m_value(value)
    {
    }

    Index::~Index()
    {
    }


    std::unique_ptr<Backend::CodeGen::IR::Value> Index::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
    {
        if (m_dst[0] >= '0' && m_dst[0] <= '9')
        {
            printf("ERROR in index");
            exit(0);
        }

        std::shared_ptr<Backend::CodeGen::IR::Variable> sv = context->GetLocalVariable(m_dst);

        std::unique_ptr<Backend::CodeGen::IR::Variable> var(new Backend::CodeGen::IR::Variable(sv->GetIdentifier(), sv->GetType(), false));

        std::unique_ptr<Backend::CodeGen::IR::Value> value;

        if (m_value[0] >= '0' && m_value[0] <= '9')
        {
            std::unique_ptr<Backend::CodeGen::IR::DTInt> num(new Backend::CodeGen::IR::DTInt(4));
            num->SetValue(m_value);

            value = std::move(num);
        }
        else
        {
            std::shared_ptr<Backend::CodeGen::IR::Variable> v = context->GetLocalVariable(m_value);
            std::unique_ptr<Backend::CodeGen::IR::Variable> variable(new Backend::CodeGen::IR::Variable(v->GetIdentifier(), v->GetType(), false));

            value = std::move(variable);
        }

        std::unique_ptr<Backend::CodeGen::IR::Element> el(new Backend::CodeGen::IR::Element(std::move(var), std::move(value)));
        return std::move(el);
    }
}