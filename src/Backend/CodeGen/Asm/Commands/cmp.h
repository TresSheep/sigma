#pragma once

#include <vector>
#include <string>
#include "../Registers.h"

namespace Backend::CodeGen::Asm::Command
{
    template <size_t Size>
    struct AsmCmpBase
    {
        static std::vector<uint8_t> GetBytes();

        static std::string GetDebug()
        {
            return cmpDebug;
        }

    protected:
        static std::string cmpDebug;
    };

    template <size_t Size>
    std::string AsmCmpBase<Size>::cmpDebug = "";

    template <size_t Type>
    struct AsmCmp : public AsmCmpBase<Type> { };

    template <>
    struct AsmCmp<8> : public AsmCmpBase<8>
    {
        template <Reg64 lhs, typename INT8TYPE = int8_t>
        static std::vector<uint8_t> GetBytes(INT8TYPE rhs)
        {
            cmpDebug = "cmp qword " + reg_to_string(lhs) + ", " + std::to_string(rhs) + "\n";
            std::vector<uint8_t> bytes;
            bytes.push_back(0x48);
            bytes.push_back(0x83);

            // the rest

            return bytes;
        }

        template <Reg64 lhs, Reg64 rhs, typename INT8TYPE = int8_t>
        static std::vector<uint8_t> GetBytes(INT8TYPE val)
        {
            cmpDebug = "cmp byte [" + reg_to_string(lhs) + "+" + reg_to_string(rhs) + "], " + std::to_string(val) + "\n";
            std::vector<uint8_t> bytes;
            bytes.push_back(0x80);
            uint8_t byte = 0x3C;

            bytes.push_back(byte);

            byte = 0x00;
            reg_to_bin((size_t)rhs, byte, 5);
            reg_to_bin((size_t)lhs, byte, 2);
            bytes.push_back(byte);
            bytes.push_back(val);

            // the rest

            return bytes;
        }
    };

    template <>
    struct AsmCmp<4> : public AsmCmpBase<4>
    {
        template <Reg32 dst, Reg32 src, bool is_mem = false, bool dst_mem = false>
        static std::vector<uint8_t> GetBytes(size_t value)
        {
            if (is_mem)
            {
                cmpDebug = "cmp byte [" + reg_to_string(dst) + "+" + reg_to_string(src) + "], " + std::to_string(value) + "\n";
            }
            std::vector<uint8_t> bytes;

            return bytes;
        }

