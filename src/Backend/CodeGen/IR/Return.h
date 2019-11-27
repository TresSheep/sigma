#pragma once

#include "Value.h"

namespace Backend::CodeGen::IR
{
    class Return : public Value
    {
    public:
        Return(std::unique_ptr<Value> value);
        ~Return();
        
        const std::string IR() override;

    private:
        std::unique_ptr<Value> m_value;
    };
}