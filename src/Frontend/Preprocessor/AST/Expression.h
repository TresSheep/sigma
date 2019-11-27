#pragma once

#include "../Generator.h"

namespace Frontend::Preprocessor::AST
{
    typedef std::vector<std::pair<std::string, std::string>> syntax_args;

    class Expression
    {
    public:
        virtual void GenerateCode(Generator& generator) = 0;
    };
}