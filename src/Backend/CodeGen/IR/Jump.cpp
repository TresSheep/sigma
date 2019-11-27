#include "Jump.h"

namespace Backend::CodeGen::IR
{
    Jump::Jump(std::string_view block) :
        m_block(block)
    {
    }

    Jump::~Jump()
    {
    }

    void Jump::SetType(const JumpCommands command)
    {
        m_type = command;
    }

    const std::string Jump::IR()
    {
        std::string str;

        switch (m_type)
        {
        case JumpCommands::jmp:
            return "jmp " + m_block;
        case JumpCommands::jne:
            return "jne " + m_block;
        case JumpCommands::je:
            return "je " + m_block;
        }

        return "";
    }
}