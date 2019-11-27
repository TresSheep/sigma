#include "AsmWriter.h"
#include <memory>

namespace Backend::CodeGen::Asm
{
    AsmWriter::AsmWriter()
    {
#ifdef WINDOWS
        //InitPE();
#endif
    }

    AsmWriter::~AsmWriter()
    {
    }

    void AsmWriter::AddSymbolExternal(const std::string& name)
    {
        m_externals.push_back(name);
    }

    void AsmWriter::AddSymbolGlobal(const std::string& name, size_t offset)
    {
        m_globals.push_back(std::pair(name, offset));
    }

    void AsmWriter::AddSymbol(const std::string& name, size_t value, size_t section)
    {
        Symbol s;
        s.name = name;
        s.value = value;
        s.section = section;
        m_symbols.push_back(s);
    }

    void AsmWriter::AddRelocation(size_t va, const std::string& name, size_t type, size_t section)
    {
        Reloc r;
        r.va = va;
        r.name = name;
        r.type = type;
        r.section = section;
        m_relocs.push_back(r);
    }

    const std::vector<std::string>& AsmWriter::GetExternals()
    {
        return m_externals;
    }

    const std::vector<std::pair<std::string, size_t>>& AsmWriter::GetGlobals()
    {
        return m_globals;
    }

    const std::vector<Symbol>& AsmWriter::GetSymbols()
    {
        return m_symbols;
    }

    const std::vector<Reloc>& AsmWriter::GetRelocs()
    {
        return m_relocs;
    }

    void AsmWriter::generate_assembly()
    {
//        for (std::string line : m_lines)
//        {
//            m_file << line << std::endl;
//        }
//        m_file.close();
//
//        std::shared_ptr<OutputFormats::PE::Symbol> textSymbol = m_pe.GetSymbol(".text");
//        std::unique_ptr<OutputFormats::PE::AuxSectionDefinition> textAux(new OutputFormats::PE::AuxSectionDefinition());
//        textAux->SetLength(m_peTextSection->GetRawDataSize());
//        textAux->SetNumberOfRelocations(m_peTextSection->GetNumberOfRelocations() / 10);
//
//        textSymbol->AddAuxiliarySymbol(std::move(textAux));
//
//
//
//        std::shared_ptr<OutputFormats::PE::Symbol> dataSymbol = m_pe.GetSymbol(".data");
//
//        std::unique_ptr<OutputFormats::PE::AuxSectionDefinition> dataAux(new OutputFormats::PE::AuxSectionDefinition());
//        dataAux->SetLength(m_peDataSection->GetRawDataSize());
//        dataAux->SetNumberOfRelocations(0);
//
//        dataSymbol->AddAuxiliarySymbol(std::move(dataAux));
//
//        if (m_debug)
//        {
//#ifdef WINDOWS
//            Debug::CodeView::CodeView cv(m_pe);
//#endif
//        }
//
//        m_pe.Write();
    }

#ifdef WINDOWS
    //void AsmWriter::InitPE()
    //{
        //update_sections(2);
        //section(DATA);
        //section(TEXT);
        //m_externSection = 0;
        //m_globalSection = 1;
        //m_dataSection = 3;

        //OutputFormats::PE::FileHeader fileHeader;
        //fileHeader.SetMachine(OutputFormats::PE::AMD64); // x64

        //m_pe.SetFileHeader(fileHeader); // Set the file header

        //m_peDataSection = std::make_shared<OutputFormats::PE::Section>();
        //m_peDataSection->SetName(".data");
        //m_peDataSection->SetCharacteristics(OutputFormats::PE::CNT_INITIALIZED_DATA | OutputFormats::PE::ALIGN_4BYTES | OutputFormats::PE::MEM_WRITE | OutputFormats::PE::MEM_READ);

        //m_peTextSection = std::make_unique<OutputFormats::PE::Section>();
        //m_peTextSection->SetName(".text");
        //m_peTextSection->SetCharacteristics(
        //    OutputFormats::PE::ImageSectionFlag::ALIGN_16BYTES |
        //    OutputFormats::PE::ImageSectionFlag::CNT_CODE |
        //    OutputFormats::PE::ImageSectionFlag::MEM_EXECUTE |
        //    OutputFormats::PE::ImageSectionFlag::MEM_READ);

        //m_pe.AddSection(m_peDataSection); // Set data section (#1)
        //m_pe.AddSection(m_peTextSection); // Set text section (#2)

        //std::shared_ptr<OutputFormats::PE::Symbol> filenameSymbol(new OutputFormats::PE::Symbol());
        //filenameSymbol->SetSymbolName(".file");
        //filenameSymbol->SetSymbolValue(0);
        //filenameSymbol->SetSectionNumber(OutputFormats::PE::SYM_DEBUG);
        //filenameSymbol->SetSymbolType(0);
        //filenameSymbol->SetStorageClass((int16_t)OutputFormats::PE::ImageSymbolClass::FILE);
        //filenameSymbol->SetAuxiliaryCount(1);

        //m_pe.AddSymbol(filenameSymbol);

        //std::unique_ptr<OutputFormats::PE::AuxSymbolFilename> filenameAuxSymbol(new OutputFormats::PE::AuxSymbolFilename());
        //filenameAuxSymbol->SetFilename("test.asm");

        //filenameSymbol->AddAuxiliarySymbol(std::move(filenameAuxSymbol));

        //std::shared_ptr<OutputFormats::PE::Symbol> textSymbol(new OutputFormats::PE::Symbol());
        //textSymbol->SetSymbolName(".text");
        //textSymbol->SetSymbolValue(0);
        //textSymbol->SetSectionNumber(2);
        //textSymbol->SetSymbolType(0);
        //textSymbol->SetStorageClass((int16_t)OutputFormats::PE::ImageSymbolClass::STATIC);
        //textSymbol->SetAuxiliaryCount(1);

        //m_pe.AddSymbol(textSymbol);

        //std::shared_ptr<OutputFormats::PE::Symbol> dataSymbol(new OutputFormats::PE::Symbol());
        //dataSymbol->SetSymbolName(".data");
        //dataSymbol->SetSymbolValue(0);
        //dataSymbol->SetSectionNumber(1);
        //dataSymbol->SetStorageClass((int16_t)OutputFormats::PE::ImageSymbolClass::STATIC);
        //dataSymbol->SetAuxiliaryCount(1);

        //m_pe.AddSymbol(dataSymbol);
    //}
#endif
}
