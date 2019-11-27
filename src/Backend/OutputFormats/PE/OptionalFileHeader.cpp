#include "OptionalFileHeader.h"

namespace Backend::OutputFormats::PE
{
    OptionalFileHeader::OptionalFileHeader() :
        Magic(0x20B), MajorLinkerVersion(0), MinorLinkerVersion(0), SizeOfCode(0), SizeOfInitializedData(0), SizeOfUninitializedData(0), AddressOfEntryPoint(0),
        BaseOfCode(0), ImageBase(0), SectionAlignment(0), FileAlignment(0), MajorOperatingSystemVersion(0), MinorOperatingSystemVersion(0), MajorImageVersion(0),
        MinorImageVersion(0), MajorSubsystemVersion(0), MinorSubsystemVersion(0), Win32VersionValue(0), SizeOfImage(0), SizeOfHeaders(0), CheckSum(0), Subsystem(0),
        DllCharacteristics(0), SizeOfStackReserve(0), SizeOfStackCommit(0), SizeOfHeapReserve(0), SizeOfHeapCommit(0), LoaderFlags(0), NumberOfRvaAndSizes(0)
    {
    }

    OptionalFileHeader::~OptionalFileHeader()
    {
    }

    const size_t OptionalFileHeader::GetSize()
    {
        size_t size = 2 * sizeof(int8_t) + 9 * sizeof(int16_t) + 13 * sizeof(int32_t) + 5 * sizeof(int64_t);
        for (auto dir : m_directories)
        {
            size += ImageDataDirectory::Size;
        }

        return size;
    }

    void OptionalFileHeader::Write(std::ofstream& stream)
    {
        stream.write(reinterpret_cast<char*>(&Magic), sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&MajorLinkerVersion), sizeof(int8_t));
        stream.write(reinterpret_cast<char*>(&MinorLinkerVersion), sizeof(int8_t));
        stream.write(reinterpret_cast<char*>(&SizeOfCode), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&SizeOfInitializedData), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&SizeOfUninitializedData), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&AddressOfEntryPoint), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&BaseOfCode), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&ImageBase), sizeof(int64_t));
        stream.write(reinterpret_cast<char*>(&SectionAlignment), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&FileAlignment), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&MajorOperatingSystemVersion), sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&MinorOperatingSystemVersion), sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&MajorImageVersion), sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&MinorImageVersion), sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&MajorSubsystemVersion), sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&MinorSubsystemVersion), sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&Win32VersionValue), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&SizeOfImage), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&SizeOfHeaders), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&CheckSum), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&Subsystem), sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&DllCharacteristics), sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&SizeOfStackReserve), sizeof(int64_t));
        stream.write(reinterpret_cast<char*>(&SizeOfStackCommit), sizeof(int64_t));
        stream.write(reinterpret_cast<char*>(&SizeOfHeapReserve), sizeof(int64_t));
        stream.write(reinterpret_cast<char*>(&SizeOfHeapCommit), sizeof(int64_t));
        stream.write(reinterpret_cast<char*>(&LoaderFlags), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&NumberOfRvaAndSizes), sizeof(int32_t));

        for (auto dir : m_directories)
        {
            dir.Write(stream);
        }
    }
}
