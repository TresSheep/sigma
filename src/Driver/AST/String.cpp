#include "String.h"

namespace Driver::AST
{

    String::String(std::string identifier) :
        m_identifier(identifier)
    {
    }

    String::~String()
    {
    }

    void String::GenerateCode(Build::BuildfileBuilder& builder)
    {
    }
}
