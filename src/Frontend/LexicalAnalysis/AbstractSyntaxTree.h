
#pragma once

#include "Lexer.h"
#include <memory>

namespace Frontend::LexicalAnalysis
{

    template <typename Builder>
    class AbstractSyntaxTree
    {
    public:
        AbstractSyntaxTree(const std::vector<Token>& tokenStream, Builder& builder);
        ~AbstractSyntaxTree();

        void Run(const std::vector<Token>& tokenStream, Builder& builder);

    private:

    };

}

#include "AbstractSyntaxTree.inl"