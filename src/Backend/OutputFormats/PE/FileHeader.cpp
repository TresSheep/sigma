#include "FileHeader.h"

namespace Backend::OutputFormats::PE
{
    FileHeader::FileHeader() :
        m_machine(0), m_numberOfSections(0), m_timeDateStamp(0), m_pointerToSymbolTable(0), m_numberOfSymbols(0),
        m_sizeOfOptionalHeader(0), m_characteristics(0)
    {
    }

    FileHeader::~FileHeader()
    {
    }

    void FileHeader::SetMachine(int16_t machine)
    {
        m_machine = machine;
    }

    void FileHeader::SetNumberOfSections(int16_t numberOfSections)
    {
        m_numberOfSections = numberOfSections;
    }

    void FileHeader::SetTimeDateStamp(int32_t timeDateStamp)
    {
        m_timeDateStamp = timeDateStamp;
    }

    void FileHeader::SetPointerToSymbolTable(int32_t pointerToSymbolTable)
    {
        m_pointerToSymbolTable = pointerToSymbolTable;
    }

    void FileHeader::SetNumberOfSymbols(int32_t numberOfSymbols)
    {
        m_numberOfSymbols = numberOfSymbols;
    }

    void FileHeader::SetSizeOfOptionalHeader(int16_t sizeOfOptionalHeader)
    {
        m_sizeOfOptionalHeader = sizeOfOptionalHeader;
    }

    void FileHeader::SetCharacteristics(int16_t characteristics)
    {
        m_characteristics = characteristics;
    }

    void FileHeader::Write(std::ofstream& stream)
    {
        m_timeDateStamp = time(NULL);
        stream.write(reinterpret_cast<char*>(&m_machine),               sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&m_numberOfSections),      sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&m_timeDateStamp),         sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&m_pointerToSymbolTable),  sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&m_numberOfSymbols),       sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&m_sizeOfOptionalHeader),  sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&m_characteristics),       sizeof(int16_t));
    }
}
