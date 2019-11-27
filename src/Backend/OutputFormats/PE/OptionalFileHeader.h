#pragma once

#include <fstream>
#include <time.h>
#include <vector>
#include "ImageDataDirectory.h"

namespace Backend::OutputFormats::PE
{

    class OptionalFileHeader
    {
    public:
        OptionalFileHeader();
        ~OptionalFileHeader();

        void Write(std::ofstream& stream);
        const size_t GetSize();

        std::vector<ImageDataDirectory> m_directories;

        int16_t Magic;
        int8_t MajorLinkerVersion;
        int8_t MinorLinkerVersion;
        int32_t SizeOfCode;
        int32_t SizeOfInitializedData;
        int32_t SizeOfUninitializedData;
        int32_t AddressOfEntryPoint;
        int32_t BaseOfCode;
        int64_t ImageBase;
        int32_t SectionAlignment;
        int32_t FileAlignment;
        int16_t MajorOperatingSystemVersion;
        int16_t MinorOperatingSystemVersion;
        int16_t MajorImageVersion;
        int16_t MinorImageVersion;
        int16_t MajorSubsystemVersion;
        int16_t MinorSubsystemVersion;
        int32_t Win32VersionValue;
        int32_t SizeOfImage;
        int32_t SizeOfHeaders;
        int32_t CheckSum;
        int16_t Subsystem;
        int16_t DllCharacteristics;
        int64_t SizeOfStackReserve;
        int64_t SizeOfStackCommit;
        int64_t SizeOfHeapReserve;
        int64_t SizeOfHeapCommit;
        int32_t LoaderFlags;
        int32_t NumberOfRvaAndSizes;


    };
}
