#pragma once

#include "Value.h"
#include "Types/DT.h"
#include <vector>

namespace Backend::CodeGen::IR
{
    class Structure : public Value
    {
    public:
        Structure(const std::string& id, std::vector<std::unique_ptr<Value>> body, bool un = false);
        ~Structure();

        const std::string& GetId();
        std::vector<std::unique_ptr<Value>>& GetBody();

        bool IsUnion()
        {
            return m_union;
        }

        const std::string IR() override;

    private:
        std::string m_id;
        std::vector<std::unique_ptr<Value>> m_body;
        bool m_union;
    };
}