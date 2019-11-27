#pragma once

#include "../Value.h"

namespace Backend::CodeGen::IR::Logic
{
    class Compare : public Value
    {
    public:
        Compare(std::unique_ptr<Value> val1, std::unique_ptr<Value> val2);
        ~Compare();

        const std::string IR() override;

    private:
        std::unique_ptr<Value> m_val1;
        std::unique_ptr<Value> m_val2;
    };
}