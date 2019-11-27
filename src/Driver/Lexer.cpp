#include "Lexer.h"

namespace Driver::Build
{

    // macro a-z
#define IS_LOW_ALPHA(character) character >= 'a' && character <= 'z' || character == '_'

// macro A-Z
#define IS_HIGH_ALPHA(character) character >= 'A' && character <= 'Z' || character == '_'

#define IS_NUMBER(character) character >= '0' && character <= '9'

    Lexer::Lexer(std::string filename) :
        m_tokenStream(0)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cout << "can't open the file: " << filename;
            exit(0);
        }

        std::stringstream ss;
        size_t position = 0;
        ss << file.rdbuf();

        for (std::string str; std::getline(ss, str);)
        {
            Lex(str, position);
        }
    }

    Lexer::Lexer(std::stringstream stream) :
        m_tokenStream(0)
    {
        size_t position = 0;
        for (std::string str; std::getline(stream, str);)
        {
            Lex(str, position);
        }
    }

    Lexer::~Lexer()
    {
    }

    void Lexer::Lex(std::string str, size_t& position)
    {
        for (size_t position = 0; position < str.length(); position++)
        {
            if (str[position + 0] == '/'&&str[position + 1] == '/') {
                position = str.length();
            }
            if (str[position + 0] == '=') {
                Token token;
                token.type = TokenType::EQUAL;
                token.content = "=";
                m_tokenStream.push_back(token);
                position += 0;
            }
            if (str[position + 0] == ';') {
                Token token;
                token.type = TokenType::END_STATEMENT;
                token.content = ";";
                m_tokenStream.push_back(token);
                position += 0;
            }
            else if (str[position] == '\"') {
                Token token;
                token.type = TokenType::STRING;
                position += 1;
                while (str[position] != '\"') {
                    token.content += str[position];
                    position++;
                }
                m_tokenStream.push_back(token);
            }
            else if (IS_HIGH_ALPHA(str[position]) || IS_LOW_ALPHA(str[position])) {
                Token token;
                token.type = TokenType::IDENTIFIER;
                while (IS_HIGH_ALPHA(str[position]) || IS_LOW_ALPHA(str[position]) || IS_NUMBER(str[position])) {
                    token.content += str[position];
                    position++;
                }
                position--;
                m_tokenStream.push_back(token);
            }
            else if (IS_NUMBER(str[position])) {
                Token token;
                token.type = TokenType::NUMBER;
                while (IS_NUMBER(str[position])) {
                    token.content += str[position];
                    position++;
                }
                position--;
                m_tokenStream.push_back(token);
            }
        }
    }

    std::vector<Token> Lexer::GetTokenStream()
    {
        return m_tokenStream;
    }
}