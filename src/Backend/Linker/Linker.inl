#pragma once
#include "Linker.h"

namespace Backend::Linker
{
    template <>
    void Linker<Backend::OutputFormats::PE::PE>::Write()
    {
        Backend::OutputFormats::PE::FileHeader fileHeader;
        fileHeader.SetMachine(Backend::OutputFormats::PE::AMD64);
        fileHeader.SetCharacteristics(Backend::OutputFormats::PE::EXECUTABLE_IMAGE);

        m_format->SetFileHeader(fileHeader);

        size_t sizeOfRawText = 0;
        std::vector<int8_t> textCode;
        for (auto file : m_files)
        {
            sizeOfRawText = file.GetSections().at(1).GetRawData().size();
            textCode.insert(textCode.begin(), file.GetSections().at(1).GetRawData().begin(), file.GetSections().at(1).GetRawData().end());
        }

        // Section .text
        Backend::OutputFormats::PE::Section textSection;
        textSection.SetName(".text");
        textSection.SetPhysicalAddress(sizeOfRawText); // Becomes Virtual size
        textSection.SetCharacteristics(CNT_CODE | MEM_EXECUTE | MEM_READ);
        for (auto byte : textCode)
            textSection.AddRawData(byte);

        m_format->AddSection(textSection);


        Backend::OutputFormats::PE::OptionalFileHeader optionalFileHeader;
        optionalFileHeader.ImageBase = 0x00400000;
        optionalFileHeader.SectionAlignment = 0x1000;
        optionalFileHeader.Subsystem = 3;
        optionalFileHeader.MajorLinkerVersion = 1;
        optionalFileHeader.FileAlignment = 0x200;
        optionalFileHeader.MajorOperatingSystemVersion = 0x06;
        optionalFileHeader.MajorSubsystemVersion = 0x06;
        optionalFileHeader.SizeOfStackReserve = 0x100000;
        optionalFileHeader.SizeOfStackCommit = 0x1000;
        optionalFileHeader.SizeOfHeapReserve = 0x100000;
        optionalFileHeader.SizeOfHeapCommit = 0x1000;
        optionalFileHeader.SizeOfHeaders = 0x400;
        optionalFileHeader.NumberOfRvaAndSizes = 2;
        optionalFileHeader.BaseOfCode = 0x1000;

        Backend::OutputFormats::PE::ExportDirectoryTable edt;
        Backend::OutputFormats::PE::ImportDirectoryTable idt;

        Backend::OutputFormats::PE::ImageDataDirectory dir;
        dir.SetExportTable(edt);
        dir.SetImportTable(idt);

        optionalFileHeader.m_directories.push_back(dir);

        m_format->SetOptionalFileHeader(optionalFileHeader);

        // Add sections

        m_format->Write();
    }

    template <typename OutputFormat>
    void Linker<OutputFormat>::AddLib(const std::string& lib)
    {
        m_libs.push_back(lib);
    }

    // START PE

    template <>
    Linker<Backend::OutputFormats::PE::PE>::Linker(std::string_view output)
    {
        m_format = std::make_unique<Backend::OutputFormats::PE::PE>(output, true);
    }

    template <>
    Linker<Backend::OutputFormats::PE::PE>::~Linker()
    {
    }

    // END PE
}