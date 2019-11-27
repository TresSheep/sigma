#pragma once

#include <string>
#include <vector>
#include <memory>
#include <Driver/BuildfileBuilder.h>
#include "Expression.h"

namespace Driver::AST
{
    class String : public Expression
    {
    public:
        String(std::string identifier);
        ~String();

        void GenerateCode(Build::BuildfileBuilder& builder) override;

    private:
        std::string m_identifier;
    };
}