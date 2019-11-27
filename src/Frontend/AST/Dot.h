#pragma once

#include "Expression.h"
#include <Backend/CodeGen/IR/Element.h>

namespace Frontend
{
    namespace AST
    {
        class Dot : public Expression
        {
        public:
            Dot(std::string lhs, std::string  rhs);
            Dot(std::unique_ptr<Expression> lhs, std::string rhs);
            Dot(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
            ~Dot();

            std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;
        private:
            std::string m_textLhs;
            std::string m_textRhs;
            std::unique_ptr<Expression> m_exprLhs;
            std::unique_ptr<Expression> m_exprRhs;
        };
    }
}