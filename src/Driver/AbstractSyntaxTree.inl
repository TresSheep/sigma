
#include "AbstractSyntaxTree.h"

namespace Driver::Build
{

    template <typename Builder>
    AbstractSyntaxTree<Builder>::AbstractSyntaxTree(const std::vector<Token>& tokenStream, Builder& builder) :
        m_expression(nullptr), m_statement(nullptr), m_line(0)
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
        for (size_t position = 0; position < tokenStream.size(); position += 0)
        {
            m_expression = std::move(ParseExpr(tokenStream, position, builder));
            m_statement = std::move(ParseStatement(tokenStream, position, builder));

            if (m_expression == nullptr)
            {
                std::cout << "Undefined error. Line: " << m_line;
                exit(1);
            }
        }
    }

    template <typename Builder>
    std::unique_ptr<_Expression_t> AbstractSyntaxTree<Builder>::ParseExpr(const std::vector<Token>& tokenStream, size_t& position, Builder& builder)
    {
        switch (tokenStream[position].type)
        {
        case TokenType::IDENTIFIER:
        {
            std::unique_ptr<_Expression_t> _ptr = std::make_unique<_Expression_t>(std::make_unique<AST::Identifier>(tokenStream[position].content), PossibleExpression::Identifier);
            position += 1;
            return std::move(_ptr);
        }
        case TokenType::STRING:
        {
            std::unique_ptr<_Expression_t> _ptr = std::make_unique<_Expression_t>(std::make_unique<AST::String>(tokenStream[position].content), PossibleExpression::String);
            position += 1;
            return std::move(_ptr);
        }
        case TokenType::EQUAL:
        {
            if (m_expression->possible_expression == PossibleExpression::String)
            {
                std::cout << "lhs cannot be a string. Line " << m_line;
                exit(1);
            }

            std::unique_ptr<AST::Expression> lhs = std::move(m_expression->expression_ptr);
            position += 1; // Skip equal
            std::unique_ptr<AST::Expression> rhs = std::move(ParseExpr(tokenStream, position, builder)->expression_ptr);
            std::unique_ptr<_Expression_t> _ptr = std::make_unique<_Expression_t>(std::make_unique<AST::Equal>(std::move(lhs), std::move(rhs)), PossibleExpression::Equal);
            position += 0;
            return std::move(_ptr);
        }

        default:
            return nullptr;
        }
    }

    template <typename Builder>
    std::unique_ptr<AST::Statement> AbstractSyntaxTree<Builder>::ParseStatement(const std::vector<Token>& tokenStream, size_t& position, Builder& builder)
    {
        switch (tokenStream[position].type)
        {
        case TokenType::END_STATEMENT:
        {
            if (m_expression->possible_expression == PossibleExpression::String || m_expression->possible_expression == PossibleExpression::Identifier)
            {
                std::cout << "Invalid statement. Line: " << m_line;
                exit(1);
            }
            m_expression->expression_ptr->GenerateCode(builder);
            return nullptr;
        }
        default:
            return nullptr;
        }
    }

}