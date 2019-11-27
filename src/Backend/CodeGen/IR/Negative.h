#pragma once

#include "Types/DTInt.h"

namespace Backend::CodeGen::IR
{
    class Negative : public Value
    {
    public:
        Negative(std::unique_ptr<Value> expr);
        ~Negative();

        const std::string IR() override;

    private:
        std::unique_ptr<Value> m_expr;
    };
}