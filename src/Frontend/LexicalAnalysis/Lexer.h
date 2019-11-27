#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

enum class TokenType
{
    newline,
    RET,
    FOREIGN,
    _NULL,
    EQUAL,
    PLUS,
    MUL,
    AUTO,
    IF,
    REPEAT,
    PROTO_SEPARATOR,
    SEPARATOR,
    ARROW,
    OPEN_P,
    CLOSE_P,
    OPEN_BLOCK,
    CLOSE_BLOCK,
    END_STATEMENT,
    STRING,
    IDENTIFIER,
    NUMBER,
    SLASH,
    COMMA,
    POINTER,
    COLON,    OPEN_BRACKET,    CLOSE_BRACKET,
    VAR,
    LOG_EQUAL,
    LOG_NEQ,
    MINUS,
    STRUCT,
    DOT,
    UNION,
    MODULO,
    AND,
    IMPL
};

struct Token
{
	TokenType type;
	std::string content;
};

class Lexer
{
public:
    Lexer(std::string filename);
    Lexer(std::stringstream& filename);
    ~Lexer();

    void Lex(std::string str, size_t& position);

    std::vector<Token> GetTokenStream();

private:
    std::vector<Token> m_tokenStream;
};

