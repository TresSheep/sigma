#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Driver::Build
{

    enum class TokenType
    {
        newline,
        EQUAL,
        END_STATEMENT,
        STRING,
        IDENTIFIER,
        NUMBER,


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

        Lexer(std::stringstream filename);

        ~Lexer();



        void Lex(std::string str, size_t& position);



        std::vector<Token> GetTokenStream();



    private:

        std::vector<Token> m_tokenStream;

    };



}