#include "Symbol.h"
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <cstring>

namespace Backend::OutputFormats::PE
{
    Symbol::Symbol() :
        m_symbolName(), m_symbolValue(0), m_sectionNumber(0), m_symbolType(0), m_storageClass(0), m_auxiliaryCount(0),
        m_stringTableString(""), m_zeroes(0), m_offset(0), m_auxiliarySymbols(0)
    {
    }

    Symbol::~Symbol()
    {
    }

    // Must be shorter than 8 byte
    void Symbol::SetSymbolName(const char* symbolName)
    {
        if (strlen(symbolName) >= 8)
            m_stringTableString = symbolName;
        else
            memcpy(m_symbolName, symbolName, sizeof(m_symbolName));
    }

    void Symbol::SetStringTableOffset(int32_t offset)
    {
        m_offset = offset;
    }

    void Symbol::SetSymbolValue(int32_t symbolValue)
    {
        m_symbolValue = symbolValue;
    }

    void Symbol::SetSectionNumber(int16_t sectionNumber)
    {
        m_sectionNumber = sectionNumber;
    }

    void Symbol::SetSymbolType(int16_t symbolType)
    {
        m_symbolType = symbolType;
    }

    void Symbol::SetStorageClass(int8_t storageClass)
    {
        m_storageClass = storageClass;
    }

    void Symbol::SetAuxiliaryCount(int8_t auxiliaryCount)
    {
        m_auxiliaryCount = auxiliaryCount;
    }

    bool Symbol::NeedsAddressFromStringTable()
    {
        return (!m_stringTableString.empty());
    }

    std::string Symbol::GetStringTableString()
    {
        return m_stringTableString;
    }

    void Symbol::AddAuxiliarySymbol(AuxSymbol& aux)
    {
        m_auxiliarySymbols.push_back(aux);
    }

    size_t Symbol::GetAuxiliaryCount()
    {
        return m_auxiliarySymbols.size();
    }

    std::string Symbol::GetSymbolName()
    {
        if (!m_stringTableString.empty())
            return m_stringTableString;

        char str[8];
        memcpy(str, m_symbolName, sizeof(m_symbolName));

        std::string s;
        s = str;
        return s;
    }

    void Symbol::Write(std::ofstream& stream)
    {
        m_auxiliaryCount = m_auxiliarySymbols.size();

        if (m_offset == 0)
        {
            stream.write(reinterpret_cast<char*>(&m_symbolName), sizeof(int8_t[8]));
        }
        else
        {
            stream.write(reinterpret_cast<char*>(&m_zeroes), sizeof(int32_t));
            stream.write(reinterpret_cast<char*>(&m_offset), sizeof(int32_t));
        }

        stream.write(reinterpret_cast<char*>(&m_symbolValue), sizeof(int32_t));
        stream.write(reinterpret_cast<char*>(&m_sectionNumber), sizeof(int16_t));
        stream.write(reinterpret_cast<char*>(&m_symbolType), sizeof(uint16_t));
        stream.write(reinterpret_cast<char*>(&m_storageClass), sizeof(int8_t));
        stream.write(reinterpret_cast<char*>(&m_auxiliaryCount), sizeof(int8_t));

        for (auto aux : m_auxiliarySymbols)
        {
            aux.Write(stream);
        }
    }
}
