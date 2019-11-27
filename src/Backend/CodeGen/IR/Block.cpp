#include "Block.h"

namespace Backend::CodeGen::IR
{
    Block::Block(std::string_view name, bool nested) :
        m_name(name), m_nested(nested)
    {
    }

    Block::~Block()
    {
    }

    void Block::AddBody(std::vector<std::unique_ptr<Value>> body)
    {
        m_body = std::move(body);
    }

    void Block::AddInit(std::vector<std::unique_ptr<Value>> init)
    {
        m_init = std::move(init);
    }

    const std::string Block::IR()
    {
        std::string str;
        str += m_name + ":\n";

        if (m_body.size() > 0)
        {
            for (auto& part : m_body)
            {
                str += "\t" + part->IR();
                str += "\n";
            }
        }
        return str;
    }
}