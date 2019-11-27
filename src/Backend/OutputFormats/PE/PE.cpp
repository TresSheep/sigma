#include "PE.h"

namespace Backend::OutputFormats::PE
{
    PE::PE(std::string_view filename, bool exe) :
        m_filename(filename), m_fileHeader(), m_symbols(0), m_sections(0), m_exe(exe)
    {
        m_stringTable = StringTable();
    }

    PE::~PE()
    {
    }

    void PE::SetFileHeader(FileHeader fileHeader)
    {
        m_fileHeader = fileHeader;
    }

    void PE::SetOptionalFileHeader(OptionalFileHeader optionalFileHeader)
    {
        m_optionalFileHeader = optionalFileHeader;
    }

    void PE::AddSection(const Section& section)
    {
        m_sections.push_back(section);
    }

    void PE::AddSymbol(Symbol& symbol)
    {
        m_symbols.push_back(symbol);
    }

    size_t PE::GetRelocIndex(std::string name)
    {
        size_t i = 0;
        for (auto& symbol : m_symbols)
        {
            if (symbol.GetSymbolName().compare(name) == 0)
            {
                if (name.compare(".data") == 0)
                    return i - 1;
                return i;
            }

            if (symbol.GetSymbolName().compare(".data") == 0)
                i++;
            if (symbol.GetSymbolName().compare(".text") == 0)
                i++;

            i += symbol.GetAuxiliaryCount();
            i++;
        }

        return 0;
    }

    void PE::AddRelocation(std::string name, size_t position, int16_t type, std::string sectionName)
    {
        Relocation reloc;
        reloc.SetVirtualAddress(position - 4);
        reloc.SetSymbolTableIndex(GetRelocIndex(name));
        reloc.SetType(type);

        for (auto section : m_sections)
        {
            if (section.GetName().compare(sectionName) == 0)
            {
                section.AddRelocation(reloc);
            }
        }
    }

    StringTable& PE::GetStringTable()
    {
        return m_stringTable;
    }

    Symbol& PE::GetSymbol(const std::string& name)
    {
        for (auto& symbol : m_symbols)
        {
            if (symbol.GetSymbolName().compare(name) == 0)
                return symbol;
        }
    }

