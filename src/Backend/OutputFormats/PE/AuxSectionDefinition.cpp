#include "AuxSectionDefinition.h"

namespace Backend::OutputFormats::PE
{
    AuxSectionDefinition::AuxSectionDefinition() :
        m_length(0), m_numberOfRelocations(0), m_numberOfLinenumbers(0), m_checkSum(0), m_number(0),
        m_section(0)
    {
    }

    AuxSectionDefinition::~AuxSectionDefinition()
    {
    }

    void AuxSectionDefinition::SetLength(int32_t length)
    {
        m_length = length;
    }

    void AuxSectionDefinition::SetNumberOfRelocations(int16_t numberOfRelocations)
    {
        m_numberOfRelocations = numberOfRelocations;
    }

    void AuxSectionDefinition::SetNumberOfLinenumbers(int16_t numberOfLinenumbers)
    {
        m_numberOfLinenumbers = numberOfLinenumbers;
    }

    void AuxSectionDefinition::SetCheckSum(int32_t checkSum)
    {
        m_checkSum = checkSum;
    }

    void AuxSectionDefinition::SetNumber(int16_t number)
    {
        m_number = number;
    }

    void AuxSectionDefinition::SetSection(int8_t section)
    {
        m_section = section;
    }

    void AuxSectionDefinition::Write(std::ofstream& stream)
    {
        stream.write(reinterpret_cast<char*>(&m_length), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&m_numberOfRelocations), sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&m_numberOfLinenumbers), sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&m_checkSum), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&m_number), sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&m_section), sizeof(int8_t));
        uint8_t null = 0;
        stream.write(reinterpret_cast<char*>(&null), sizeof(int8_t) * 3);
    }
}