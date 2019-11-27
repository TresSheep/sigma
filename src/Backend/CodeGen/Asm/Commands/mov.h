#pragma once

#include <vector>
#include <string>
#include "xor.h"
#include "variable.h"
#include <memory>
#include "../Registers.h"
#include "lea.h"

namespace Backend::CodeGen::Asm::Command
{
    union Int64ToBytes
    {
        size_t number;
        uint8_t bytes[8];
    };

    template <size_t Size>
    struct AsmMovBase
    {
        static std::vector<uint8_t> GetBytes();

        static std::string GetDebug()
        {
            return movDebug;
        }

    protected:
        static std::string movDebug;
    };

    template <size_t Size>
    std::string AsmMovBase<Size>::movDebug = "";

    template <size_t Size>
    struct AsmMov : public AsmMovBase<Size> { };

    template <>
    struct AsmMov<8> : public AsmMovBase<8>
    {
        template <Reg64 dst>
        static std::vector<uint8_t> GetBytes(int32_t src, int32_t offset = -1)
        {
            std::vector<uint8_t> bytes;

            if ((size_t)dst > 7)
            {
                movDebug = "mov qword " + reg_to_string(dst) + ", " + std::to_string(src) + "\n";
                bytes.push_back(0x41);
                bytes.push_back(0xB8 + (size_t)dst - 8);
            }
            else
            {
                movDebug = "mov qword " + reg_to_string(dst) + ", " + std::to_string(src) + "\n";

                if (offset != -1)
                {
                    if (offset < 0)
                    {
                        bytes.push_back(0x48);
                        bytes.push_back(0xC7);

                        movDebug = "mov qword [" + reg_to_string(dst) + "+" + std::to_string(-offset) + "], " + std::to_string(src) + "\n";
                        uint8_t byte = 0x00;
                        byte |= (1 << 6);
                        reg_to_bin((size_t)dst, byte, 2);
                        bytes.push_back(byte);

                        bytes.push_back(0x24);
                        bytes.push_back(-offset);
                    }
                    else
                    {
                        movDebug = "mov qword [" + reg_to_string(dst) + std::to_string(-offset) + "], " + std::to_string(src) + "\n";
                        uint8_t byte = 0x00;
                        byte |= (1 << 7);
                        byte |= (1 << 6);
                        reg_to_bin((size_t)dst, byte, 2);
                        bytes.push_back(byte);
                    }
                }
                else
                {
                    bytes.push_back(0x48);
                    bytes.push_back(0xC7);

                    //bytes.push_back(0xBA); // Can have something to do with r8-
                    uint8_t byte = 0x00;
                    byte |= (1 << 7);
                    byte |= (1 << 6);
                    reg_to_bin((size_t)dst, byte, 2);
                    bytes.push_back(byte);
                }
            }

            bytes.push_back((src >> 0) & 0xFF);
            bytes.push_back((src >> 8) & 0xFF);
            bytes.push_back((src >> 16) & 0xFF);
            bytes.push_back((src >> 24) & 0xFF);

            return bytes;
        }

        template <Reg64 dst>
        static std::vector<uint8_t> GetBytes(std::string src, size_t value, int32_t offset = -1)
        {
            movDebug = "mov qword " + reg_to_string(dst) + ", " + src + "\n";

            if (offset != -1)
                movDebug = "mov qword [" + reg_to_string(dst) + "-" + std::to_string(offset) + "], " + src + "\n";

            std::vector<uint8_t> bytes;

            bytes.push_back(0b01001000);
            bytes.push_back(0xB8);
            //bytes.push_back(0xC7);

            //uint8_t byte = 0x00;
            //byte |= (1 << 6);
            //reg_to_bin(dst, byte, 2);
            //bytes.push_back(byte);

            //bytes.push_back(-offset);

            Int64ToBytes conv = { 0 };
            conv.number = value;

            bytes.push_back(conv.bytes[0]);
            bytes.push_back(conv.bytes[1]);
            bytes.push_back(conv.bytes[2]);
            bytes.push_back(conv.bytes[3]);
            bytes.push_back(conv.bytes[4]);
            bytes.push_back(conv.bytes[5]);
            bytes.push_back(conv.bytes[6]);
            bytes.push_back(conv.bytes[7]);

            //uint8_t byte = 0x00;
            //byte |= (1 << 6);
            //reg_to_bin(dst, byte, 2);
            //bytes.push_back(byte);

            //if (offset != -1)
            //    bytes.push_back(-offset);

            return bytes;
        }

