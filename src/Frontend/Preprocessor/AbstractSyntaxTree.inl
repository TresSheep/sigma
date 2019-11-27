
#include "AbstractSyntaxTree.h"

namespace Frontend::Preprocessor
{

    template <typename Builder>
    AbstractSyntaxTree<Builder>::AbstractSyntaxTree(const std::vector<Token>& tokenStream, Builder& builder)
    {
        Run(tokenStream, builder);
    }

    template <typename Builder>
    AbstractSyntaxTree<Builder>::~AbstractSyntaxTree()
    {
    }

    template <typename Builder>
    void AbstractSyntaxTree<Builder>::Run(const std::vector<Token>& tokenStream, Builder& builder)
    {
        for (size_t position = 0; position < tokenStream.size(); position++)
        {
        }
    }

}