#pragma once

#include <vector>
#include <string>
#include "../Registers.h"

namespace Backend::CodeGen::Asm::Command
{
    template <typename Type>
    struct AsmSubBase
    {
        static std::vector<uint8_t> GetBytes();

        static std::string GetDebug()
        {
            return subDebug;
        }

    protected:
        static std::string subDebug;
    };

    template <typename Type>
    std::string AsmSubBase<Type>::subDebug = "";

    template <typename Type>
    struct AsmSub : public AsmSubBase<Type> { };

    template <>
    struct AsmSub<Reg64> : public AsmSubBase<Reg64>
    {
        template <Reg64 dst, Reg64 src>
        static std::vector<uint8_t> GetBytes()
        {
            subDebug = "sub " + reg_to_string(dst) + ", " + reg_to_string(src) + "\n";
            std::vector<uint8_t> bytes;

            bytes.push_back(0b01001000);
            bytes.push_back(0x29);

            uint8_t byte = 0x00;
            byte |= (1 << 7);
            byte |= (1 << 6);
            reg_to_bin((size_t)dst, byte, 5);
            reg_to_bin((size_t)src, byte, 2);
            bytes.push_back(byte);

            return bytes;
        }

        template <Reg64 reg>
        static std::vector<uint8_t> GetBytes(int32_t val)
        {
            subDebug = "sub " + reg_to_string(reg) + ", " + std::to_string(val) + "\n";
            // Int

            std::vector<uint8_t> bytes;

            bytes.push_back(0b01001000);

            // Imm32
            bytes.push_back(0x83);

            uint8_t byte = 0x00;
            byte |= (1 << 7);
            byte |= (1 << 6);
            byte |= (1 << 5);
            byte |= (1 << 3);

            reg_to_bin((size_t)reg, byte, 2);
            bytes.push_back(byte);
            bytes.push_back(val);

            return bytes;
        }
    };
}