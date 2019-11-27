#include "Identifier.h"

namespace Driver::AST
{

    Identifier::Identifier(std::string identifier) :
        m_identifier(identifier)
    {
    }

    Identifier::~Identifier()
    {
    }

    void Identifier::GenerateCode(Build::BuildfileBuilder& builder)
    {
    }
}
