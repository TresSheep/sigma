#include "ObjectFile.h"

namespace Backend::CodeGen::Asm
{
    template <typename T>
    ObjectFile<T>::ObjectFile(std::string_view filename, bool debug) :
        m_format(filename, false), m_filename(filename), m_debug(debug)
    {
    }

    template <typename T>
    ObjectFile<T>::~ObjectFile()
    {
    }

    template <typename T>
    void ObjectFile<T>::GetContextInfo(AsmContext& con)
    {
        FileHeader fileHeader;
        fileHeader.SetMachine(AMD64);

        m_format.SetFileHeader(fileHeader);

        Symb filenameSymbol;
        filenameSymbol.SetSymbolName(".file");
        filenameSymbol.SetSymbolValue(0);
        filenameSymbol.SetSectionNumber(SYM_DEBUG);
        filenameSymbol.SetSymbolType(0);
        filenameSymbol.SetStorageClass((int8_t)ImageSymbolClass::FILE);
        filenameSymbol.SetAuxiliaryCount(1);

        AuxSymbolFile asf;
        std::string f = m_filename + ".asm";
        asf.SetFilename(f.c_str());

        filenameSymbol.AddAuxiliarySymbol(asf);

        m_format.AddSymbol(filenameSymbol);

        Section dataSection = CreateDataSection();
        Section textSection = CreateTextSection();

        std::vector<uint8_t> textBytes;
        std::vector<uint8_t> dataBytes;
        std::vector<uint8_t> debugBytes;
        
        std::string globalDebug;
        std::string textDebug;
        std::string dataDebug;

        AsmWriter writer;
        for (auto& func : con.GetFunctions())
        {
            func->SetPosition(textBytes.size());

            std::unique_ptr<Command::AsmValue> value = func->Asm(writer); // Add types
            textBytes.insert(textBytes.end(), value->textBytes.begin(), value->textBytes.end());
            dataBytes.insert(dataBytes.end(), value->dataBytes.begin(), value->dataBytes.end());
            debugBytes.insert(debugBytes.end(), value->debugBytes.begin(), value->debugBytes.end());
            globalDebug += value->globalDebug;
            textDebug += value->textDebug;
            dataDebug += value->dataDebug;
        }

        for (uint8_t byte : textBytes)
            textSection.AddRawData(byte);

        for (uint8_t byte : dataBytes)
            dataSection.AddRawData(byte);

        // RESOLVE WRITER DEPENDENCIES
        for (auto extrn : writer.GetExternals())
        {
            Symb symb;
            symb.SetSymbolName(extrn.c_str());
            symb.SetStorageClass((int8_t)ImageSymbolClass::EXTERNAL);
            
            m_format.AddSymbol(symb);
        }

        for (auto global : writer.GetGlobals())
        {
            Symb symb;
            symb.SetSymbolName(global.first.c_str());
            symb.SetSectionNumber(2);
            symb.SetSymbolValue(global.second);
            symb.SetStorageClass((int8_t)ImageSymbolClass::EXTERNAL);

            m_format.AddSymbol(symb);
        }

        for (auto symbol : writer.GetSymbols())
        {
            Symb symb;
            symb.SetSymbolName(symbol.name.c_str());
            symb.SetSectionNumber(symbol.section);
            symb.SetStorageClass((int8_t)ImageSymbolClass::STATIC);
            symb.SetSymbolValue(symbol.value);

            m_format.AddSymbol(symb);
        }

        // TEXT SYMBOL

        Symb textSymbol;
        textSymbol.SetSymbolName(".text");
        textSymbol.SetSymbolValue(0);
        textSymbol.SetSectionNumber(2);
        textSymbol.SetSymbolType(0);
        textSymbol.SetStorageClass((int8_t)ImageSymbolClass::STATIC);
        textSymbol.SetAuxiliaryCount(1);

        AuxSectionDef textAux;
        textAux.SetLength(textBytes.size());
        textAux.SetNumberOfRelocations(textSection.GetNumberOfRelocations() / 10);

        textSymbol.AddAuxiliarySymbol(textAux);

        m_format.AddSymbol(textSymbol);

        // DATA SYMBOL

        Symb dataSymbol;
        dataSymbol.SetSymbolName(".data");
        dataSymbol.SetSymbolValue(0);
        dataSymbol.SetSectionNumber(1);
        dataSymbol.SetSymbolType(0);
        dataSymbol.SetStorageClass((int8_t)ImageSymbolClass::STATIC);
        dataSymbol.SetAuxiliaryCount(1);

        AuxSectionDef dataAux;
        dataAux.SetLength(dataBytes.size());
        dataAux.SetNumberOfRelocations(0);

        dataSymbol.AddAuxiliarySymbol(dataAux);

        m_format.AddSymbol(dataSymbol);

        // RELOCATIONS
        for (auto reloc : writer.GetRelocs())
        {
            if (reloc.section == TEXT)
            {
                FormatRelocation rel;
                rel.SetSymbolTableIndex(m_format.GetRelocIndex(reloc.name));
                rel.SetVirtualAddress(reloc.va);
                rel.SetType(reloc.type);
                textSection.AddRelocation(rel);
            }
            if (reloc.section == DATA)
            {
                FormatRelocation rel;
                rel.SetSymbolTableIndex(m_format.GetRelocIndex(reloc.name));
                rel.SetVirtualAddress(reloc.va - 4);
                rel.SetType(reloc.type);
                dataSection.AddRelocation(rel);
            }
        }

        m_format.AddSection(dataSection);
        m_format.AddSection(textSection);

        m_content += globalDebug;
        m_content += "\nsection .data\n";
        m_content += dataDebug;
        m_content += "\nsection .text\n";
        m_content += textDebug;
    }

