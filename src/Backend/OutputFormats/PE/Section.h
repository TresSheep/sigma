#pragma once

#include <fstream>
#include <vector>
#include <Backend/OutputFormats/PE/Relocation.h>
#include <cstring>

namespace Backend::OutputFormats::PE
{
    enum ImageSectionFlag
    {
        TYPE_NO_PAD = 0x00000008,
        CNT_CODE = 0x00000020,
        CNT_INITIALIZED_DATA = 0x00000040,
        CNT_UNINITIALIZED_DATA = 0x00000080,
        LNK_OTHER = 0x00000100,
        LNK_INFO = 0x00000200,
        LNK_REMOVE = 0x00000800,
        LNK_COMDAT = 0x00001000,
        GPREL = 0x00008000,
        MEM_PURGEABLE = 0x00020000,
        MEM_16BIT = 0x00020000,
        MEM_LOCKED = 0x00040000,
        MEM_PRELOAD = 0x00080000,
        ALIGN_1BYTES = 0x00100000,
        ALIGN_2BYTES = 0x00200000,
        ALIGN_4BYTES = 0x00300000,
        ALIGN_8BYTES = 0x00400000,
        ALIGN_16BYTES = 0x00500000,
        ALIGN_32BYTES = 0x00600000,
        ALIGN_64BYTES = 0x00700000,
        ALIGN_128BYTES = 0x00800000,
        ALIGN_256BYTES = 0x00900000,
        ALIGN_512BYTES = 0x00A00000,
        ALIGN_1024BYTES = 0x00B00000,
        ALIGN_2048BYTES = 0x00C00000,
        ALIGN_4096BYTES = 0x00D00000,
        ALIGN_8192BYTES = 0x00E00000,
        LNK_NRELOC_OVFL = 0x01000000,
        MEM_DISCARDABLE = 0x02000000,
        MEM_NOT_CACHED = 0x04000000,
        MEM_NOT_PAGED = 0x08000000,
        MEM_SHARED = 0x10000000,
        MEM_EXECUTE = 0x20000000,
        MEM_READ = 0x40000000,
        MEM_WRITE = 0x80000000
    };

    enum ImageSymbolTable
    {
        SYM_UNDEFINED = 0,
        SYM_ABSOLUTE = -1,
        SYM_DEBUG = -2
    };

    enum class ImageSymbolClass
    {
        END_OF_FUNCTION = -1,
        _NULL = 0,
        AUTOMATIC = 1,
        EXTERNAL = 2,
        STATIC = 3,
        REGISTER = 4,
        EXTERNAL_DEF = 5,
        LABEL = 6,
        UNDEFINED_LABEL = 7,
        MEMBER_OF_STRUCT = 8,
        ARGUMENT = 9,
        STRUCT_TAG = 10,
        MEMBER_OF_UNION = 11,
        UNION_TAG = 12,
        TYPE_DEFINITION = 13,
        UNDEFINED_STATIC = 14,
        ENUM_TAG = 15,
        MEMBER_OF_ENUM = 16,
        REGISTER_PARAM = 17,
        BIT_FIELD = 18,
        BLOCK = 100,
        FUNCTION = 100,
        END_OF_STRUCT = 102,
        FILE = 103,
        SECTION = 104,
        WEAK_EXTERNAL = 105,
        CLR_TOKEN = 107
    };

    class Section
    {
    public:
        Section();
        ~Section();

        Section::Section(const Section& s)
        {
            m_rawData.insert(m_rawData.begin(), s.m_rawData.begin(), s.m_rawData.end());
        }

        void SetName(const char* name); // Must shorter than 8 bytes
        void SetPhysicalAddress(int32_t physicalAddress);
        void SetVirtualAddress(int32_t virtualAddress);
        void SetSizeOfRawData(int32_t sizeOfRawData);
        void SetPointerToRawData(int32_t pointerToRawData);
        void SetPointerToRelocations(int32_t pointerToRelocations);
        void SetPointerToLinenumbers(int32_t pointerToLinenumbers);
        void SetNumberOfRelocations(int16_t numberOfRelocations);
        void SetNumberOfLinenumbers(int16_t numberOfLinenumbers);
        void SetCharacteristics(int32_t characteristics);

        void AddRawData(int8_t byte);
        size_t GetRawDataSize();
        std::vector<int8_t>& GetRawData()
        {
            return m_rawData;
        }

        void AddRelocation(Relocation& relocation);
        size_t GetNumberOfRelocations();

        void Write(std::ofstream& stream);
        void WriteRawData(std::ofstream& stream);
        void WriteRelocations(std::ofstream& stream);

        std::string GetName();

        static const size_t Size = sizeof(int8_t[8]) + 7 * sizeof(int32_t) + 2 * sizeof(int16_t);

    private:
        int8_t m_name[8];
        int32_t m_physicalAddress;
        int32_t m_virtualAddress;
        int32_t m_sizeOfRawData;
        int32_t m_pointerToRawData;
        int32_t m_pointerToRelocations;
        int32_t m_pointerToLinenumbers;
        int16_t m_numberOfRelocations;
        int16_t m_numberOfLinenumbers;
        int32_t m_characteristics;

        std::vector<int8_t> m_rawData;

        std::vector<Relocation> m_relocations;
    };
}
