#pragma once

#include "../Value.h"
#include "../Variable.h"

namespace Backend::CodeGen::IR
{
    class Add : public Value
    {
    public:
        Add(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs);
        ~Add();
        
        const std::string IR() override;

    private:
        std::unique_ptr<Value> m_lhs;
        std::unique_ptr<Value> m_rhs;
    };
}