    template <typename T>
    void ObjectFile<T>::Save()
    {
        if (m_debug)
        {
#ifdef WINDOWS

            // .debug$S

            Debug::CodeView::DebugSectionS section;

            std::string str = "B:\\eplus\\test\\src\\test.asm";
            section.AddStringToStringTable(str);
            section.AddFileCheckSum();
            section.SetLineNumbers(1);
            section.AddLine(8);
            section.AddObjectFileName(m_filename);
            section.AddCompileFlag("eplus");
            section.AddFunction("main");

            auto sec = section.GetSection();

            Symb debugSymbol;
            debugSymbol.SetSymbolName(".debug$S");
            debugSymbol.SetSymbolValue(0);
            debugSymbol.SetSectionNumber(3);
            debugSymbol.SetSymbolType(0);
            debugSymbol.SetStorageClass((int8_t)ImageSymbolClass::STATIC);
            debugSymbol.SetAuxiliaryCount(1);

            AuxSectionDef debugAux;
            debugAux.SetLength(sec.GetRawDataSize());
            debugAux.SetNumberOfRelocations(0); // Temp

            debugSymbol.AddAuxiliarySymbol(debugAux);

            m_format.AddSymbol(debugSymbol);

            m_format.AddSection(sec);

            // .debug$T

            //Debug::CodeView::DebugSectionT section;

            //auto secT = section.GetSection();

            //std::unique_ptr<Symb> debugTSymbol(new Symb());
            //debugTSymbol->SetSymbolName(".debug$T");
            //debugTSymbol->SetSymbolValue(0);
            //debugTSymbol->SetSectionNumber(4);
            //debugTSymbol->SetSymbolType(0);
            //debugTSymbol->SetStorageClass((int8_t)ImageSymbolClass::STATIC);
            //debugTSymbol->SetAuxiliaryCount(1);

            //std::unique_ptr<AuxSectionDef> debugTAux(new AuxSectionDef());
            //debugTAux->SetLength(secT.GetRawDataSize());
            //debugTAux->SetNumberOfRelocations(0); // Temp

            //debugTSymbol->AddAuxiliarySymbol(std::move(debugTAux));

            //m_format.AddSymbol(std::move(debugTSymbol));

            //m_format.AddSection(secT);
#endif
        }

        m_format.Write();

#ifdef DEBUG
        std::ofstream debug_stream(m_filename + ".asm");
        debug_stream << m_content;
        debug_stream.close();
#endif
    }

    template <typename T>
    Section ObjectFile<T>::CreateTextSection()
    {
        // ALL SECTIONS MUST HAVE THE SAME FUNCTIONS
        Section section;
        section.SetName(".text");
        section.SetCharacteristics(
            SectionFlags::ALIGN_16BYTES |
            SectionFlags::CNT_CODE |
            SectionFlags::MEM_EXECUTE |
            SectionFlags::MEM_READ
        );

        return section;
    }

    template <typename T>
    Section ObjectFile<T>::CreateDataSection()
    {
        Section section;
        section.SetName(".data");
        section.SetCharacteristics(
            SectionFlags::CNT_INITIALIZED_DATA |
            SectionFlags::ALIGN_4BYTES |
            SectionFlags::MEM_WRITE |
            SectionFlags::MEM_READ
        );

        return section;
    }
}