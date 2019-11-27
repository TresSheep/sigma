#include "Relocation.h"
#include <fstream>

namespace Backend::OutputFormats::PE
{
    Relocation::Relocation() :
        m_virtualAddress(0), m_symbolTableIndex(0), m_type(0)
    {
    }

    Relocation::~Relocation()
    {
    }

    void Relocation::SetVirtualAddress(int32_t virtualAddress)
    {
        m_virtualAddress = virtualAddress;
    }

    void Relocation::SetSymbolTableIndex(int32_t symbolTableIndex)
    {
        m_symbolTableIndex = symbolTableIndex;
    }

    void Relocation::SetType(int16_t type)
    {
        m_type = type;
    }

    void Relocation::Write(std::ofstream& stream)
    {
        stream.write(reinterpret_cast<char*>(&m_virtualAddress), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&m_symbolTableIndex), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&m_type), sizeof(int16_t));
    }
}
