#pragma once

#include <string>
#include <memory>
#include "Value.h"

namespace Backend::CodeGen::IR
{
    enum class JumpCommands
    {
        jmp,
        jne,
        je
    };
    class Jump : public Value
    {
    public:
        Jump(std::string_view block);
        ~Jump();

        void SetType(const JumpCommands commmand);

        const std::string IR() override;

    private:
        std::string m_block;
        JumpCommands m_type;
    };
}
