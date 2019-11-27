#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <bitset>
#include <sstream>
#include "Registers.h"

#ifdef WINDOWS
#include <Backend/OutputFormats/PE/PE.h>
#include <Backend/OutputFormats/PE/FileHeader.h>
#include <Backend/OutputFormats/PE/Section.h>
#include <Backend/OutputFormats/PE/Symbol.h>
#include <Backend/OutputFormats/PE/AuxSectionDefinition.h>
#include <Backend/OutputFormats/PE/AuxSymbolFilename.h>
#include <Backend/Debug/CodeView/CodeView.h>
#endif

namespace Backend::CodeGen::Asm
{
    enum RelocType
    {
        ADDR64 = 0x0001,
        ADDR32 = 0x0002,
        REL32 = 0x0004
    };

    enum SectionType
    {
        TEXT = 2,
        DATA = 1,
        _DEBUG_ = 3
    };

    struct Reloc
    {
        size_t va;
        std::string name;
        size_t type;
        size_t section;
    };

    struct Symbol
    {
        std::string name;
        size_t value;
        size_t section;
    };

    class AsmWriter
    {
    public:
        AsmWriter();
        ~AsmWriter();

        void AddSymbolExternal(const std::string& name);
        void AddSymbolGlobal(const std::string& name, size_t offset);
        void AddSymbol(const std::string& name, size_t value, size_t section);
        void AddRelocation(size_t va, const std::string& name, size_t type, size_t section);

        const std::vector<std::string>& GetExternals();
        const std::vector<std::pair<std::string, size_t>>& GetGlobals();
        const std::vector<Symbol>& GetSymbols();
        const std::vector<Reloc>& GetRelocs();

        void generate_assembly();
    private:
        std::vector<std::string> m_externals;
        std::vector<std::pair<std::string, size_t>> m_globals;

        std::vector<Symbol> m_symbols;

        std::vector<Reloc> m_relocs;
    };
}