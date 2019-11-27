#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Backend::CodeGen::Asm
{

    enum class TokenType
    {
        newline,
        RETURN,
        CALL,
        DECL,
        GLOBAL,
        MOVE,
        EXTERN,
        CMP,
        JE,
        JNE,
        JMP,
        POINTER,
        OPEN_BLOCK,
        CLOSE_BLOCK,
        OPEN_P,
        CLOSE_P,
        STRING,
        IDENTIFIER,
        NUMBER,
        PERCENT,
        COLON,
        DOT,
        END_STATEMENT,
        ELEMENT,
        ADD,        MINUS,        COMMA,
        STRUCT,
        ARRAY,
        FORWARD,
        MODULO,
        DIV,
        UNION,
        ADDRESS_OF
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

}