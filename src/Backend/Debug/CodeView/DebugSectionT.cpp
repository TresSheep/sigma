#include "DebugSectionT.h"

namespace Backend::Debug::CodeView
{
    DebugSectionT::DebugSectionT() :
        m_bytes(0)
    {
    }

    DebugSectionT::~DebugSectionT()
    {
    }

    OutputFormats::PE::Section DebugSectionT::GetSection()
    {
        OutputFormats::PE::Section section;
        section.SetName(".debug$T");
        section.SetCharacteristics(
            OutputFormats::PE::ImageSectionFlag::CNT_INITIALIZED_DATA |
            OutputFormats::PE::ImageSectionFlag::MEM_DISCARDABLE |
            OutputFormats::PE::ImageSectionFlag::ALIGN_1BYTES |
            OutputFormats::PE::ImageSectionFlag::MEM_READ
        );

        for (auto byte : m_bytes)
            section.AddRawData(byte);

        return section;
    }
}