#pragma once

#include <string>
#include "Value.h"
#include <memory>
#include <vector>

namespace Backend::CodeGen::IR
{
    class Call : public Value
    {
    public:
        Call(std::string_view name);
        ~Call();

        void AddArg(std::unique_ptr<Value> arg);

        const std::string IR();

    private:
        std::string m_name;
        std::vector<std::unique_ptr<Value>> m_args;
    };
}