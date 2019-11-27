#pragma once

#include <string>
#include <vector>
#include <memory>
#include <Driver/BuildfileBuilder.h>
#include "Expression.h"

namespace Driver::AST
{
    class Identifier : public Expression
    {
    public:
        Identifier(std::string identifier);
        ~Identifier();

        void GenerateCode(Build::BuildfileBuilder& builder) override;

    private:
        std::string m_identifier;
    };
}