    void PE::Write()
    {
        m_stream = std::ofstream(m_filename, std::ios::binary);
        if (m_exe)
        {

            // PE dos stub from link.exe
            unsigned char stub[232] = {
    0x4D, 0x5A, 0x90, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00,
    0x0E, 0x1F, 0xBA, 0x0E, 0x00, 0xB4, 0x09, 0xCD, 0x21, 0xB8, 0x01, 0x4C, 0xCD, 0x21, 0x54, 0x68,
    0x69, 0x73, 0x20, 0x70, 0x72, 0x6F, 0x67, 0x72, 0x61, 0x6D, 0x20, 0x63, 0x61, 0x6E, 0x6E, 0x6F,
    0x74, 0x20, 0x62, 0x65, 0x20, 0x72, 0x75, 0x6E, 0x20, 0x69, 0x6E, 0x20, 0x44, 0x4F, 0x53, 0x20,
    0x6D, 0x6F, 0x64, 0x65, 0x2E, 0x0D, 0x0D, 0x0A, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xBB, 0xEA, 0x27, 0x05, 0xFF, 0x8B, 0x49, 0x56, 0xFF, 0x8B, 0x49, 0x56, 0xFF, 0x8B, 0x49, 0x56,
    0x7E, 0xE0, 0x4D, 0x57, 0xF4, 0x8B, 0x49, 0x56, 0x7E, 0xE0, 0x4A, 0x57, 0xFC, 0x8B, 0x49, 0x56,
    0x7E, 0xE0, 0x4C, 0x57, 0xDF, 0x8B, 0x49, 0x56, 0x7E, 0xE0, 0x48, 0x57, 0xFA, 0x8B, 0x49, 0x56,
    0x9A, 0xED, 0x48, 0x57, 0xFB, 0x8B, 0x49, 0x56, 0xFF, 0x8B, 0x48, 0x56, 0x17, 0x8B, 0x49, 0x56,
    0xC9, 0xE7, 0x4C, 0x57, 0x8F, 0x8B, 0x49, 0x56, 0xC9, 0xE7, 0xB6, 0x56, 0xFE, 0x8B, 0x49, 0x56,
    0xC9, 0xE7, 0x4B, 0x57, 0xFE, 0x8B, 0x49, 0x56, 0x52, 0x69, 0x63, 0x68, 0xFF, 0x8B, 0x49, 0x56,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            };


            m_stream.write(reinterpret_cast<char*>(&stub), 232);

            m_stream << "PE";
            m_stream << '\0';
            m_stream << '\0';
        }

        /* FILE HEADER */
        m_fileHeader.SetNumberOfSections(m_sections.size());
        size_t numberOfSymbols = 0;
        for (auto& symbol : m_symbols)
        {
            numberOfSymbols += symbol.GetAuxiliaryCount();
            numberOfSymbols++;
        }
        m_fileHeader.SetNumberOfSymbols(numberOfSymbols);

        size_t rawData = 0;
        for (auto section : m_sections)
        {
            rawData += section.GetRawDataSize();
            rawData += section.GetNumberOfRelocations();
        }
        m_fileHeader.SetPointerToSymbolTable(FileHeader::Size + (m_sections.size() * Section::Size) + rawData);
        if (m_exe)
            m_fileHeader.SetPointerToSymbolTable(0);

        if (m_exe)
        {
            m_fileHeader.SetSizeOfOptionalHeader(m_optionalFileHeader.GetSize());
            m_optionalFileHeader.SizeOfCode = m_sections.at(0).GetRawData().size(); // .text
            m_optionalFileHeader.SizeOfImage = m_optionalFileHeader.GetSize();
        }

        m_fileHeader.Write(m_stream);

        /* END FILE HEADER */

        /* OPTIONAL HEADER */

        if (m_exe)
            m_optionalFileHeader.Write(m_stream);

        /* END OPTIONAL HEADER*/

        /* SECTIONS */

        //rawData = 0;
        //int32_t pointerToRawData = FileHeader::Size + (m_sections.size() * Section::Size);

        size_t data = 0;
        size_t currentPosition = FileHeader::Size + (m_sections.size() * Section::Size);
        // SECTION
        for (auto section : m_sections)
        {
            currentPosition += data;

            section.SetPhysicalAddress(0);
            if (m_exe)
                section.SetPhysicalAddress(section.GetRawData().size());
            section.SetPointerToRawData(currentPosition);
            section.Write(m_stream);

            //section.WriteRawData(m_stream);
            //section.WriteRelocations(m_stream);

            data += section.GetRawDataSize();
            data += section.GetNumberOfRelocations();
        }

        //// Section
        //for (auto section : m_sections)
        //{
        //    section.SetPhysicalAddress(rawData);
        //    if (section.GetRawDataSize() != 0)
        //    {
        //        section.SetPointerToRawData(pointerToRawData);
        //    }
        //    section.Write(m_stream);
        //    pointerToRawData += section.GetRawDataSize();
        //    rawData += section.GetRawDataSize();
        //}
        // Write raw data
        for (auto section : m_sections)
        {
            if (section.GetRawDataSize() != 0)
            {
                section.WriteRawData(m_stream);
                section.WriteRelocations(m_stream);
            }
        }

        /* END SECTIONS */

        /* SYMBOLS */

        for (auto& symbol : m_symbols)
        {
            // Add offset from String Table
            if (symbol.NeedsAddressFromStringTable())
            {
                int32_t offset = m_stringTable.AddString(symbol.GetStringTableString()) + sizeof(int32_t);

                symbol.SetStringTableOffset(offset);
            }

            symbol.Write(m_stream);
        }

        /* END SYMBOLS */

        /* STRING TABLE */

        m_stringTable.Write(m_stream);

        /* END STRING TABLE */

        m_stream.close();
    }
}
