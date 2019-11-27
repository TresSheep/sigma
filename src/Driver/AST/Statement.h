#pragma once

#include <string>
#include <vector>
#include <memory>
#include <Driver/BuildfileBuilder.h>

namespace Driver::AST
{
    class Statement
    {
    public:
        virtual void GenerateCode(Build::BuildfileBuilder& builder) = 0;
    };
}