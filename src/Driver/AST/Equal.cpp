#include "Equal.h"

namespace Driver::AST
{

    Equal::Equal(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) :
        m_lhs(std::move(lhs)), m_rhs(std::move(rhs))
    {
    }

    Equal::~Equal()
    {
    }

    void Equal::GenerateCode(Build::BuildfileBuilder& builder)
    {
    }
}
