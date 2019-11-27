#pragma once

#include <fstream>

namespace Backend::OutputFormats::PE
{
    enum RelocationAMD
    {
        _ABSOLUTE = 0x0000,
        ADDR64 = 0x0001,
        ADDR32 = 0x0002,
        ADDR32NB = 0x0003,
        REL32 = 0x0004,
        REL32_1 = 0x0005,
        REL32_2 = 0x0006,
        REL32_3 = 0x0007,
        REL32_4 = 0x0008,
        REL32_5 = 0x0009,
        SECTION = 0x000A,
        SECREL = 0x000B,
        SECREL7 = 0x000C,
        TOKEN = 0x000D,
        SREL32 = 0x000E,
        PAIR = 0x000F,
        SSPAN32 = 0x0010
    };

    class Relocation
    {
    public:
        Relocation();
        ~Relocation();

        void SetVirtualAddress(int32_t virtualAddress);
        void SetSymbolTableIndex(int32_t symbolTableIndex);
        void SetType(int16_t type);
        
        void Write(std::ofstream& stream);

    private:
        int32_t m_virtualAddress;
        int32_t m_symbolTableIndex;
        int16_t m_type;
    };
}