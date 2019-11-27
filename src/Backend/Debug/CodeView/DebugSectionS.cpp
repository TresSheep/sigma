#include "DebugSectionS.h"

namespace Backend::Debug::CodeView
{
    DebugSectionS::DebugSectionS() :
        m_bytes(0)
    {
    }

    DebugSectionS::~DebugSectionS()
    {
    }

    void DebugSectionS::AddFileCheckSum()
    {
        m_bytes.push_back(0x18);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);

        FILEDATA data;
        data.offsetFileName = 0x00000001;
        data.ChecksumType = 0x01;
        data.cbChecksum = 0x10;

        auto ptr = reinterpret_cast<uint8_t*>(&data);
        auto buffer = std::vector<uint8_t>{ ptr, ptr + sizeof(FILEDATA) };
        m_bytes.insert(m_bytes.end(), buffer.begin(), buffer.end());

        std::ofstream file("B:/eplus/test/src/test.asm");
        std::stringstream ss;
        ss << file.rdbuf();
        std::string str = "B:/eplus/test/src/test.asm";

        unsigned char result[16];
        //MD5((unsigned char*)str.c_str(), str.length(), result);

        m_bytes.push_back(result[0]);
        m_bytes.push_back(result[1]);
        m_bytes.push_back(result[2]);
        m_bytes.push_back(result[3]);
        m_bytes.push_back(result[4]);
        m_bytes.push_back(result[5]);
        m_bytes.push_back(result[6]);
        m_bytes.push_back(result[7]);
        m_bytes.push_back(result[8]);
        m_bytes.push_back(result[9]);
        m_bytes.push_back(result[10]);
        m_bytes.push_back(result[11]);
        m_bytes.push_back(result[12]);
        m_bytes.push_back(result[13]);
        m_bytes.push_back(result[14]);
        m_bytes.push_back(result[15]);

        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
    }

    void DebugSectionS::AddObjectFileName(std::string_view filename)
    {
        //      2           2             4          *
        // [ length ] [ S_OBJNAME ] [ Signature ] [ name ]
        //

        std::string str = filename.data();
        str += ".o";

        OBJNAMESYM obj;

        obj.recordLength = str.length() + sizeof(OBJNAMESYM) - 5;
        obj.recordType = 0x1101;
        obj.signature = 0x00;

        auto ptr = reinterpret_cast<uint8_t*>(&obj);
        auto buffer = std::vector<uint8_t>{ ptr, ptr + sizeof(OBJNAMESYM) - 4 };
        m_bytes.insert(m_bytes.end(), buffer.begin(), buffer.end());

        m_bytes.insert(m_bytes.end(), str.begin(), str.end());
        m_bytes.push_back(0x00);
    }

    void DebugSectionS::AddCompileFlag(std::string_view name)
    {
        COMPILESYM compile;

        compile.recordLength = name.length() + sizeof(COMPILESYM) - 1;
        compile.recordType = 0x1116; // S_COMPILE2

        compile.flags.iLanguage = 0x03;
        compile.flags.fEC = 0x00;
        compile.flags.fNoDbgInfo = 0x00;
        compile.flags.fLTCG = 0x00;
        compile.flags.fNoDataAlign = 0x00;
        compile.flags.fManagedPresent = 0x00;
        compile.flags.fSecurityChecks = 0x00;
        compile.flags.fHotPatch = 0x00;
        compile.flags.fCVTCIL = 0x00;
        compile.flags.fMSILModule = 0x00;
        compile.flags.pad = 0x00;

        compile.machine = 0xD0;
        compile.verFEMajor = 0x00;
        compile.verFEMinor = 0x00;
        compile.verFEBuild = 0x00;
        compile.verMajor = 0x08;
        compile.verMinor = 0x00;
        compile.verBuild = 50727;
        //compile.verSt[0] = 0x27;
        //compile.verSt[1] = 0xC6;

        auto ptr = reinterpret_cast<uint8_t*>(&compile);
        auto buffer = std::vector<uint8_t>{ ptr, ptr + sizeof(COMPILESYM) - 2 };
        m_bytes.insert(m_bytes.end(), buffer.begin(), buffer.end());

        m_bytes.insert(m_bytes.end(), name.begin(), name.end());

        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
    }

    void DebugSectionS::AddStringToStringTable(std::string_view str)
    {
        if (m_bytes.size() == 0)
        {
            // Create string table
            m_bytes.push_back(0x04);
            m_bytes.push_back(0x00);
            m_bytes.push_back(0x00);
            m_bytes.push_back(0x00);

            m_bytes.push_back(0xF3);
            m_bytes.push_back(0x00);
            m_bytes.push_back(0x00);
            m_bytes.push_back(0x00);
        }

        m_bytes.push_back(str.length() + 2);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);

        m_bytes.insert(m_bytes.end(), str.begin(), str.end());
        m_bytes.push_back(0x00);


        m_bytes.push_back(0xF4);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
    }

    void DebugSectionS::SetLineNumbers(size_t number)
    {
        m_bytes.push_back(0xF2);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x20);

        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);

        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);

        m_bytes.push_back((number >> 0) & 0xFF);
        m_bytes.push_back((number >> 8) & 0xFF);
        m_bytes.push_back((number >> 16) & 0xFF);
        m_bytes.push_back((number >> 24) & 0xFF);
        m_bytes.push_back((number >> 32) & 0xFF);
        m_bytes.push_back((number >> 40) & 0xFF);
        m_bytes.push_back((number >> 48) & 0xFF);
        m_bytes.push_back((number >> 56) & 0xFF);
    }

    void DebugSectionS::AddLine(size_t num)
    {
        m_bytes.push_back(0x01);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);

        m_bytes.push_back(0x14);

        m_bytes.push_back((num >> 56) & 0xFF);
        m_bytes.push_back((num >> 48) & 0xFF);
        m_bytes.push_back((num >> 40) & 0xFF);
        m_bytes.push_back((num >> 32) & 0xFF);
        m_bytes.push_back((num >> 24) & 0xFF);
        m_bytes.push_back((num >> 16) & 0xFF);
        m_bytes.push_back((num >> 8) & 0xFF);
        m_bytes.push_back((num >> 0) & 0xFF);

        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x80);

        m_bytes.push_back(0xF1);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);

        m_bytes.push_back(0x5E);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
    }

    void DebugSectionS::AddFunction(std::string_view name)
    {
        LABELSYM32 label;

        label.recordLength = name.length() + sizeof(LABELSYM32) - 2;
        label.recordType = 0x1105;
        label.offset = 0x00;
        label.seg = 0x00;

        auto ptr = reinterpret_cast<uint8_t*>(&label);
        auto buffer = std::vector<uint8_t>{ ptr, ptr + sizeof(LABELSYM32) - 2 };
        m_bytes.insert(m_bytes.end(), buffer.begin(), buffer.end());

        m_bytes.push_back(0x00);

        m_bytes.insert(m_bytes.end(), name.begin(), name.end());

        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
        m_bytes.push_back(0x00);
    }

    OutputFormats::PE::Section DebugSectionS::GetSection()
    {
        OutputFormats::PE::Section section;
        section.SetName(".debug$S");
        section.SetCharacteristics(
            OutputFormats::PE::ImageSectionFlag::CNT_INITIALIZED_DATA |
            OutputFormats::PE::ImageSectionFlag::MEM_DISCARDABLE |
            OutputFormats::PE::ImageSectionFlag::ALIGN_1BYTES |
            OutputFormats::PE::ImageSectionFlag::MEM_READ
        );

        for (auto byte : m_bytes)
            section.AddRawData(byte);

        for (auto reloc : m_relocations)
            section.AddRelocation(reloc);

        return section;
    }

    void DebugSectionS::Write(std::ofstream& stream)
    {
        for (auto byte : m_bytes)
            stream << byte;
    }
}