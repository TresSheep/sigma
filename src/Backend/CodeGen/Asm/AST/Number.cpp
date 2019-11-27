#include "Number.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>
#include "../Constant.h"

namespace Backend::CodeGen::Asm::AST
{
    Number::Number(std::string number) :
        m_number(number)
    {
    }

    Number::~Number()
    {
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Number::GenerateCode(Asm::AsmContext& context)
    {
        std::unique_ptr<Constant> constant(new Constant(m_number, "i32"));
        return std::move(constant);
    }
}