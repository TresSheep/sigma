#pragma once

#include <vector>
#include <string>
#include "../Registers.h"

namespace Backend::CodeGen::Asm::Command
{
    template <typename Type>
    struct AsmLeaBase
    {
        static std::vector<uint8_t> GetBytes();

        static std::string GetDebug()
        {
            return leaDebug;
        }

    protected:
        static std::string leaDebug;
    };

    template <typename Type>
    std::string AsmLeaBase<Type>::leaDebug = "";

    template <typename Type>
    struct AsmLea : public AsmLeaBase<Type> { };

    template <>
    struct AsmLea<Reg64> : public AsmLeaBase<Reg64>
    {
        template <Reg64 dst, Reg64 src, bool dst_mem = false>
        static std::vector<uint8_t> GetBytes(int64_t offset = -1)
        {
            std::vector<uint8_t> bytes;
            leaDebug = "lea " + reg_to_string(dst) + ", ";
            if (offset != -1)
                leaDebug += "[" + reg_to_string(src) + "-" + std::to_string(offset) + "]\n";

            bytes.push_back(0x48);
            bytes.push_back(0x8D);

            uint8_t byte = 0x00;
            byte |= (1 << 6);
            reg_to_bin((size_t)dst, byte, 5);
            reg_to_bin((size_t)src, byte, 2);
            bytes.push_back(byte);

            if (offset != -1)
                bytes.push_back(-offset);

            return bytes;
        }
    };

    template <>
    struct AsmLea<Reg32> : public AsmLeaBase<Reg32>
    {
        template <Reg32 dst, Reg32 src, bool dst_mem = false>
        static std::vector<uint8_t> GetBytes(int64_t offset = -1)
        {
            std::vector<uint8_t> bytes;
            return bytes;
        }
    };
}