        // Default to r64_rm64_mov
        template <Reg64 dst, Reg64 src, bool dst_mem = false>
        static std::vector<uint8_t> GetBytes(int32_t offset = -1, bool mem = false)
        {
            std::vector<uint8_t> bytes;
            if (mem)
            {
                // Use lea instead
                bytes = AsmLea<Reg64>::GetBytes<dst, src>(offset);
                movDebug = AsmLea<Reg64>::GetDebug();

                return bytes;
            }
            movDebug = "mov qword " + reg_to_string(dst) + ", " + reg_to_string(src) + "\n";

            if (dst_mem)
            {
                if (offset != -1 && offset > 0)
                    movDebug = "mov qword [" + reg_to_string(dst) + "-" + std::to_string(offset) + "], " + reg_to_string(src) + "\n";
                else if (offset != -1 && offset < 0)
                    movDebug = "mov qword [" + reg_to_string(dst) + "+" + std::to_string(-offset) + "], " + reg_to_string(src) + "\n";

                // rm64_r64_mov

                if ((size_t)src > 7)
                    bytes.push_back(0b01001100);
                else if ((size_t)dst > 7)
                    bytes.push_back(0b01001001);
                else
                    bytes.push_back(0b01001000);
                bytes.push_back(0x89);

                uint8_t byte = 0x00;
                byte |= (1 << 6);

                if (offset != -1)
                {
                    reg_to_bin((size_t)src, byte, 5);
                    reg_to_bin((size_t)dst, byte, 2);
                    bytes.push_back(byte);
                    bytes.push_back(-offset);
                }
                else
                {
                    byte |= (1 << 7);
                    reg_to_bin((size_t)src, byte, 5);
                    reg_to_bin((size_t)dst, byte, 2);
                    bytes.push_back(byte);
                }
            }
            else
            {
                // r64_rm64_mov

                if (offset != -1 && offset > 0)
                    movDebug = "mov qword " + reg_to_string(dst) + ", [" + reg_to_string(src) + "-" + std::to_string(offset) + "]\n";
                else if (offset != -1 && offset < 0)
                    movDebug = "mov qword " + reg_to_string(dst) + ", [" + reg_to_string(src) + "+" + std::to_string(-offset) + "]\n";

                if ((size_t)dst > 7 || (size_t)src > 7)
                    bytes.push_back(0b01001100);
                else
                    bytes.push_back(0b01001000);
                bytes.push_back(0x8B);

                uint8_t byte = 0x00;
                //byte |= (1 << 7);
                byte |= (1 << 6);
                reg_to_bin((size_t)dst, byte, 5);
                reg_to_bin((size_t)src, byte, 2);
                bytes.push_back(byte);

                if (offset != -1)
                {
                    bytes.push_back(-offset);
                }
            }

            return bytes;
        }
    };

    template <>
    struct AsmMov<4> : public AsmMovBase<4>
    {
        // Default to r32_rm32_mov
        template <Reg32 dst, Reg32 src, bool dst_mem = false>
        static std::vector<uint8_t> GetBytes(int32_t offset = -1, bool mem = false)
        {
            std::vector<uint8_t> bytes;

            if (mem)
            {
                // Use lea instead
                bytes = AsmLea<Reg32>::GetBytes<dst, src>(offset);
                movDebug = AsmLea<Reg32>::GetDebug();

                return bytes;
            }

            movDebug = "mov dword " + reg_to_string(dst) + ", " + reg_to_string(src) + "\n";

            if (dst_mem)
            {
                if (offset != -1)
                {
                    if (offset < 0)
                        movDebug = "mov dword [" + reg_to_string(dst) + "+" + std::to_string(-offset) + "], " + reg_to_string(src) + "\n";
                    else if (offset > 0)
                        movDebug = "mov dword [" + reg_to_string(dst) + "-" + std::to_string(offset) + "], " + reg_to_string(src) + "\n";
                }

                // rm32_r32_mov

                if ((size_t)dst > 7 || (size_t)src > 7)
                    bytes.push_back(0x41);

                if (offset != -1)
                {
                    bytes.push_back(0x67);
                    bytes.push_back(0x89);
                    uint8_t byte = 0x00;
                    byte |= (1 << 6);
                    reg_to_bin((size_t)src, byte, 5);
                    reg_to_bin((size_t)dst, byte, 2);
                    bytes.push_back(byte);
                }
                else
                {

                    bytes.push_back(0x89);
                    uint8_t byte = 0x00;
                    byte |= (1 << 7);
                    byte |= (1 << 6);
                    reg_to_bin((size_t)src, byte, 5);
                    reg_to_bin((size_t)dst, byte, 2);
                    bytes.push_back(byte);
                }

                if (offset != -1)
                {
                    bytes.push_back(-offset);
                }
            }
            else
            {
                if (offset != -1)
                    movDebug = "mov dword " + reg_to_string(dst) + ", [" + reg_to_string(src) + "-" + std::to_string(offset) + "]\n";

                // r32_rm32_mov

                bytes.push_back(0x67);

                if ((size_t)dst > 7 || (size_t)src > 7)
                    bytes.push_back(0x44);

                bytes.push_back(0x8B);
                uint8_t byte = 0x00;
                byte |= (1 << 6);
                reg_to_bin((size_t)dst, byte, 5);
                reg_to_bin((size_t)src, byte, 2);
                bytes.push_back(byte);

                if (offset != -1)
                {
                    bytes.push_back(-offset);
                }
            }

            return bytes;
        }

