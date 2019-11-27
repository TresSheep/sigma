#include "Lexer.h"

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
    ss << file.rdbuf();
    ss.seekp(0, std::ios::end);
    auto size = ss.tellp();
    ss.seekp(0, std::ios::beg);
    m_tokenStream.reserve(size);
    size_t position = 0;

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
        if (str[position + 0] == '/'&&str[position + 1] == '/') {
            position = str.length();
        }
        if (str[position + 0] == 'v'&&str[position + 1] == 'a'&&str[position + 2] == 'r') {
            Token token;
            token.type = TokenType::VAR;
            token.content = "var";
            m_tokenStream.push_back(token);
            position += 3;
        }
        if (str[position + 0] == 'r'&&str[position + 1] == 'e'&&str[position + 2] == 't') {
            Token token;
            token.type = TokenType::RET;
            token.content = "ret";
            m_tokenStream.push_back(token);
            position += 3;
        }
        else if (str[position + 0] == 'f'&&str[position + 1] == 'o'&&str[position + 2] == 'r'&&str[position + 3] == 'e'&&str[position + 4] == 'i'&&str[position + 5] == 'g'&&str[position + 6] == 'n') {
            Token token;
            token.type = TokenType::FOREIGN;
            token.content = "foreign";
            m_tokenStream.push_back(token);
            position += 6;
        }
        else if (str[position + 0] == 'n'&&str[position + 1] == 'u'&&str[position + 2] == 'l'&&str[position + 3] == 'l') {
            Token token;
            token.type = TokenType::_NULL;
            token.content = "null";
            m_tokenStream.push_back(token);
            position += 3;
        }
        else if (str[position + 0] == 'i'&&str[position + 1] == 'm'&&str[position + 2] == 'p'&&str[position + 3] == 'l') {
            Token token;
            token.type = TokenType::IMPL;
            token.content = "impl";
            m_tokenStream.push_back(token);
            position += 3;
        }

        else if (str[position + 0] == 's'&&str[position + 1] == 't'&&str[position + 2] == 'r'&&str[position + 3] == 'u'&&str[position + 4] == 'c'&&str[position + 5] == 't') {
            Token token;
            token.type = TokenType::STRUCT;
            token.content = "struct";
            m_tokenStream.push_back(token);
            position += 5;
        }
        else if (str[position + 0] == 'u'&&str[position + 1] == 'n'&&str[position + 2] == 'i'&&str[position + 3] == 'o'&&str[position + 4] == 'n') {
            Token token;
            token.type = TokenType::UNION;
            token.content = "union";
            m_tokenStream.push_back(token);
            position += 4;
        }
        else if (str[position + 0] == '=' && str[position + 1] == '=') {
            Token token;
            token.type = TokenType::LOG_EQUAL;
            token.content = "==";
            m_tokenStream.push_back(token);
            position += 1;
        }
        else if (str[position + 0] == '/' && str[position + 1] == '=') {
            Token token;
            token.type = TokenType::LOG_NEQ;
            token.content = "/=";
            m_tokenStream.push_back(token);
            position += 1;
        }
        else if (str[position + 0] == '-'&&str[position + 1] == '>') {
            Token token;
            token.type = TokenType::ARROW;
            token.content = "->";
            m_tokenStream.push_back(token);
            position += 1;
        }
        else if (str[position + 0] == '=') {
            Token token;
            token.type = TokenType::EQUAL;
            token.content = "=";
            m_tokenStream.push_back(token);
            position += 0;
        }
        else if (str[position + 0] == '+') {
            Token token;
            token.type = TokenType::PLUS;
            token.content = "+";
            m_tokenStream.push_back(token);
            position += 0;
        }
        else if (str[position + 0] == '-') {
            Token token;
            token.type = TokenType::MINUS;
            token.content = "-";
            m_tokenStream.push_back(token);
            position += 0;
        }
        else if (str[position + 0] == '*') {
            Token token;
            token.type = TokenType::MUL;
            token.content = "*";
            m_tokenStream.push_back(token);
            position += 0;
        }
        else if (str[position + 0] == ':'&&str[position + 1] == '=') {
            Token token;
            token.type = TokenType::AUTO;
            token.content = ":=";
            m_tokenStream.push_back(token);
            position += 1;
        }
        else if (str[position + 0] == '+') {
            Token token;
            token.type = TokenType::PLUS;
            token.content = "+";
            m_tokenStream.push_back(token);
            position += 0;
        }
        else if (str[position + 0] == '&') {
            Token token;
            token.type = TokenType::AND;
            token.content = "&";
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
        else if (str[position + 0] == 'i'&&str[position + 1] == 'f') {
            Token token;
            token.type = TokenType::IF;
            token.content = "if";
            m_tokenStream.push_back(token);
            position += 1;
        }
        else if (str[position + 0] == 'r'&&str[position + 1] == 'e'&&str[position + 2] == 'p'&&str[position + 3] == 'e'&&str[position + 4] == 'a'&&str[position + 5] == 't') {
            Token token;
            token.type = TokenType::REPEAT;
            token.content = "repeat";
            m_tokenStream.push_back(token);
            position += 5;
        }
        else if (str[position + 0] == ':'&&str[position + 1] == ':') {
            Token token;
            token.type = TokenType::PROTO_SEPARATOR;
            token.content = "::";
            m_tokenStream.push_back(token);
            position += 1;
        }
        else if (str[position + 0] == ':') {
            Token token;
            token.type = TokenType::SEPARATOR;
            token.content = ":";
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
        else if (str[position + 0] == '[') {
            Token token;
            token.type = TokenType::OPEN_BRACKET;
            token.content = "[";
            m_tokenStream.push_back(token);
            position += 0;
        }
        else if (str[position + 0] == ']') {
            Token token;
            token.type = TokenType::CLOSE_BRACKET;
            token.content = "]";
            m_tokenStream.push_back(token);
            position += 0;
        }
        else if (str[position + 0] == ';') {
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
        else if (str[position + 0] == '/') {
            Token token;
            token.type = TokenType::SLASH;
            token.content = "/";
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
        else if (str[position + 0] == '*') {
            Token token;
            token.type = TokenType::POINTER;
            token.content = "*";
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
    }
}

std::vector<Token> Lexer::GetTokenStream()
{
    return m_tokenStream;
}
