#pragma once

#include <fstream>

namespace Backend::OutputFormats::PE
{
    typedef struct _ExportDirectoryTable
    {
        int32_t VirtualAddress = 0;
        int32_t Size = 0;

        int32_t ExportFlags = 0;
        int32_t Time = 0;
        int16_t MajorVersion = 0;
        int16_t MinorVersion = 0;
        int32_t NameRVA = 0;
        int32_t OrdinalBase = 0;
        int32_t AddressTableEntries = 0;
        int32_t NumberOfNamePointers = 0;
        int32_t ExportAddressTableRVA = 0;
        int32_t NamePointerRVA = 0;
        int32_t OrdinalTableRVA = 0;

        void Write(std::ofstream& stream)
        {
            stream.write(reinterpret_cast<char*>(&VirtualAddress), sizeof(int32_t));
            stream.write(reinterpret_cast<char*>(&Size), sizeof(int32_t));

            stream.write(reinterpret_cast<char*>(&ExportFlags), sizeof(int32_t));
            stream.write(reinterpret_cast<char*>(&Time), sizeof(int32_t));
            stream.write(reinterpret_cast<char*>(&MajorVersion), sizeof(int16_t));
            stream.write(reinterpret_cast<char*>(&MinorVersion), sizeof(int16_t));
            stream.write(reinterpret_cast<char*>(&NameRVA), sizeof(int32_t));
            stream.write(reinterpret_cast<char*>(&OrdinalBase), sizeof(int32_t));
            stream.write(reinterpret_cast<char*>(&AddressTableEntries), sizeof(int32_t));
            stream.write(reinterpret_cast<char*>(&NumberOfNamePointers), sizeof(int32_t));
            stream.write(reinterpret_cast<char*>(&ExportAddressTableRVA), sizeof(int32_t));
            stream.write(reinterpret_cast<char*>(&NamePointerRVA), sizeof(int32_t));
            stream.write(reinterpret_cast<char*>(&OrdinalTableRVA), sizeof(int32_t));
        }
    } ExportDirectoryTable;

    typedef struct _ImportDirectoryTable
    {
        int32_t VirtualAddress = 0;
        int32_t Size = 0;

        int32_t ImportLookupTable = 0;
        int32_t Time = 0;
        int32_t ForwarderChain = 0;
        int32_t NameRVA = 0;
        int32_t ImportAddressTable = 0;

        void Write(std::ofstream& stream)
        {
            stream.write(reinterpret_cast<char*>(&VirtualAddress), sizeof(int32_t));
            stream.write(reinterpret_cast<char*>(&Size), sizeof(int32_t));

            stream.write(reinterpret_cast<char*>(&ImportLookupTable), sizeof(int32_t));
            stream.write(reinterpret_cast<char*>(&Time), sizeof(int32_t));
            stream.write(reinterpret_cast<char*>(&ForwarderChain), sizeof(int32_t));
            stream.write(reinterpret_cast<char*>(&NameRVA), sizeof(int32_t));
            stream.write(reinterpret_cast<char*>(&ImportAddressTable), sizeof(int32_t));

        }
    } ImportDirectoryTable;

    class ImageDataDirectory
    {
    public:
        ImageDataDirectory();
        ~ImageDataDirectory();

        void Write(std::ofstream& stream);
        void SetExportTable(ExportDirectoryTable table);
        void SetImportTable(ImportDirectoryTable table);

        static const size_t Size = sizeof(int32_t) * 7 * 2; // Increase 2

    private:
        ImportDirectoryTable m_importTable;
        ExportDirectoryTable m_exportTable;
    };
}