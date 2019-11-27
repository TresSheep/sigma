#include "String.h"

namespace Backend::CodeGen::Asm::AST
{
    String::String(std::string str) :
        m_str(str)
    {
    }

    String::~String()
    {
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> String::GenerateCode(Asm::AsmContext& context)
    {
        std::unique_ptr<Asm::String> str(new Asm::String(m_str));
        return std::move(str);
    }
}