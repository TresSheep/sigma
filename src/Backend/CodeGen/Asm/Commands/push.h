#pragma once

#include <vector>
#include <string>
#include "../Registers.h"

namespace Backend::CodeGen::Asm::Command
{
    template <typename Type>
    struct AsmPushBase
    {
        static uint8_t GetByte()
        {
            return 0;
        }

        static uint8_t GetBytes()
        {
        }

        static std::string GetDebug()
        {
            return pushDebug;
        }

    protected:
        static std::string pushDebug;
    };

    template <typename Type>
    std::string AsmPushBase<Type>::pushDebug = "";

    template <typename Type>
    struct AsmPush : public AsmPushBase<Type>
    {
    };

    template <>
    struct AsmPush<Reg64> : public AsmPushBase<Reg64>
    {
        template <Reg64 reg>
        static uint8_t GetByte()
        {
            pushDebug = "push " + reg_to_string(reg) + "\n";
            uint8_t byte = 0x50 + (size_t)reg;
            return byte;
        }

        static std::vector<uint8_t> GetBytes(int8_t val)
        {
            pushDebug = "push " + std::to_string(val) + "\n";
            std::vector<uint8_t> bytes;
            bytes.push_back(0x6A);
            bytes.push_back(val);
            return bytes;
        }
    };
}