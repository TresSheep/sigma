#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <Backend/OutputFormats/PE/PE.h>
#include <Backend/OutputFormats/PE/Section.h>
#include <Backend/OutputFormats/PE/Relocation.h>

namespace Backend::Debug::CodeView
{
#pragma pack(push, 1)
    struct FILEDATA
    {
        uint32_t offsetFileName;
        uint8_t cbChecksum;
        uint8_t ChecksumType;
    };
#pragma pack(pop)
    struct OBJNAMESYM
    {
        uint16_t recordLength;
        uint16_t recordType; // S_OBJNAME
        uint32_t signature;
        unsigned char name[1];
    };
    struct COMPILESYM
    {
        uint16_t recordLength; // Record length
        uint16_t recordType; // S_COMPILE2
        struct
        {
            unsigned long iLanguage : 8;
            unsigned long fEC : 1;
            unsigned long fNoDbgInfo : 1;
            unsigned long fLTCG : 1;
            unsigned long fNoDataAlign : 1;
            unsigned long fManagedPresent : 1;
            unsigned long fSecurityChecks : 1;
            unsigned long fHotPatch : 1;
            unsigned long fCVTCIL : 1;
            unsigned long fMSILModule : 1;
            unsigned long pad : 15; // reseerved, must be 0
        } flags;

        uint16_t machine;
        uint16_t verFEMajor; // Frontend major
        uint16_t verFEMinor;
        uint16_t verFEBuild;
        uint16_t verMajor;
        uint16_t verMinor;
        uint16_t verBuild;
        uint8_t verSt[1];
    };

    struct CV_PROCFLAGS
    {
        union
        {
            uint8_t bAll;
            uint8_t grfAll;
            struct
            {
                uint8_t CV_PFLAG_NOFPO : 1; // frame pointer present
                uint8_t CV_PFLAG_IN : 1; // interrupt return
                uint8_t CV_PFLAG_FAR : 1; // far return
                uint8_t CV_PFLAG_NEVER : 1; // function does not return
                uint8_t CV_PLFLAG_NOTREACHED : 1; // label isn't fallen into
                uint8_t CV_PFLAG_CUST_CALL : 1; // custom calling convention
                uint8_t CV_PFLAG_NOINLINE : 1; // function marked as noinline
                uint8_t CV_PFLAG_OPTDBGINFO : 1; // function has debug information for optimized code
            };
        };
    };

    struct LABELSYM32
    {
        uint16_t recordLength;
        uint16_t recordType;
        uint32_t offset;
        uint16_t seg;
        CV_PROCFLAGS flags;
        uint8_t name[1];
    };

    class DebugSectionS
    {
    public:
        DebugSectionS();
        ~DebugSectionS();

        void AddFileCheckSum();
        void AddObjectFileName(std::string_view filename);
        void AddCompileFlag(std::string_view name);
        void AddStringToStringTable(std::string_view str);
        void SetLineNumbers(size_t number);
        void AddLine(size_t num);
        void AddFunction(std::string_view name);

        OutputFormats::PE::Section GetSection();
        void Write(std::ofstream& stream);

    private:
        std::vector<uint8_t> m_bytes;
        std::vector<OutputFormats::PE::Relocation> m_relocations;
    };
}