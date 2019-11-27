#include "Block.h"

namespace Backend::CodeGen::Asm::AST
{
    Block::Block(std::string name) :
        m_name(name)
    {
    }

    Block::~Block()
    {
    }

    void Block::SetParent(std::string parent)
    {
        m_parent = parent;
    }

    std::string Block::GetName()
    {
        return m_name;
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Block::GenerateCode(Asm::AsmContext& context)
    {
        std::vector<std::unique_ptr<Value>> body;
        std::unique_ptr<CodeBlock> codeBlock(new CodeBlock(m_name, m_parent));
        return std::move(codeBlock);
    }
}