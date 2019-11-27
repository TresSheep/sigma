#pragma once

#include "../Value.h"
#include "../Variable.h"

namespace Backend::CodeGen::IR
{
    class Subtract : public Value
    {
    public:
        Subtract(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs);
        ~Subtract();

        const std::string IR() override;

    private:
        std::unique_ptr<Value> m_lhs;
        std::unique_ptr<Value> m_rhs;
    };
}