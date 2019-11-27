#pragma once

#include "../Value.h"
#include "Add.h"
#include "../IRGenerator.h"

namespace Backend::CodeGen::IR
{
    class Assign : public Value
    {
    public:
        Assign(IRGenerator& irGenerator, std::shared_ptr<Value> lhs, std::shared_ptr<Value> rhs);
        ~Assign();

        void AddInit(std::unique_ptr<Value> init)
        {
            m_init = std::move(init);
        }

        const std::string IR() override;

    private:
        std::shared_ptr<Value> m_lhs;
        std::shared_ptr<Value> m_rhs;
        std::unique_ptr<Value> m_init;
        IRGenerator& m_gen;
    };
}