#pragma once

#include <vector>
#include <string>
#include "../Registers.h"
#include "mov.h"

namespace Backend::CodeGen::Asm::Command
{
    template <typename Type>
    struct AsmAddBase
    {
        static std::vector<uint8_t> GetBytes();

        static std::string GetDebug()
        {
            return addDebug;
        }

    protected:
        static std::string addDebug;
    };

    template <typename Type>
    std::string AsmAddBase<Type>::addDebug = "";

    template <typename Type>
    struct AsmAdd : public AsmAddBase<Type> { };

    template <>
    struct AsmAdd<Reg64> : public AsmAddBase<Reg64>
    {
        template <Reg64 dst, Reg64 src, bool dst_mem = false>
        static std::vector<uint8_t> GetBytes()
        {
            addDebug = "add qword " + reg_to_string(dst) + ", " + reg_to_string(src) + "\n";
            std::vector<uint8_t> bytes;

            bytes.push_back(0b01001000);

            if (dst_mem)
            {
                // rm64_r64_add
                bytes.push_back(0x01);

                uint8_t byte = 0x00;
                byte |= (1 << 7);
                byte |= (1 << 6);
                reg_to_bin(src, byte, 5);
                reg_to_bin(dst, byte, 2);
                bytes.push_back(byte);
            }
            else
            {
                // r64_rm64_add

                bytes.push_back(0x03);

                uint8_t byte = 0x00;
                byte |= (1 << 7);
                byte |= (1 << 6);
                reg_to_bin(src, byte, 5);
                reg_to_bin(dst, byte, 2);
                bytes.push_back(byte);
            }

            return bytes;
        }

        template <Reg64 dst>
        static std::vector<uint8_t> GetBytes(int8_t value, int32_t offset = -1)
        {
            addDebug = "add " + reg_to_string(dst) + ", " + std::to_string(value) + "\n";

            std::vector<uint8_t> bytes;
            if (offset != -1)
            {
                addDebug = "add qword [" + reg_to_string(dst) + "-" + std::to_string(offset) + "], " + std::to_string(value) + "\n";

                // With offset
                // r64_imm32_add

                bytes.push_back(0b01001000);
                bytes.push_back(0x81);

            }
            else
            {
                // Without offset
                // rm64_imm8_add

                bytes.push_back(0b01001000);
                bytes.push_back(0x83);
                uint8_t byte = 0x00;
                byte |= (1 << 7);
                byte |= (1 << 6);
                reg_to_bin(dst, byte, 2);
                bytes.push_back(byte);
                bytes.push_back(value);
            }

            return bytes;
        }
    };

    template <>
    struct AsmAdd<Reg32> : public AsmAddBase<Reg32>
    {
        template <Reg32 dst>
        static std::vector<uint8_t> GetBytes(int8_t value, int32_t offset = -1)
        {
            addDebug = "add dword " + reg_to_string(dst) + ", " + std::to_string(value) + "\n";

            std::vector<uint8_t> bytes;
            if (offset != -1)
            {
                addDebug = "add dword [" + reg_to_string(dst) + "-" + std::to_string(offset) + "], " + std::to_string(value) + "\n";

                bytes.push_back(0x67);
                bytes.push_back(0x83);
                uint8_t byte = 0x00;
                byte |= (1 << 6);
                reg_to_bin((size_t)dst, byte, 2);

                bytes.push_back(byte);
                bytes.push_back(-offset);

                bytes.push_back(value);
            }
            else
            {
                // Without offset
                // rm32_imm8_add

                bytes.push_back(0x83);
                uint8_t byte = 0x00;
                byte |= (1 << 7);
                byte |= (1 << 6);
                reg_to_bin((size_t)dst, byte, 2);

                bytes.push_back(byte);
                bytes.push_back(value);
            }

            return bytes;
        }
    };
}