        template <Reg32 dst>
        static std::vector<uint8_t> GetBytes(int32_t src, int8_t offset_dst = -1)
        {
            std::vector<uint8_t> bytes;
            if (offset_dst != -1)
            {
                // rm_32_imm32
                if (offset_dst < 0)
                    movDebug = "mov dword [" + reg_to_string(dst) + " + " + std::to_string(-offset_dst) + "], " + std::to_string(src) + "\n";
                else if (offset_dst > 0)
                    movDebug = "mov dword [" + reg_to_string(dst) + " - " + std::to_string(offset_dst) + "], " + std::to_string(src) + "\n";

                bytes.push_back(0x67);
                bytes.push_back(0xC7);

                uint8_t byte = 0x00;
                byte |= (1 << 6);
                reg_to_bin((size_t)dst, byte, 2);
                bytes.push_back(byte);

                if (offset_dst != -1)
                {
                    if (offset_dst < 0) // Positive
                        bytes.push_back(0x24);
                    bytes.push_back(-offset_dst);
                }

                bytes.push_back((src >> 0) & 0xFF);
                bytes.push_back((src >> 8) & 0xFF);
                bytes.push_back((src >> 16) & 0xFF);
                bytes.push_back((src >> 24) & 0xFF);
            }
            else
            {
                movDebug = "mov dword " + reg_to_string(dst) + ", " + std::to_string(src) + "\n";

                uint8_t byte = 0xB8 + ((size_t)dst);

                if ((size_t)dst > 7)
                {
                    bytes.push_back(0x41);
                    byte -= 8;
                }

                bytes.push_back(byte);
                bytes.push_back((src >> 0) & 0xFF);
                bytes.push_back((src >> 8) & 0xFF);
                bytes.push_back((src >> 16) & 0xFF);
                bytes.push_back((src >> 24) & 0xFF);
            }

            return bytes;
        }

        static std::vector<uint8_t> GetBytes(Reg32 dst, int32_t src, int8_t offset_dst = -1)
        {
            std::vector<uint8_t> bytes;
            if (offset_dst != -1)
            {
                // rm_32_imm32
                movDebug = "mov dword [" + reg_to_string(dst) + " - " + std::to_string(offset_dst) + "], " + std::to_string(src) + "\n";

                bytes.push_back(0x67);
                bytes.push_back(0xC7);

                uint8_t byte = 0x00;
                byte |= (1 << 6);
                reg_to_bin((size_t)dst, byte, 2);
                bytes.push_back(byte);

                if (offset_dst != -1)
                {
                    bytes.push_back(-offset_dst);
                }

                bytes.push_back((src >> 0) & 0xFF);
                bytes.push_back((src >> 8) & 0xFF);
                bytes.push_back((src >> 16) & 0xFF);
                bytes.push_back((src >> 24) & 0xFF);
            }
            else
            {
                movDebug = "mov dword " + reg_to_string(dst) + ", " + std::to_string(src) + "\n";
            }

            return bytes;
        }
    };

    template <>
    struct AsmMov<1> : public AsmMovBase<1>
    {
        // Default to r8_rm8_mov
        template <Reg8 dst, Reg8 src, bool dst_mem = false>
        static std::vector<uint8_t> GetBytes(int32_t offset = 0)
        {
            std::vector<uint8_t> bytes;
            movDebug = "mov byte " + reg_to_string(dst) + ", " + reg_to_string(src) + "\n";

            if (dst_mem)
            {
                // rm8_r8_mov
            }
            else
            {
                // r8_rm8_mov
            }

            return bytes;
        }

    };
}
