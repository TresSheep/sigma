#pragma once

#include <fstream>
#include <time.h>

namespace Backend::OutputFormats::PE
{
    enum ImageFileMachine
    {
        UNKNOWN = 0x0, // The contents of this field are assumed to be applicable to any machine type
        AM33 = 0x1d3, // Matsushita AM33
        AMD64 = 0x8664, // x64
        ARM = 0x1c0, // ARM little endian
        ARM64 = 0xaa64, // ARM64 little endian
        ARMNT = 0x1c4, // ARM Thumb-2 little endian
        EBC = 0x3bc, // EFI byte code
        I386 = 0x14c, // Intel 386 or later processors and compatible processors
        IA64 = 0x200, // intel Itanium processor family
        M32R = 0x9041, // Mitsubishi M32R little endian
        MIPS16 = 0x266, // MIPS16
        MIPSFPU = 0x366, // MIPS with FPU
        MIPSFPU16 = 0x466, // MIPS16 with FPU
        POWERPC = 0x1f0, // Power PC little endian
        POWERPCFP = 0x1f1, // Power PC with floating point support
        R4000 = 0x166, // MIPS little endian
        RISCV32 = 0x5032, // RICS-V 32-bit address space
        RISCV64 = 0x5064, // RISC-V 64-bit address space
        RISCV128 = 0x5128, // RISC-V 128-bit address space
        SH3 = 0x1a2, // Hitachi SH3
        SH3DSP = 0x1a3, // Hitachi SH3 DSP
        SH4 = 0x1a6, // Hitachi SH4
        SH5 = 0x1a8, // Hitachi SH5
        THUMB = 0x1c2, // Thumb
        WCEMIPSV2 = 0x169 // MIPS little-endian WCE v2
    };

    enum ImageFileCharacteristics
    {
        RELOCS_STRIPPED = 0x0001,
        EXECUTABLE_IMAGE = 0x0002,
        LINE_NUMS_STRIPPED = 0x0004,
        LOCAL_SYMS_STRIPPED = 0x0008,
        AGGRESSIVE_WS_TRIM = 0x0010,
        LARGE_ADDRESS_AWARE = 0x0020,
        BYTES_REVERSED_LO = 0x0080,
        _32BIT_MACHINE = 0x0100,
        DEBUG_STRIPPED = 0x0200,
        REMOVABLE_RUN_FROM_SWAP = 0x0400,
        NET_RUN_FROM_SWAP = 0x0800,
        SYSTEM = 0x1000,
        DLL = 0x2000,
        UP_SYSTEM_ONLY = 0x4000,
        BYTES_REVERSED_HI = 0x8000
    };

    class FileHeader
    {
    public:
        FileHeader();
        ~FileHeader();

        void SetMachine(int16_t machine);
        void SetNumberOfSections(int16_t numberOfSections);
        void SetTimeDateStamp(int32_t timeDateStamp);
        void SetPointerToSymbolTable(int32_t pointerToSymbolTable);
        void SetNumberOfSymbols(int32_t numberOfSymbols);
        void SetSizeOfOptionalHeader(int16_t sizeOfOptionalHeader);
        void SetCharacteristics(int16_t characteristics);
        void Write(std::ofstream& stream);

        static const size_t Size = 4 * sizeof(int16_t) + 3 * sizeof(int32_t);

    private:
        int16_t m_machine;
        int16_t m_numberOfSections;
        int32_t m_timeDateStamp;
        int32_t m_pointerToSymbolTable;
        int32_t m_numberOfSymbols;
        int16_t m_sizeOfOptionalHeader;
        int16_t m_characteristics;
    };
}
