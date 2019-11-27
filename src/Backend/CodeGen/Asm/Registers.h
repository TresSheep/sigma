#pragma once

#include <string>
#include <vector>

enum class Reg8 : size_t
{
    AL = 0,
    BL = 3,
    CL = 1,
    DL = 2,
    AH = 4,
    BH = 7,
    CH = 5,
    DH = 6
};

enum class Reg16
{
    AX = 0,
    BX = 3,
    CX = 1,
    DX = 2,
    DI = 7,
    SI,
    BP,
    SP
};

enum class Reg32 :size_t
{
    EAX = 0,
    ECX = 1,
    EDX = 2,
    EBX = 3,
    ESP = 4,
    EBP = 5,
    ESI = 6,
    EDI = 7,
    R8D = 8,
    R9D = 9,
    R10D = 10,
    R11D = 11,
    R12D = 12,
    R13D = 13,
    R14D = 14,
    R15D = 15,
};

enum class Reg64 : size_t
{
    RAX = 0,
    RCX = 1,
    RDX = 2,
    RBX = 3,
    RSP = 4,
    RBP = 5,
    RSI = 6,
    RDI = 7,
    R8 = 8,
    R9 = 9,
    R10 = 10,
    R11 = 11,
    R12 = 12,
    R13 = 13,
    R14 = 14,
    R15 = 15,
};

enum _Size
{
    BYTE,
    WORD,
    DWORD,
    QWORD
};

enum _Section
{
    TEXT,
    DATA,
    BSS
};

namespace Backend::CodeGen::Asm::Command
{

    struct AsmValue
    {
        size_t reg;
        int32_t offset = -1;
        std::vector<uint8_t> textBytes;
        std::vector<uint8_t> dataBytes;
        std::vector<uint8_t> debugBytes;
        std::string textDebug;
        std::string dataDebug;
        std::string globalDebug;
        size_t size;
    };
}

#include "Registers.inl"
