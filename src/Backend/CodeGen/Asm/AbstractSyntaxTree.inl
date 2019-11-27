
#include "AbstractSyntaxTree.h"

namespace Backend::CodeGen::Asm
{


    typedef std::vector<std::pair<std::string, std::string>> syntax_args;
    typedef std::pair<std::string, std::string> syntax_arg;
    typedef std::pair<syntax_args, std::unique_ptr<Backend::CodeGen::Asm::AST::Expression>> node_and_expr_arg;
    typedef std::vector<std::pair<syntax_args, std::unique_ptr<Backend::CodeGen::Asm::AST::Expression>>> node_and_expr_args;

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
            m_exprNodes.push_back(ParseExprNode(tokenStream, position));
        }

        for (size_t position = 0; position < m_exprNodes.size(); position += 0)
        {
            ParseFreestanding(m_exprNodes, builder, position);
        }
    }

    template <typename Builder>
    ExprNode AbstractSyntaxTree<Builder>::ParseExprNode(const std::vector<Token>& tokenStream, size_t& position)
    {
        if (tokenStream[position + 0].type == TokenType::IDENTIFIER &&tokenStream[position + 1].type == TokenType::IDENTIFIER &&tokenStream[position + 2].type == TokenType::OPEN_P) {
            ExprNode node;
            node.ent = ENT::EXPR_PROTOTYPE_BEGIN;
            std::string type = tokenStream[position + 0].content;
            node.content.push_back(std::pair<std::string, std::string>("type", type));
            std::string id = tokenStream[position + 1].content;
            node.content.push_back(std::pair<std::string, std::string>("id", id));
            position += 2;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::IDENTIFIER &&tokenStream[position + 1].type == TokenType::POINTER &&tokenStream[position + 2].type == TokenType::IDENTIFIER &&tokenStream[position + 3].type == TokenType::OPEN_P) {
            ExprNode node;
            node.ent = ENT::EXPR_PROTOTYPE_BEGIN;
            std::string type = tokenStream[position + 0].content;
            node.content.push_back(std::pair<std::string, std::string>("type", type));
            std::string ptr = tokenStream[position + 1].content;
            node.content.push_back(std::pair<std::string, std::string>("ptr", ptr));
            std::string id = tokenStream[position + 2].content;
            node.content.push_back(std::pair<std::string, std::string>("id", id));
            position += 3;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::DECL&&tokenStream[position + 1].type == TokenType::IDENTIFIER &&tokenStream[position + 2].type == TokenType::IDENTIFIER &&tokenStream[position + 3].type == TokenType::POINTER) {
            ExprNode node;
            node.ent = ENT::EXPR_VARIABLE;
            std::string id = tokenStream[position + 1].content;
            node.content.push_back(std::pair<std::string, std::string>("id", id));
            std::string type = tokenStream[position + 2].content;
            node.content.push_back(std::pair<std::string, std::string>("type", type));
            std::string ptr = tokenStream[position + 3].content;
            node.content.push_back(std::pair<std::string, std::string>("ptr", ptr));
            position += 3;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::DECL&&tokenStream[position + 1].type == TokenType::IDENTIFIER &&tokenStream[position + 2].type == TokenType::IDENTIFIER) {
            ExprNode node;
            node.ent = ENT::EXPR_VARIABLE;
            std::string id = tokenStream[position + 1].content;
            node.content.push_back(std::pair<std::string, std::string>("id", id));
            std::string type = tokenStream[position + 2].content;
            node.content.push_back(std::pair<std::string, std::string>("type", type));
            position += 2;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::IDENTIFIER &&tokenStream[position + 1].type == TokenType::COLON) {
            ExprNode node;
            node.ent = ENT::EXPR_BLOCK;
            std::string id = tokenStream[position + 0].content;
            node.content.push_back(std::pair<std::string, std::string>("id", id));
            position += 1;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::OPEN_BLOCK) {
            ExprNode node;
            node.ent = ENT::EXPR_OPEN_BLOCK;
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::CLOSE_BLOCK) {
            ExprNode node;
            node.ent = ENT::EXPR_CLOSE_BLOCK;
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::MOVE) {
            ExprNode node;
            node.ent = ENT::EXPR_MOVE;
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::IDENTIFIER &&tokenStream[position + 1].type == TokenType::NUMBER) {
            ExprNode node;
            node.ent = ENT::EXPR_CONSTANT;
            std::string type = tokenStream[position + 0].content;
            node.content.push_back(std::pair<std::string, std::string>("type", type));
            std::string num = tokenStream[position + 1].content;
            node.content.push_back(std::pair<std::string, std::string>("num", num));
            position += 1;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::IDENTIFIER &&tokenStream[position + 1].type == TokenType::MINUS &&tokenStream[position + 2].type == TokenType::NUMBER) {
            ExprNode node;
            node.ent = ENT::EXPR_CONSTANT;
            std::string type = tokenStream[position + 0].content;
            node.content.push_back(std::pair<std::string, std::string>("type", type));
            std::string minus = tokenStream[position + 1].content;
            node.content.push_back(std::pair<std::string, std::string>("minus", minus));
            std::string num = tokenStream[position + 2].content;
            node.content.push_back(std::pair<std::string, std::string>("num", num));
            position += 2;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::ARRAY&&tokenStream[position + 1].type == TokenType::IDENTIFIER &&tokenStream[position + 2].type == TokenType::IDENTIFIER &&tokenStream[position + 3].type == TokenType::NUMBER) {
            ExprNode node;
            node.ent = ENT::EXPR_ARRAY;
            std::string type = tokenStream[position + 1].content;
            node.content.push_back(std::pair<std::string, std::string>("type", type));
            std::string id = tokenStream[position + 2].content;
            node.content.push_back(std::pair<std::string, std::string>("id", id));
            std::string size = tokenStream[position + 3].content;
            node.content.push_back(std::pair<std::string, std::string>("size", size));
            position += 3;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::UNION&&tokenStream[position + 1].type == TokenType::IDENTIFIER) {
            ExprNode node;
            node.ent = ENT::EXPR_UNION;
            std::string id = tokenStream[position + 1].content;
            node.content.push_back(std::pair<std::string, std::string>("id", id));
            position += 1;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::CALL) {
            ExprNode node;
            node.ent = ENT::EXPR_CALL;
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::ELEMENT) {
            ExprNode node;
            node.ent = ENT::EXPR_ELEMENT;
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::RETURN) {
            ExprNode node;
            node.ent = ENT::EXPR_RETURN;
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::COMMA) {
            ExprNode node;
            node.ent = ENT::EXPR_COMMA;
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::MINUS) {
            ExprNode node;
            node.ent = ENT::EXPR_MINUS;
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::MODULO) {
            ExprNode node;
            node.ent = ENT::EXPR_MODULO;
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::DIV) {
            ExprNode node;
            node.ent = ENT::EXPR_DIV;
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::IDENTIFIER &&tokenStream[position + 1].type == TokenType::OPEN_P) {
            ExprNode node;
            node.ent = ENT::EXPR_CALL_OPEN;
            std::string id = tokenStream[position + 0].content;
            node.content.push_back(std::pair<std::string, std::string>("id", id));
            position += 1;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::CLOSE_P) {
            ExprNode node;
            node.ent = ENT::EXPR_CLOSE_P;
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::IDENTIFIER &&tokenStream[position + 1].type == TokenType::POINTER &&tokenStream[position + 2].type == TokenType::STRING) {
            ExprNode node;
            node.ent = ENT::EXPR_STRING;
            std::string type = tokenStream[position + 0].content;
            node.content.push_back(std::pair<std::string, std::string>("type", type));
            std::string ptr = tokenStream[position + 1].content;
            node.content.push_back(std::pair<std::string, std::string>("ptr", ptr));
            std::string str = tokenStream[position + 2].content;
            node.content.push_back(std::pair<std::string, std::string>("str", str));
            position += 2;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::IDENTIFIER &&tokenStream[position + 1].type == TokenType::STRING) {
            ExprNode node;
            node.ent = ENT::EXPR_STRING;
            std::string type = tokenStream[position + 0].content;
            node.content.push_back(std::pair<std::string, std::string>("type", type));
            std::string str = tokenStream[position + 1].content;
            node.content.push_back(std::pair<std::string, std::string>("str", str));
            position += 1;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::JE) {
            ExprNode node;
            node.ent = ENT::EXPR_JUMP;
            std::string id = tokenStream[position + 0].content;
            node.content.push_back(std::pair<std::string, std::string>("id", id));
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::JNE) {
            ExprNode node;
            node.ent = ENT::EXPR_JUMP;
            std::string id = tokenStream[position + 0].content;
            node.content.push_back(std::pair<std::string, std::string>("id", id));
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::JMP) {
            ExprNode node;
            node.ent = ENT::EXPR_JUMP;
            std::string id = tokenStream[position + 0].content;
            node.content.push_back(std::pair<std::string, std::string>("id", id));
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::CMP) {
            ExprNode node;
            node.ent = ENT::EXPR_CMP;
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::ADD) {
            ExprNode node;
            node.ent = ENT::EXPR_ADD;
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::STRUCT&&tokenStream[position + 1].type == TokenType::IDENTIFIER) {
            ExprNode node;
            node.ent = ENT::EXPR_STRUCT;
            std::string id = tokenStream[position + 1].content;
            node.content.push_back(std::pair<std::string, std::string>("id", id));
            position += 1;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::ADDRESS_OF &&tokenStream[position + 1].type == TokenType::IDENTIFIER) {
            ExprNode node;
            node.ent = ENT::EXPR_VARIABLE_USAGE;
            std::string lval = tokenStream[position + 0].content;
            node.content.push_back(std::pair<std::string, std::string>("lval", lval));
            std::string id = tokenStream[position + 1].content;
            node.content.push_back(std::pair<std::string, std::string>("id", id));
            position += 1;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::IDENTIFIER &&tokenStream[position + 1].type == TokenType::POINTER) {
            ExprNode node;
            node.ent = ENT::EXPR_VARIABLE_USAGE;
            std::string id = tokenStream[position + 0].content;
            node.content.push_back(std::pair<std::string, std::string>("id", id));
            std::string ptr = tokenStream[position + 1].content;
            node.content.push_back(std::pair<std::string, std::string>("ptr", ptr));
            position += 1;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::IDENTIFIER) {
            ExprNode node;
            node.ent = ENT::EXPR_VARIABLE_USAGE;
            std::string id = tokenStream[position + 0].content;
            node.content.push_back(std::pair<std::string, std::string>("id", id));
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::END_STATEMENT) {
            ExprNode node;
            node.ent = ENT::EXPR_END_STATEMENT;
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::EXTERN) {
            ExprNode node;
            node.ent = ENT::EXPR_EXTERN;
            position += 0;
            return node;
        }
        if (tokenStream[position + 0].type == TokenType::FORWARD) {
            ExprNode node;
            node.ent = ENT::EXPR_FORWARD;
            position += 0;
            return node;
        }


        std::string s = "ERROR: Unexpected token: " + tokenStream[position].content + "!";
        printf(s.c_str());
        exit(1);
    }

    template <typename Builder>
    std::unique_ptr<AST::Expression> AbstractSyntaxTree<Builder>::ParseFreestanding(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position)
    {
        m_expr = std::move(ConstructStruct(exprStream, builder, position));
        if (m_expr) {
            m_expr->GenerateCode(builder);
            m_expr = nullptr;
            return nullptr;
        }
        m_expr = std::move(ConstructUnion(exprStream, builder, position));
        if (m_expr) {
            m_expr->GenerateCode(builder);
            m_expr = nullptr;
            return nullptr;
        }
        m_expr = std::move(ConstructForwardFunction(exprStream, builder, position));
        if (m_expr) {
            m_expr->GenerateCode(builder);
            m_expr = nullptr;
            return nullptr;
        }
        m_expr = std::move(ConstructExternFunction(exprStream, builder, position));
        if (m_expr) {
            m_expr->GenerateCode(builder);
            m_expr = nullptr;
            return nullptr;
        }
        m_expr = std::move(ConstructFunction(exprStream, builder, position));
        if (m_expr) {
            m_expr->GenerateCode(builder);
            m_expr = nullptr;
            return nullptr;
        }

        return nullptr;
    }


    template <typename Builder>
    std::unique_ptr<AST::Expression> AbstractSyntaxTree<Builder>::ParseExpression(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position, bool isExpr)
    {
        if (position < exprStream.size() - 1) {
            if (exprStream[position + 0].ent == ENT::EXPR_MINUS) {
                if (auto expr = ConstructNegative(exprStream, builder, position)) {
                    m_expr = std::move(expr);
                    if (isExpr) {
                        return nullptr;
                    }
                }
            }
        }
        if (position < exprStream.size() - 0) {
            if (exprStream[position + 0].ent == ENT::EXPR_ARRAY) {
                if (auto expr = ConstructArray(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 2) {
            if (exprStream[position + 0].ent == ENT::EXPR_ADD) {
                if (auto expr = ConstructAdd(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 2) {
            if (exprStream[position + 0].ent == ENT::EXPR_ADD) {
                if (auto expr = ConstructAdd(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 2) {
            if (exprStream[position + 0].ent == ENT::EXPR_MODULO) {
                if (auto expr = ConstructModulo(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 2) {
            if (exprStream[position + 0].ent == ENT::EXPR_MODULO) {
                if (auto expr = ConstructModulo(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 2) {
            if (exprStream[position + 0].ent == ENT::EXPR_DIV) {
                if (auto expr = ConstructDiv(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 2) {
            if (exprStream[position + 0].ent == ENT::EXPR_DIV) {
                if (auto expr = ConstructDiv(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 1) {
            if (exprStream[position + 0].ent == ENT::EXPR_RETURN) {
                if (auto expr = ConstructReturn(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 1) {
            if (exprStream[position + 0].ent == ENT::EXPR_RETURN) {
                if (auto expr = ConstructReturn(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 2) {
            if (exprStream[position + 0].ent == ENT::EXPR_ELEMENT) {
                if (auto expr = ConstructElement(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 0) {
            if (exprStream[position + 0].ent == ENT::EXPR_BLOCK) {
                if (auto expr = ConstructBlock(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 0) {
            if (exprStream[position + 0].ent == ENT::EXPR_VARIABLE) {
                if (auto expr = ConstructDecl(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 2) {
            if (exprStream[position + 0].ent == ENT::EXPR_MOVE) {
                if (auto expr = ConstructMove(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 2) {
            if (exprStream[position + 0].ent == ENT::EXPR_MOVE) {
                if (auto expr = ConstructMove(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 2) {
            if (exprStream[position + 0].ent == ENT::EXPR_MOVE) {
                if (auto expr = ConstructMove(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 2) {
            if (exprStream[position + 0].ent == ENT::EXPR_MOVE) {
                if (auto expr = ConstructMove(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 3) {
            if (exprStream[position + 0].ent == ENT::EXPR_CALL&&exprStream[position + 1].ent == ENT::EXPR_CALL_OPEN) {
                if (auto expr = ConstructCall(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 2) {
            if (exprStream[position + 0].ent == ENT::EXPR_CMP) {
                if (auto expr = ConstructCompare(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 2) {
            if (exprStream[position + 0].ent == ENT::EXPR_CMP) {
                if (auto expr = ConstructCompare(exprStream, builder, position)) {
                    return expr;
                }
            }
        }
        if (position < exprStream.size() - 1) {
            if (exprStream[position + 0].ent == ENT::EXPR_JUMP&&exprStream[position + 1].ent == ENT::EXPR_VARIABLE_USAGE) {
                if (auto expr = ConstructJump(exprStream, builder, position)) {
                    return expr;
                }
            }
        }

        return nullptr;
    }

    template <typename Builder>
    std::unique_ptr<AST::Prototype> AbstractSyntaxTree<Builder>::ConstructPrototype(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_PROTOTYPE_BEGIN) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            std::vector<std::pair<std::string, std::string>> vec;
            position += 1;
            while (exprStream[position].ent == ENT::EXPR_VARIABLE) {
                vec.insert(vec.end(), exprStream[position].content.begin(), exprStream[position].content.end());
                if (exprStream[position + 2].ent == ENT::EXPR_VARIABLE) {
                    if (exprStream[position + 1].ent != ENT::EXPR_COMMA) {
                        printf("ERROR: Expected separator");
                        exit(1);
                    }
                    position += 2;
                }
                else {
                    position += 1;
                    break;
                }
            }
            if (exprStream[position + 0].ent != ENT::EXPR_CLOSE_P) {
                break;
            }
            size_t a3 = position + 0;
            auto l3 = exprStream[a3].content;

            std::string id0;
            for (auto var : exprStream[a1].content) {
                if (var.first.compare("id") == 0) {
                    id0 = var.second;
                    break;
                }
            }
            std::string type1;
            for (auto var : exprStream[a3].content) {
                if (var.first.compare("type") == 0) {
                    type1 = var.second;
                    break;
                }
            }
            position += 1;
            std::unique_ptr<AST::Prototype> expr(new AST::Prototype(id0, std::move(vec), type1));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Struct> AbstractSyntaxTree<Builder>::ConstructStruct(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_STRUCT) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            if (exprStream[position + 1].ent != ENT::EXPR_OPEN_BLOCK) {
                break;
            }
            size_t a2 = position + 1;
            auto l2 = exprStream[a2].content;

            std::vector<std::unique_ptr<AST::Expression>> vec;
            position += 2;
            while (auto expr = ParseExpression(exprStream, builder, position, false)) {
                vec.push_back(std::move(expr));
            }
            if (exprStream[position + 0].ent != ENT::EXPR_CLOSE_BLOCK) {
                break;
            }
            size_t a4 = position + 0;
            auto l4 = exprStream[a4].content;

            std::string id0;
            for (auto var : exprStream[a1].content) {
                if (var.first.compare("id") == 0) {
                    id0 = var.second;
                    break;
                }
            }
            position += 1;
            std::unique_ptr<AST::Struct> expr(new AST::Struct(id0, std::move(vec)));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Union> AbstractSyntaxTree<Builder>::ConstructUnion(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_UNION) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            if (exprStream[position + 1].ent != ENT::EXPR_OPEN_BLOCK) {
                break;
            }
            size_t a2 = position + 1;
            auto l2 = exprStream[a2].content;

            std::vector<std::unique_ptr<AST::Expression>> vec;
            position += 2;
            while (auto expr = ParseExpression(exprStream, builder, position, false)) {
                vec.push_back(std::move(expr));
            }
            if (exprStream[position + 0].ent != ENT::EXPR_CLOSE_BLOCK) {
                break;
            }
            size_t a4 = position + 0;
            auto l4 = exprStream[a4].content;

            std::string id0;
            for (auto var : exprStream[a1].content) {
                if (var.first.compare("id") == 0) {
                    id0 = var.second;
                    break;
                }
            }
            position += 1;
            std::unique_ptr<AST::Union> expr(new AST::Union(id0, std::move(vec)));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Expression> AbstractSyntaxTree<Builder>::ConstructNegative(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_MINUS) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            auto l2 = exprStream[position + 1].content;
            position += 2;
            std::unique_ptr<AST::Negative> expr(new AST::Negative(std::move(l2)));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Expression> AbstractSyntaxTree<Builder>::ConstructArray(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_ARRAY) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            std::string type0;
            for (auto var : exprStream[a1].content) {
                if (var.first.compare("type") == 0) {
                    type0 = var.second;
                    break;
                }
            }
            std::string id1;
            for (auto var : exprStream[a1].content) {
                if (var.first.compare("id") == 0) {
                    id1 = var.second;
                    break;
                }
            }
            std::string size2;
            for (auto var : exprStream[a1].content) {
                if (var.first.compare("size") == 0) {
                    size2 = var.second;
                    break;
                }
            }
            position += 1;
            std::unique_ptr<AST::Array> expr(new AST::Array(type0, id1, size2));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Expression> AbstractSyntaxTree<Builder>::ConstructAdd(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_ADD) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            auto l2 = exprStream[position + 1].content;
            position += 2;
            auto l3 = ParseExpression(exprStream, builder, position, false);
            if (!l3) {
                break;
            }
            position += 0;
            std::unique_ptr<AST::Add> expr(new AST::Add(std::move(l2), std::move(l3)));
            return std::move(expr);
        }
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_ADD) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            auto l2 = exprStream[position + 1].content;
            auto l3 = exprStream[position + 2].content;
            position += 3;
            std::unique_ptr<AST::Add> expr(new AST::Add(std::move(l2), std::move(l3)));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Expression> AbstractSyntaxTree<Builder>::ConstructModulo(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_MODULO) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            auto l2 = exprStream[position + 1].content;
            position += 2;
            auto l3 = ParseExpression(exprStream, builder, position, false);
            if (!l3) {
                break;
            }
            position += 0;
            std::unique_ptr<AST::Modulo> expr(new AST::Modulo(std::move(l2), std::move(l3)));
            return std::move(expr);
        }
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_MODULO) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            auto l2 = exprStream[position + 1].content;
            auto l3 = exprStream[position + 2].content;
            position += 3;
            std::unique_ptr<AST::Modulo> expr(new AST::Modulo(std::move(l2), std::move(l3)));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Expression> AbstractSyntaxTree<Builder>::ConstructDiv(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_DIV) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            auto l2 = exprStream[position + 1].content;
            position += 2;
            auto l3 = ParseExpression(exprStream, builder, position, false);
            if (!l3) {
                break;
            }
            position += 0;
            std::unique_ptr<AST::Div> expr(new AST::Div(std::move(l2), std::move(l3)));
            return std::move(expr);
        }
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_DIV) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            auto l2 = exprStream[position + 1].content;
            auto l3 = exprStream[position + 2].content;
            position += 3;
            std::unique_ptr<AST::Div> expr(new AST::Div(std::move(l2), std::move(l3)));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Expression> AbstractSyntaxTree<Builder>::ConstructReturn(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_RETURN) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            position += 1;
            ParseExpression(exprStream, builder, position);
            if (!m_expr) {
                break;
            }
            auto l2 = std::move(m_expr);
            position += 0;
            std::unique_ptr<AST::Return> expr(new AST::Return(std::move(l2)));
            return std::move(expr);
        }
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_RETURN) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            auto l2 = exprStream[position + 1].content;
            position += 2;
            std::unique_ptr<AST::Return> expr(new AST::Return(std::move(l2)));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Expression> AbstractSyntaxTree<Builder>::ConstructElement(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_ELEMENT) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            auto l2 = exprStream[position + 1].content;
            auto l3 = exprStream[position + 2].content;
            position += 3;
            std::unique_ptr<AST::Element> expr(new AST::Element(std::move(l2), std::move(l3)));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Expression> AbstractSyntaxTree<Builder>::ConstructBlock(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_BLOCK) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            std::string id0;
            for (auto var : exprStream[a1].content) {
                if (var.first.compare("id") == 0) {
                    id0 = var.second;
                    break;
                }
            }
            position += 1;
            std::unique_ptr<AST::Block> expr(new AST::Block(id0));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Expression> AbstractSyntaxTree<Builder>::ConstructDecl(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_VARIABLE) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            std::string id0;
            for (auto var : exprStream[a1].content) {
                if (var.first.compare("id") == 0) {
                    id0 = var.second;
                    break;
                }
            }
            std::string type1;
            for (auto var : exprStream[a1].content) {
                if (var.first.compare("type") == 0) {
                    type1 = var.second;
                    break;
                }
            }
            std::string ptr2;
            for (auto var : exprStream[a1].content) {
                if (var.first.compare("ptr") == 0) {
                    ptr2 = var.second;
                    break;
                }
            }
            position += 1;
            std::unique_ptr<AST::Decl> expr(new AST::Decl(id0, type1, ptr2));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Expression> AbstractSyntaxTree<Builder>::ConstructMove(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_MOVE) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            position += 1;
            auto l2 = ParseExpression(exprStream, builder, position, false);
            if (!l2) {
                break;
            }
            auto l3 = ParseExpression(exprStream, builder, position, false); // Was not there
            if (!l3) {
                break;
            }
            //auto l3 = std::move(m_expr);
            position += 1;
            std::unique_ptr<AST::Move> expr(new AST::Move(std::move(l2), std::move(l3)));
            return std::move(expr);
        }
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_MOVE) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            position += 1;
            auto l2 = ParseExpression(exprStream, builder, position, false);
            if (!l2) {
                break;
            }
            auto l3 = exprStream[position + 0].content;
            position += 1;
            std::unique_ptr<AST::Move> expr(new AST::Move(std::move(l2), std::move(l3)));
            return std::move(expr);
        }
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_MOVE) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            auto l2 = exprStream[position + 1].content;
            position += 2;
            auto l3 = ParseExpression(exprStream, builder, position, false);
            if (!l3) {
                break;
            }
            position += 0;
            std::unique_ptr<AST::Move> expr(new AST::Move(std::move(l2), std::move(l3)));
            return std::move(expr);
        }
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_MOVE) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            auto l2 = exprStream[position + 1].content;
            auto l3 = exprStream[position + 2].content;
            position += 3;
            std::unique_ptr<AST::Move> expr(new AST::Move(std::move(l2), std::move(l3)));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Expression> AbstractSyntaxTree<Builder>::ConstructCall(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_CALL) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            if (exprStream[position + 1].ent != ENT::EXPR_CALL_OPEN) {
                break;
            }
            size_t a2 = position + 1;
            auto l2 = exprStream[a2].content;

            position += 2;
            node_and_expr_args vec;
            while (exprStream[position].ent != ENT::EXPR_CLOSE_P) {
                ParseExpression(exprStream, builder, position);
                if (m_expr) {
                    node_and_expr_arg e = node_and_expr_arg(syntax_args(), std::move(m_expr));
                    vec.push_back(std::move(e));
                    if (exprStream[position].ent != ENT::EXPR_CLOSE_P) {
                        if (exprStream[position].ent != ENT::EXPR_COMMA) {
                            printf("ERROR: Expected Separator");
                            exit(1);
                        }
                        position += 1;
                    }
                    else {
                        break;
                    }
                }
                else
                {
                    syntax_args e;
                    e.insert(e.end(), exprStream[position].content.begin(), exprStream[position].content.end());
                    vec.push_back(node_and_expr_arg(e, nullptr));
                    if (exprStream[position + 1].ent != ENT::EXPR_CLOSE_P) {
                        if (exprStream[position + 1].ent != ENT::EXPR_COMMA) {
                            printf("ERROR: Expected Separator");
                            exit(1);
                        }
                        position += 2;
                    }
                    else {
                        position += 1;
                        break;
                    }
                }
            }
            if (exprStream[position + 0].ent != ENT::EXPR_CLOSE_P) {
                break;
            }
            size_t a4 = position + 0;
            auto l4 = exprStream[a4].content;

            std::string id0;
            for (auto var : exprStream[a2].content) {
                if (var.first.compare("id") == 0) {
                    id0 = var.second;
                    break;
                }
            }
            std::string type1;
            for (auto var : exprStream[a2].content) {
                if (var.first.compare("type") == 0) {
                    type1 = var.second;
                    break;
                }
            }
            position += 1;
            std::unique_ptr<AST::Call> expr(new AST::Call(id0, type1, std::move(vec)));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Expression> AbstractSyntaxTree<Builder>::ConstructCompare(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_CMP) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            position += 1;
            auto l2 = ParseExpression(exprStream, builder, position, false);
            if (!l2) {
                break;
            }
            auto l3 = exprStream[position + 0].content;
            position += 1;
            std::unique_ptr<AST::Compare> expr(new AST::Compare(std::move(l2), std::move(l3)));
            return std::move(expr);
        }
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_CMP) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            auto l2 = exprStream[position + 1].content;
            auto l3 = exprStream[position + 2].content;
            position += 3;
            std::unique_ptr<AST::Compare> expr(new AST::Compare(std::move(l2), std::move(l3)));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Expression> AbstractSyntaxTree<Builder>::ConstructJump(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_JUMP) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            if (exprStream[position + 1].ent != ENT::EXPR_VARIABLE_USAGE) {
                break;
            }
            size_t a2 = position + 1;
            auto l2 = exprStream[a2].content;

            std::string id0;
            for (auto var : exprStream[a1].content) {
                if (var.first.compare("id") == 0) {
                    id0 = var.second;
                    break;
                }
            }
            std::string id1;
            for (auto var : exprStream[a2].content) {
                if (var.first.compare("id") == 0) {
                    id1 = var.second;
                    break;
                }
            }
            position += 2;
            std::unique_ptr<AST::Jump> expr(new AST::Jump(id0, id1));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::ForwardFunction> AbstractSyntaxTree<Builder>::ConstructForwardFunction(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_FORWARD) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            position += 1;
            auto l2 = ConstructPrototype(exprStream, builder, position);
            if (!l2) {
            }
            position += 0;
            std::unique_ptr<AST::ForwardFunction> expr(new AST::ForwardFunction(std::move(l2)));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::ExternFunction> AbstractSyntaxTree<Builder>::ConstructExternFunction(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            if (exprStream[position + 0].ent != ENT::EXPR_EXTERN) {
                break;
            }
            size_t a1 = position + 0;
            auto l1 = exprStream[a1].content;

            position += 1;
            auto l2 = ConstructPrototype(exprStream, builder, position);
            if (!l2) {
            }
            position += 0;
            std::unique_ptr<AST::ExternFunction> expr(new AST::ExternFunction(std::move(l2)));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }
    template <typename Builder>
    std::unique_ptr<AST::Function> AbstractSyntaxTree<Builder>::ConstructFunction(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position) {
        size_t tempPos = position;
        position = tempPos;
        while (true) {
            auto l1 = ConstructPrototype(exprStream, builder, position);
            if (!l1) {
            }
            if (exprStream[position + 0].ent != ENT::EXPR_OPEN_BLOCK) {
                break;
            }
            size_t a2 = position + 0;
            auto l2 = exprStream[a2].content;

            std::vector<std::unique_ptr<AST::Expression>> vec;
            position += 1;
            while (auto expr = ParseExpression(exprStream, builder, position, false)) {
                vec.push_back(std::move(expr));
            }
            if (exprStream[position + 0].ent != ENT::EXPR_CLOSE_BLOCK) {
                break;
            }
            size_t a4 = position + 0;
            auto l4 = exprStream[a4].content;

            position += 1;
            std::unique_ptr<AST::Function> expr(new AST::Function(std::move(l1), std::move(vec)));
            return std::move(expr);
        }
        position = tempPos;
        return nullptr;
    }



}