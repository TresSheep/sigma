#pragma once

#include <string>
#include <vector>
#include <memory>
#include <Driver/BuildfileBuilder.h>
#include "Expression.h"

namespace Driver::AST
{
    class Equal : public Expression
    {
    public:
        Equal(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
        ~Equal();

        void GenerateCode(Build::BuildfileBuilder& builder) override;

    private:
        std::unique_ptr<Expression> m_lhs;
        std::unique_ptr<Expression> m_rhs;
    };
}