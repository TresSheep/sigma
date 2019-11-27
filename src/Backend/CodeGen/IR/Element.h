#pragma once

#include <string>
#include <memory>
#include "Value.h"

namespace Backend::CodeGen::IR
{
    class Element : public Value
    {
    public:
        Element(std::unique_ptr<Value> dst, std::unique_ptr<Value> value);
        ~Element();

        const std::string IR() override;

    private:
        std::unique_ptr<Value> m_dst;
        std::unique_ptr<Value> m_value;
    };
}
