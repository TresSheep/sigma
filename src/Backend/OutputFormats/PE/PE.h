#pragma once

// Class for generating an PE/COFF object file

#include "FileHeader.h"
#include "OptionalFileHeader.h"
#include "Symbol.h"
#include "Section.h"
#include "StringTable.h"
#include "Relocation.h"
#include <vector>
#include <memory>

namespace Backend::OutputFormats::PE
{
    class PE
    {
    public:
        PE(std::string_view filename, bool exe = false);
        ~PE();

        PE::PE(const PE& pe)
        {
            m_stream << pe.m_stream.rdbuf();
            m_fileHeader = pe.m_fileHeader;
            m_optionalFileHeader = pe.m_optionalFileHeader;
            m_sections.insert(m_sections.begin(), pe.m_sections.begin(), pe.m_sections.end());
        }

        void SetFileHeader(FileHeader fileHeader);
        void SetOptionalFileHeader(OptionalFileHeader optionalFileHeader);
        void AddSection(const Section& section);
        void AddSymbol(Symbol& symbol);
        size_t GetRelocIndex(std::string name);

        void AddRelocation(std::string name, size_t position, int16_t type, std::string sectionName);

        StringTable& GetStringTable();

        Symbol& GetSymbol(const std::string& name);
        std::vector<Section>& GetSections()
        {
            return m_sections;
        }

        void Write();

    private:
        std::ofstream m_stream;
        FileHeader m_fileHeader;
        OptionalFileHeader m_optionalFileHeader;
        std::vector<Symbol> m_symbols;
        std::vector<Section> m_sections;
        StringTable m_stringTable;
        std::string m_filename;
        bool m_exe;
    };
}