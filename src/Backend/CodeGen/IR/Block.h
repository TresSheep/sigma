#pragma once

#include <string>
#include "Value.h"
#include <vector>

namespace Backend::CodeGen::IR
{
    class Block : public Value
    {
    public:
        Block(std::string_view name, bool nested = false);
        ~Block();

        void AddBody(std::vector<std::unique_ptr<Value>> body);
        void AddInit(std::vector<std::unique_ptr<Value>> init);

        const std::string IR();

    private:
        std::vector<std::unique_ptr<Value>> m_body;
        std::vector<std::unique_ptr<Value>> m_init;
        std::string m_name;
        bool m_nested;
    };
}