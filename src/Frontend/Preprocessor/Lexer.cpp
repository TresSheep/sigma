#include "Lexer.h"

namespace Frontend::Preprocessor
{

    // macro a-z
#define IS_LOW_ALPHA(character) character >= 'a' && character <= 'z' || character == '_'

// macro A-Z
#define IS_HIGH_ALPHA(character) character >= 'A' && character <= 'Z' || character == '_'

#define IS_NUMBER(character) character >= '0' && character <= '9'

    Lexer::Lexer(std::string filename) :
        m_tokenStream(0)
    {
        m_currentDirectory = filename;
        m_currentDirectory.erase(m_currentDirectory.begin() + m_currentDirectory.find_last_of("/") + 1, m_currentDirectory.end());
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
        bool parse = false;
        std::string line = str;
        for (size_t position = 0; position < str.length(); position++)
        {
            if (str[position + 0] == '/'&&str[position + 1] == '/') {
                position = str.length();
            }
            if (str[position + 0] == 'i'&&str[position + 1] == 'm'&&str[position + 2] == 'p'&&str[position + 3] == 'o'&&str[position + 4] == 'r'&&str[position + 5] == 't') {
                if (parse)
                {
                    Token token;
                    token.type = TokenType::IMPORT;
                    token.content = "import";
                    m_tokenStream.push_back(token);
                    position += 5;
                }
            }
            if (str[position + 0] == 'e'&&str[position + 1] == 'x'&&str[position + 2] == 'p'&&str[position + 3] == 'o'&&str[position + 4] == 'r'&&str[position + 5] == 't') {
                if (parse)
                {
                    Token token;
                    token.type = TokenType::EXPORT;
                    token.content = "export";
                    m_tokenStream.push_back(token);
                    position += 5;
                }
            }
            else if (str[position + 0] == ':' && str[position + 1] == ':')
            {
                // Prototype
                    // Save function
                if (str.find("foreign") == std::string::npos)
                    m_functions.push_back(line + ";");

                position += 2;
            }
            else if (str[position + 0] == '#') {
                Token token;
                token.type = TokenType::HASH;
                token.content = "#";
                m_tokenStream.push_back(token);
                position += 0;
                parse = true;
            }
            else if (str[position] == '"') {
                Token token;
                if (parse)
                {
                    token.type = TokenType::STRING;
                    position += 1;
                    while (str[position] != '"') {
                        token.content += str[position];
                        position++;
                    }
                    m_tokenStream.push_back(token);

                    std::ifstream file(m_currentDirectory + token.content);
                    if (file.is_open())
                    {
                        Lexer lex(m_currentDirectory + token.content);
                        for (auto func : lex.GetFunctions())
                        {
                            m_stream << func << std::endl;;
                        }
                    }
                    else
                    {
                        // Standard lib
                        Lexer lex("B:/sigma/std/" + token.content);
                        for (auto func : lex.GetFunctions())
                        {
                            m_stream << func << std::endl;;
                        }
                        bool found = false;
                        for (auto lib : m_toLink)
                        {
                            if (lib.compare("B:/sigma/std/" + token.content) == 0)
                                found = true;
                        }
                        if (!found)
                            m_toLink.push_back("B:/sigma/std/" + token.content);
                    }
                    file.close();
                }
            }
        }        if (!parse)            m_stream << line << std::endl;
    }

    const std::vector<Token>& Lexer::GetTokenStream()
    {
        return m_tokenStream;
    }

    std::stringstream& Lexer::GetStream()
    {
        return m_stream;
    }

}