#include "Structure.h"

namespace Backend::CodeGen::IR
{
    Structure::Structure(const std::string& id, std::vector<std::unique_ptr<Value>> body, bool un) :
        m_id(id), m_body(std::move(body)), m_union(un)
    {
    }

    Structure::~Structure()
    {
    }

    const std::string& Structure::GetId()
    {
        return m_id;
    }

    std::vector<std::unique_ptr<Value>>& Structure::GetBody()
    {
        return m_body;
    }

    const std::string Structure::IR()
    {
        std::string str;
        if (m_union)
            str += "union ";
        else
            str = "struct ";
        str += m_id;
        str += " {\n";
        for (auto& part : m_body)
        {
            str += "\t" + part->IR() + "\n";
        }
        str += "}\n";
        return str;
    }
}
