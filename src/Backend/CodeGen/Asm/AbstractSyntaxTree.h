
#pragma once

#include "Lexer.h"
#include <memory>
#include <Backend/CodeGen/Asm/AST/AST.h>


namespace Backend::CodeGen::Asm
{


enum ENT
{
EXPR_PROTOTYPE_BEGIN,
EXPR_VARIABLE,
EXPR_BLOCK,
EXPR_OPEN_BLOCK,
EXPR_CLOSE_BLOCK,
EXPR_MOVE,
EXPR_CONSTANT,
EXPR_ARRAY,
EXPR_UNION,
EXPR_CALL,
EXPR_ELEMENT,
EXPR_RETURN,
EXPR_COMMA,
EXPR_MINUS,
EXPR_MODULO,
EXPR_DIV,
EXPR_CALL_OPEN,
EXPR_CLOSE_P,
EXPR_STRING,
EXPR_JUMP,
EXPR_CMP,
EXPR_ADD,
EXPR_STRUCT,
EXPR_VARIABLE_USAGE,
EXPR_END_STATEMENT,
EXPR_EXTERN,
EXPR_FORWARD,

};

typedef struct _ExprNode
{
    ENT ent;
    std::vector<std::pair<std::string, std::string>> content;
} ExprNode;

template <typename Builder>
class AbstractSyntaxTree
{
public:
    AbstractSyntaxTree(const std::vector<Token>& tokenStream, Builder& builder);
    ~AbstractSyntaxTree();

    void Run(const std::vector<Token>& tokenStream, Builder& builder);

    ExprNode ParseExprNode(const std::vector<Token>& tokenStream, size_t& position);
    std::unique_ptr<AST::Expression> ParseFreestanding(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
    std::unique_ptr<AST::Expression> ParseExpression(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position, bool isExpr = true);

private:
    std::vector<ExprNode> m_exprNodes;
    std::unique_ptr<AST::Expression> m_expr;
std::unique_ptr<AST::Prototype> ConstructPrototype(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Struct> ConstructStruct(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Union> ConstructUnion(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Expression> ConstructNegative(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Expression> ConstructArray(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Expression> ConstructAdd(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Expression> ConstructModulo(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Expression> ConstructDiv(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Expression> ConstructReturn(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Expression> ConstructElement(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Expression> ConstructBlock(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Expression> ConstructDecl(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Expression> ConstructMove(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Expression> ConstructCall(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Expression> ConstructCompare(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Expression> ConstructJump(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::ForwardFunction> ConstructForwardFunction(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::ExternFunction> ConstructExternFunction(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);
std::unique_ptr<AST::Function> ConstructFunction(const std::vector<ExprNode>& exprStream, Builder& builder, size_t& position);


};


}
#include "AbstractSyntaxTree.inl"