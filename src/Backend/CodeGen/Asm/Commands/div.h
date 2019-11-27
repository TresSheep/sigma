#pragma once

#include <vector>
#include <string>
#include "../Registers.h"
#include "mov.h"

namespace Backend::CodeGen::Asm::Command
{
    template <size_t Type>
    struct AsmDivBase
    {
        static std::vector<uint8_t> GetBytes();

        static std::string GetDebug()
        {
            return divDebug;
        }

    protected:
        static std::string divDebug;
    };

    template <size_t Type>
    std::string AsmDivBase<Type>::divDebug = "";

    template <size_t Type>
    struct AsmDiv : public AsmDivBase<Type> { };

    template <>
    struct AsmDiv<8> : public AsmDivBase<8>
    {
        static std::vector<uint8_t> GetBytes()
        {
        }
    };

    template <>
    struct AsmDiv<4> : public AsmDivBase<4>
    {
        template <Reg32 reg>
        static std::vector<uint8_t> GetBytes()
        {
            divDebug = "div " + reg_to_string(reg) + "\n";

            std::vector<uint8_t> bytes = { 0xF7, 0xF3 };

            return bytes;
        }
    };
}