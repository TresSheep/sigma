#include "Jump.h"

namespace Backend::CodeGen::Asm::AST
{
    Jump::Jump(std::string type, std::string name) :
        m_type(type), m_name(name)
    {
    }

    Jump::~Jump()
    {
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Jump::GenerateCode(Asm::AsmContext& context)
    {
        std::unique_ptr<Asm::Jump> jmp(new Asm::Jump(m_name, m_type));
        // Get label position from context
        return std::move(jmp);
    }
}
