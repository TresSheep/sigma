#pragma once

#include "Expression.h"
#include <string>
#include <fstream>

namespace Frontend::Preprocessor::AST
{
    class Import : public Expression
    {
    public:
        Import(std::string name);
        ~Import();

        void GenerateCode(Generator& generator) override;

    private:
        std::string m_name;
    };
}