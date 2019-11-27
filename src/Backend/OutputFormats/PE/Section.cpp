#include "Section.h"
#include <fstream>
#include <vector>
#include <cstring>

namespace Backend::OutputFormats::PE
{
    Section::Section() :
        m_name(), m_physicalAddress(0), m_virtualAddress(0), m_sizeOfRawData(0), m_pointerToRawData(0), m_pointerToRelocations(0),
        m_pointerToLinenumbers(0), m_numberOfRelocations(0), m_numberOfLinenumbers(0), m_characteristics(0), m_rawData(0),
		m_relocations(0)
    {
    }

    Section::~Section()
    {
    }

    void Section::SetName(const char* name)
    {
        memcpy(m_name, name, sizeof(m_name));
    }

    void Section::SetPhysicalAddress(int32_t physicalSize)
    {
        m_physicalAddress = physicalSize;
    }

    void Section::SetVirtualAddress(int32_t virtualAddress)
    {
        m_virtualAddress = virtualAddress;
    }

    void Section::SetSizeOfRawData(int32_t sizeOfRawData)
    {
        m_sizeOfRawData = sizeOfRawData;
    }

    void Section::SetPointerToRawData(int32_t pointerToRawData)
    {
        m_pointerToRawData = pointerToRawData;
    }

    void Section::SetPointerToRelocations(int32_t pointerToRelocations)
    {
        m_pointerToRelocations = pointerToRelocations;
    }

    void Section::SetPointerToLinenumbers(int32_t pointerToLinenumbers)
    {
        m_pointerToLinenumbers = pointerToLinenumbers;
    }

    void Section::SetNumberOfRelocations(int16_t numberOfRelocations)
    {
        m_numberOfRelocations = numberOfRelocations;
    }

    void Section::SetNumberOfLinenumbers(int16_t numberOfLinenumbers)
    {
        m_numberOfLinenumbers = numberOfLinenumbers;
    }

    void Section::SetCharacteristics(int32_t characteristics)
    {
        m_characteristics = characteristics;
    }

    void Section::AddRawData(int8_t byte)
    {
        m_rawData.push_back(byte);
    }

    size_t Section::GetRawDataSize()
    {
        return m_rawData.size();
    }

	void Section::AddRelocation(Relocation& relocation)
	{
		m_relocations.push_back(relocation);
	}

	size_t Section::GetNumberOfRelocations()
	{
		return m_relocations.size() * 10;
	}

    void Section::Write(std::ofstream& stream)
    {
		m_numberOfRelocations = m_relocations.size();
        m_sizeOfRawData = m_rawData.size();
		m_pointerToRelocations = m_rawData.size() + m_pointerToRawData;
		m_physicalAddress = 0;

        stream.write(reinterpret_cast<char*>(&m_name), sizeof(int8_t[8]));
        stream.write(reinterpret_cast<char*>(&m_physicalAddress), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&m_virtualAddress), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&m_sizeOfRawData), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&m_pointerToRawData), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&m_pointerToRelocations), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&m_pointerToLinenumbers), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&m_numberOfRelocations), sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&m_numberOfLinenumbers), sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&m_characteristics), sizeof(int32_t));
    }

    void Section::WriteRawData(std::ofstream& stream)
    {
        for (int8_t byte : m_rawData)
        {
            stream << byte;
        }
    }

	void Section::WriteRelocations(std::ofstream& stream)
	{
		for (auto reloc : m_relocations)
		{
			reloc.Write(stream);
		}
	}

    std::string Section::GetName()
    {
        std::string str;
        for (auto c : m_name)
        {
            if (c != '\0')
                str += (char)c;
        }

        return str;
    }
}
