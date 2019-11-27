#pragma once

#include <vector>
#include <string>

namespace Backend::CodeGen::Asm::Command
{

    template <typename Type>
    struct AsmPopBase
    {
        static uint8_t GetByte()
        {
            return 0;
        }

        static std::string GetDebug()
        {
            return popDebug;
        }

    protected:
        static std::string popDebug;
    };

    template <typename Type>
    std::string AsmPopBase<Type>::popDebug = "";

    template <typename Type>
    struct AsmPop : public AsmPopBase<Type>
    {
    };

    template <>
    struct AsmPop<Reg64> : public AsmPushBase<Reg64>
    {
        template <Reg64 reg>
        static uint8_t GetByte()
        {
            popDebug = "pop " + reg_to_string(reg) + "\n";
            return 0;
        }
    };
}
