#pragma once

#include <string>
#include <vector>
#include <memory>
#include <Driver/BuildfileBuilder.h>

namespace Driver::AST
{
    class Expression
    {
    public:
        virtual void GenerateCode(Build::BuildfileBuilder& builder) = 0;
    };
}