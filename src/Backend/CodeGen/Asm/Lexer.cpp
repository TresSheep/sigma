#include "Lexer.h"

namespace Backend::CodeGen::Asm
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

    Lexer::Lexer(std::stringstream& stream) :
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
            if (str[position + 0] == 'r'&&str[position + 1] == 'e'&&str[position + 2] == 't'&&str[position + 3] == 'u'&&str[position + 4] == 'r'&&str[position + 5] == 'n') {
                Token token;
                token.type = TokenType::RETURN;
                token.content = "return";
                m_tokenStream.push_back(token);
                position += 6;
            }
            else if (str[position + 0] == 'c'&&str[position + 1] == 'a'&&str[position + 2] == 'l'&&str[position + 3] == 'l') {
                Token token;
                token.type = TokenType::CALL;
                token.content = "call";
                m_tokenStream.push_back(token);
                position += 5;
            }
            else if (str[position + 0] == 'd'&&str[position + 1] == 'e'&&str[position + 2] == 'c'&&str[position + 3] == 'l') {
                Token token;
                token.type = TokenType::DECL;
                token.content = "decl";
                m_tokenStream.push_back(token);
                position += 5;
            }
            else if (str[position + 0] == 'g'&&str[position + 1] == 'l'&&str[position + 2] == 'o'&&str[position + 3] == 'b'&&str[position + 4] == 'a'&&str[position + 5] == 'l') {
                Token token;
                token.type = TokenType::GLOBAL;
                token.content = "global";
                m_tokenStream.push_back(token);
                position += 6;
            }
            else if (str[position + 0] == 'm'&&str[position + 1] == 'o'&&str[position + 2] == 'v') {
                Token token;
                token.type = TokenType::MOVE;
                token.content = "mov";
                m_tokenStream.push_back(token);
                position += 3;
            }
            else if (str[position + 0] == 'e'&&str[position + 1] == 'x'&&str[position + 2] == 't'&&str[position + 3] == 'e'&&str[position + 4] == 'r'&&str[position + 5] == 'n') {
                Token token;
                token.type = TokenType::EXTERN;
                token.content = "extern";
                m_tokenStream.push_back(token);
                position += 6;
            }
            else if (str[position + 0] == 'm'&&str[position + 1] == 'o'&&str[position + 2] == 'd'&&str[position + 3] == 'u'&&str[position + 4] == 'l'&&str[position + 5] == 'o') {
                Token token;
                token.type = TokenType::MODULO;
                token.content = "modulo";
                m_tokenStream.push_back(token);
                position += 6;
            }
            if (str[position + 0] == 'e'&&str[position + 1] == 'l'&&str[position + 2] == 'e'&&str[position + 3] == 'm'&&str[position + 4] == 'e'&&str[position + 5] == 'n'&&str[position + 6] == 't') {
                Token token;
                token.type = TokenType::ELEMENT;
                token.content = "element";
                m_tokenStream.push_back(token);
                position += 7;
            }
            if (str[position + 0] == 'a'&&str[position + 1] == 'd'&&str[position + 2] == 'd'&&str[position + 3] == 'r'&&str[position + 4] == 'e'&&str[position + 5] == 's'&&str[position + 6] == 's'&&str[position + 7] == '_'&&str[position + 8] == 'o'&&str[position + 9] == 'f') {
                Token token;
                token.type = TokenType::ADDRESS_OF;
                token.content = "address_of";
                m_tokenStream.push_back(token);
                position += 10;
            }
            else if (str[position + 0] == 'c'&&str[position + 1] == 'm'&&str[position + 2] == 'p') {
                Token token;
                token.type = TokenType::CMP;
                token.content = "cmp";
                m_tokenStream.push_back(token);
                position += 3;
            }
            else if (str[position + 0] == 'd'&&str[position + 1] == 'i'&&str[position + 2] == 'v') {
                Token token;
                token.type = TokenType::DIV;
                token.content = "div";
                m_tokenStream.push_back(token);
                position += 3;
            }
            else if (str[position + 0] == 'a'&&str[position + 1] == 'd'&&str[position + 2] == 'd') {
                Token token;
                token.type = TokenType::ADD;
                token.content = "add";
                m_tokenStream.push_back(token);
                position += 3;
            }
            if (str[position + 0] == 'u'&&str[position + 1] == 'n'&&str[position + 2] == 'i'&&str[position + 3] == 'o'&&str[position + 4] == 'n') {
                Token token;
                token.type = TokenType::UNION;
                token.content = "union";
                m_tokenStream.push_back(token);
                position += 5;
            }
            else if (str[position + 0] == 'j'&&str[position + 1] == 'e') {
                Token token;
                token.type = TokenType::JE;
                token.content = "je";
                m_tokenStream.push_back(token);
                position += 2;
            }
            else if (str[position + 0] == 'j'&&str[position + 1] == 'n'&&str[position + 2] == 'e') {
                Token token;
                token.type = TokenType::JNE;
                token.content = "jne";
                m_tokenStream.push_back(token);
                position += 3;
            }
            else if (str[position + 0] == 'j'&&str[position + 1] == 'm'&&str[position + 2] == 'p') {
                Token token;
                token.type = TokenType::JMP;
                token.content = "jmp";
                m_tokenStream.push_back(token);
                position += 3;
            }
            else if (str[position + 0] == 's'&&str[position + 1] == 't'&&str[position + 2] == 'r'&&str[position + 3] == 'u'&&str[position + 4] == 'c'&&str[position + 5] == 't') {
                Token token;
                token.type = TokenType::STRUCT;
                token.content = "struct";
                m_tokenStream.push_back(token);
                position += 6;
            }
            else if (str[position + 0] == 'a'&&str[position + 1] == 'r'&&str[position + 2] == 'r'&&str[position + 3] == 'a'&&str[position + 4] == 'y') {
                Token token;
                token.type = TokenType::ARRAY;
                token.content = "array";
                m_tokenStream.push_back(token);
                position += 5;
            }
            if (str[position + 0] == 'f'&&str[position + 1] == 'o'&&str[position + 2] == 'r'&&str[position + 3] == 'w'&&str[position + 4] == 'a'&&str[position + 5] == 'r'&&str[position + 6] == 'd') {
                Token token;
                token.type = TokenType::FORWARD;
                token.content = "forward";
                m_tokenStream.push_back(token);
                position += 7;
            }
            else if (str[position + 0] == '*') {
                Token token;
                token.type = TokenType::POINTER;
                token.content = "*";
                m_tokenStream.push_back(token);
                position += 0;
            }
            else if (str[position + 0] == '{') {
                Token token;
                token.type = TokenType::OPEN_BLOCK;
                token.content = "{";
                m_tokenStream.push_back(token);
                position += 0;
            }
            else if (str[position + 0] == '}') {
                Token token;
                token.type = TokenType::CLOSE_BLOCK;
                token.content = "}";
                m_tokenStream.push_back(token);
                position += 0;
            }
            else if (str[position + 0] == '(') {
                Token token;
                token.type = TokenType::OPEN_P;
                token.content = "(";
                m_tokenStream.push_back(token);
                position += 0;
            }
            else if (str[position + 0] == ')') {
                Token token;
                token.type = TokenType::CLOSE_P;
                token.content = ")";
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
            else if (str[position + 0] == '%') {
                Token token;
                token.type = TokenType::PERCENT;
                token.content = "%";
                m_tokenStream.push_back(token);
                position += 0;
            }
            else if (str[position + 0] == ':') {
                Token token;
                token.type = TokenType::COLON;
                token.content = ":";
                m_tokenStream.push_back(token);
                position += 0;
            }
            else if (str[position + 0] == '.') {
                Token token;
                token.type = TokenType::DOT;
                token.content = ".";
                m_tokenStream.push_back(token);
                position += 0;
            }
            else if (str[position + 0] == ';') {
                Token token;
                token.type = TokenType::END_STATEMENT;
                token.content = ";";
                m_tokenStream.push_back(token);
                position += 0;
            }            else if (str[position + 0] == '-') {
                Token token;
                token.type = TokenType::MINUS;
                token.content = "-";
                m_tokenStream.push_back(token);
                position += 0;
            }
            else if (str[position + 0] == ',') {
                Token token;
                token.type = TokenType::COMMA;
                token.content = ",";
                m_tokenStream.push_back(token);
                position += 0;
            }
        }
    }

    std::vector<Token> Lexer::GetTokenStream()
    {
        return m_tokenStream;
    }
}