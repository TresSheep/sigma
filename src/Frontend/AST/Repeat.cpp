#include "Repeat.h"

namespace Frontend::AST
{
    Repeat::Repeat(std::unique_ptr<Expression> exprIf) :
        m_exprIf(std::move(exprIf))
    {
    }

    Repeat::~Repeat()
    {
    }

    std::unique_ptr<Backend::CodeGen::IR::Value> Repeat::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
    {
        if (auto exprIf = dynamic_cast<If*>(m_exprIf.get()))
        {
            exprIf->SetRepeat(true);
            return std::move(m_exprIf->GenerateCode(context, irGenerator));
        }
        else
        {
            printf("ERROR: expected if");
            exit(1);
        }
        return nullptr;
    }
}