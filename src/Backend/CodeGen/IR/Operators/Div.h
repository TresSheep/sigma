#pragma once

#include "../Value.h"
#include "../Variable.h"

namespace Backend::CodeGen::IR
{
    class Div : public Value
    {
    public:
        Div(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs, bool isModulo = false);
        ~Div();

        const std::string IR() override;

    private:
        std::unique_ptr<Value> m_lhs;
        std::unique_ptr<Value> m_rhs;
        bool m_isModulo;
    };
}