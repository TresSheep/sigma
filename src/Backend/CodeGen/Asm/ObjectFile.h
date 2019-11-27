#pragma once

#include <string>
#include <fstream>
#include "AsmContext.h"
#include "Registers.h"
#ifdef WINDOWS
#include <Backend/OutputFormats/PE/Section.h>
#include <Backend/OutputFormats/PE/PE.h>
#include <Backend/Debug/CodeView/CodeView.h>
using namespace Backend::OutputFormats::PE;
#endif

namespace Backend::CodeGen::Asm
{
#ifdef WINDOWS
    typedef OutputFormats::PE::Section Section;
    typedef OutputFormats::PE::ImageSectionFlag SectionFlags;
    typedef OutputFormats::PE::Symbol Symb;
    typedef OutputFormats::PE::AuxSectionDefinition AuxSectionDef;
    typedef OutputFormats::PE::AuxSymbolFilename AuxSymbolFile;
    typedef OutputFormats::PE::FileHeader FileHeader;
    typedef OutputFormats::PE::Relocation FormatRelocation;
#endif

    template <typename T>
    class ObjectFile
    {
    public:
        ObjectFile(std::string_view filename, bool debug);
        ~ObjectFile();

        void GetContextInfo(AsmContext& con);
        T GetFormat()
        {
            return m_format;
        }

        void Save();

    private:
        Section CreateTextSection();
        Section CreateDataSection();

        T m_format;
        std::string m_filename;
        bool m_debug;

        std::string m_content;
    };
}

#include "ObjectFile.inl"