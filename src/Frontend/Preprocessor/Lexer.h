#pragma once

// HANDMADE

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Frontend::Preprocessor
{

    enum class TokenType
    {
        newline,
        IMPORT,
        PROTO_SEPARATOR,
        OPEN_P,
        CLOSE_P,
        ARROW,
        POINTER,
        COLON,
        HASH,
        STRING,
        IDENTIFIER,
        COMMA,        EXPORT,
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

        const std::vector<Token>& GetTokenStream();        std::stringstream& GetStream();        std::vector<std::string> GetFunctions()        {            return m_functions;        }        const std::vector<std::string>& GetFilesToLink()        {            return m_toLink;        }

    private:
        std::vector<Token> m_tokenStream;        std::stringstream m_stream;        std::vector<std::string> m_functions;        std::string m_currentDirectory;        std::vector<std::string> m_toLink;
    };

}