        template <Reg32 dst, typename INTTYPE = int8_t>
        static std::vector<uint8_t> GetBytes(INTTYPE src)
        {
            std::vector<uint8_t> bytes;
            switch (sizeof(INTTYPE))
            {
            case 1:
            {
                // Byte
                cmpDebug = "cmp dword " + reg_to_string(dst) + ", " + std::to_string(src) + "\n";

                bytes.push_back(0x83);
                uint8_t byte = 0x00;
                byte |= (1 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (1 << 3);
                reg_to_bin((size_t)dst, byte, 2);
                bytes.push_back(byte);
                bytes.push_back(src);
            } break;
            case 4:
            {
                // Dword
                cmpDebug = "cmp dword " + reg_to_string(dst) + ", " + std::to_string(src) + "\n";

                bytes.push_back(0x81);
                uint8_t byte = 0x00;
                byte |= (1 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (1 << 3);
                reg_to_bin((size_t)dst, byte, 2);
                bytes.push_back(byte);

                bytes.push_back((src >> 0) & 0xFF);
                bytes.push_back((src >> 8) & 0xFF);
                bytes.push_back((src >> 16) & 0xFF);
                bytes.push_back((src >> 24) & 0xFF);

            } break;
            case 8:
                // Qword
                break;
            }

            return bytes;
        }
    };

    template <>
    struct AsmCmp<1> : public AsmCmpBase<1>
    {
        template <Reg8 dst, Reg8 src, bool is_mem = false, bool dst_mem = false>
        static std::vector<uint8_t> GetBytes(size_t value)
        {
            if (is_mem)
            {
                cmpDebug = "cmp byte [" + reg_to_string(dst) + "+" + reg_to_string(src) + "], " + std::to_string(value) + "\n";
            }
            std::vector<uint8_t> bytes;

            return bytes;
        }
    };

//    // /7 means 111 = 7
//    static std::vector<uint8_t> _rm32_imm32_cmp(std::vector<uint8_t> lhs, std::vector<uint8_t> rhs, std::string& debug)
//    {
//#ifdef DEBUG
//        debug = "cmp dword ";
//#endif
//        std::vector<uint8_t> vec;
//        vec.push_back(0x81);
//
//        uint8_t byte = 0x00;
//        byte |= (1 << 6);
//        byte |= (1 << 5);
//        byte |= (1 << 4);
//        byte |= (1 << 3);
//        register_to_binary(RBP, byte, 2);
//        vec.push_back(byte);
//
//        vec.push_back(lhs[1]);
//
//        vec.push_back(rhs[0]);
//        vec.push_back(rhs[1]);
//        vec.push_back(rhs[2]);
//        vec.push_back(rhs[3]);
//
//        return vec;
//    }
//
//    // /7 means 111 = 7
//    static std::vector<uint8_t> _rm32_imm8_cmp(_32BitRegisters reg, size_t offset, int8_t value, std::string& debug)
//    {
//#ifdef DEBUG
//        debug = "\ncmp " + register_to_string(reg) + ", " + std::to_string(value);
//#endif
//        std::vector<uint8_t> vec;
//        vec.push_back(0x83);
//        uint8_t byte;
//        byte |= (1 << 6);
//        byte |= (1 << 5);
//        byte |= (1 << 4);
//        byte |= (1 << 3);
//        register_to_binary(reg, byte, 2);
//        vec.push_back(byte);
//
//        vec.push_back(value);
//
//        return vec;
//    }
//
//    // /7 means 111 = 7
//    static std::vector<uint8_t> _rm32_imm8_cmp(std::unique_ptr<AsmVariable> var, int8_t value, std::string& debug)
//    {
//        std::vector<uint8_t> bytes = var->GetTextBytes();
//#ifdef DEBUG
//        debug = "\ncmp " + var->ToString(), + ", " + std::to_string(value);
//#endif
//        std::vector<uint8_t> vec;
//        vec.push_back(0x83);
//        uint8_t byte;
//        byte = bytes[0];
//        byte |= (1 << 6);
//        byte |= (1 << 5);
//        byte |= (1 << 4);
//        byte |= (1 << 3);
//        vec.push_back(byte);
//
//
//        vec.push_back(value);
//
//        return vec;
//    }
//
//    typedef struct _AsmCmp : public AsmValue
//    {
//    private:
//        std::string debug;
//    public:
//        std::unique_ptr<AsmValue> lhs;
//        std::unique_ptr<AsmValue> rhs;
//
//        std::string ToString()
//        {
//            return debug;
//        }
//
//        std::string DataToString()
//        {
//            return "";
//        }
//
//        std::vector<uint8_t> GetTextBytes()
//        {
//            std::vector<uint8_t> bytes;
//            if (auto l = dynamic_cast<AsmBytes*>(lhs.get()))
//            {
//                bytes.insert(bytes.end(), l->bytes.begin(), l->bytes.end());
//            }
//            if (auto r = dynamic_cast<AsmBytes*>(rhs.get()))
//            {
//                bytes.insert(bytes.end(), r->bytes.begin(), r->bytes.end());
//            }
//
//            if (auto l = dynamic_cast<AsmVariable*>(lhs.get()))
//            {
//            }
//            if (auto r = dynamic_cast<AsmVariable*>(rhs.get()))
//            {
//            }
//
//            debug += lhs->ToString();
//            debug += rhs->ToString();
//            return bytes;
//        }
//
//        std::vector<uint8_t> GetDataBytes()
//        {
//            std::vector<uint8_t> bytes;
//            return bytes;
//        }
//
//    } AsmCmp;
}