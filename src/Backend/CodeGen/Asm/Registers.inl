#pragma once
#include "Registers.h"

template <typename T>
static std::string reg_to_string(T reg);

template <>
std::string reg_to_string<Reg64>(Reg64 reg)
{
    switch (reg)
    {
    case Reg64::RAX: return "rax";
    case Reg64::RBX: return "rbx";
    case Reg64::RCX: return "rcx";
    case Reg64::RDX: return "rdx";
    case Reg64::RSI: return "rsi";
    case Reg64::RDI: return "rdi";
    case Reg64::RBP: return "rbp";
    case Reg64::RSP: return "rsp";
    case Reg64::R8: return "r8";
    case Reg64::R9: return "r9";
    case Reg64::R10: return "r10";
    case Reg64::R11: return "r11";
    case Reg64::R12: return "r12";
    case Reg64::R13: return "r13";
    case Reg64::R14: return "r14";
    case Reg64::R15: return "r15";
    }

    return "";
}

template <>
std::string reg_to_string<Reg32>(Reg32 reg)
{
    switch (reg)
    {
    case Reg32::EAX: return "eax";
    case Reg32::EBX: return "ebx";
    case Reg32::ECX: return "ecx";
    case Reg32::EDX: return "edx";
    case Reg32::ESI: return "esi";
    case Reg32::EDI: return "edi";
    case Reg32::EBP: return "ebp";
    case Reg32::ESP: return "esp";
    case Reg32::R8D: return "r8d";
    case Reg32::R9D: return "r9d";
    case Reg32::R10D: return "r10d";
    case Reg32::R11D: return "r11d";
    case Reg32::R12D: return "r12d";
    case Reg32::R13D: return "r13d";
    case Reg32::R14D: return "r14d";
    case Reg32::R15D: return "r15d";
    }

    return "";
}

template <>
std::string reg_to_string<Reg16>(Reg16 reg)
{
    switch (reg)
    {
    case Reg16::AX: return "ax";
    case Reg16::BX: return "bx";
    case Reg16::CX: return "cx";
    case Reg16::DX: return "dx";
    case Reg16::DI: return "di";
    case Reg16::SI: return "si";
    case Reg16::BP: return "bp";
    case Reg16::SP: return "sp";
    }

    return "";
}

template <>
std::string reg_to_string<Reg8>(Reg8 reg)
{
    switch (reg)
    {
    case Reg8::AL: return "al";
    case Reg8::BL: return "bl";
    case Reg8::CL: return "cl";
    case Reg8::DL: return "dl";
    case Reg8::AH: return "ah";
    case Reg8::BH: return "bh";
    case Reg8::CH: return "ch";
    case Reg8::DH: return "dh";
    }

    return "";
}

static std::string reg_to_bin(size_t reg, uint8_t& byte, uint8_t start)
{
    switch (reg)
    {
    case (size_t)Reg64::RAX:
    {
        byte &= ~(1 << start);
        byte &= ~(1 << start - 1);
        byte &= ~(1 << start - 2);
        return "000";
    }
    case (size_t)Reg64::RBX:
    {
        byte &= ~(1 << start);
        byte |= (1 << start - 1);
        byte |= (1 << start - 2);
        return "011";
    }
    case (size_t)Reg64::RCX:
    {
        byte &= ~(1 << start);
        byte &= ~(1 << start - 1);
        byte |= (1 << start - 2);
        return "001";
    }
    case (size_t)Reg64::RDX:
    {
        byte &= ~(1 << start);
        byte |= (1 << start - 1);
        byte &= ~(1 << start - 2);
        return "010";
    }
    case (size_t)Reg64::RSI:
    {
        byte |= (1 << start);
        byte |= (1 << start - 1);
        byte &= ~(1 << start - 2);
        return "110";
    }
    case (size_t)Reg64::RDI:
    {
        byte |= (1 << start);
        byte |= (1 << start - 1);
        byte |= (1 << start - 2);
        return "111";
    }
    case (size_t)Reg64::RBP:
    {
        byte |= (1 << start);
        byte &= ~(1 << start - 1);
        byte |= (1 << start - 2);
        return "101";
    }
    case (size_t)Reg64::RSP:
    {
        byte |= (1 << start);
        byte &= ~(1 << start - 1);
        byte &= ~(1 << start - 2);
        return "100";
    }

    case (size_t)Reg64::R8:
    {
        byte &= ~(1 << start);
        byte &= ~(1 << start - 1);
        byte &= ~(1 << start - 2);
        return "000";
    }
    case (size_t)Reg64::R9:
    {
        byte &= ~(1 << start);
        byte &= ~(1 << start - 1);
        byte |= (1 << start - 2);
        return "001";
    }
    }

    return "";
}