
#pragma once

#include "Lexer.h"
#include <memory>
#include "AST/AST.h"

namespace Driver::Build
{
    enum PossibleExpression
    {
        Identifier,
        String,
        Equal
    };

    typedef struct _Expression
    {
        std::unique_ptr<AST::Expression> expression_ptr;
        PossibleExpression possible_expression;

        _Expression (std::unique_ptr<AST::Expression> expression_ptr, PossibleExpression possible_expression) :
            expression_ptr(std::move(expression_ptr)), possible_expression(possible_expression) { }
    } _Expression_t;

    template <typename Builder>
    class AbstractSyntaxTree
    {
    public:
        AbstractSyntaxTree(const std::vector<Token>& tokenStream, Builder& builder);
        ~AbstractSyntaxTree();

        void Run(const std::vector<Token>& tokenStream, Builder& builder);

    private:
        std::unique_ptr<_Expression_t> ParseExpr(const std::vector<Token>& tokenStream, size_t& position, Builder& builder);
        std::unique_ptr<AST::Statement> ParseStatement(const std::vector<Token>& tokenStream, size_t& position, Builder& builder);

        std::unique_ptr<_Expression_t> m_expression;
        std::unique_ptr<AST::Statement> m_statement;

        size_t m_line;
    };
}

#include "AbstractSyntaxTree.inl"