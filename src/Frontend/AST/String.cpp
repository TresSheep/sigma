#include "String.h"

namespace Frontend
{
    namespace AST
    {
        String::String(std::vector<std::string> str) :
            m_str(str)
        {
        }

        String::String(std::string str)
        {
            m_str.push_back(str);
        }

        String::~String()
        {
        }

        std::unique_ptr<Backend::CodeGen::IR::Value> String::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
        {
            std::string s;
            for (auto word : m_str)
            {
                s += word;
            }
            std::unique_ptr<Backend::CodeGen::IR::DTString> str(new Backend::CodeGen::IR::DTString(s));
            return std::move(str);
        }
    }
}