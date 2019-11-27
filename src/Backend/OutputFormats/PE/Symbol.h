#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <cstring>
#include <stdint.h>
#include <stddef.h>
#include "AuxSymbol.h"

namespace Backend::OutputFormats::PE
{
    class Symbol
    {
    public:
        Symbol();
        ~Symbol();

        void SetSymbolName(const char* symbolName); // Must be shorter than 8 byte
        void SetStringTableOffset(int32_t offset);
        void SetSymbolValue(int32_t symbolValue);
        void SetSectionNumber(int16_t sectionNumber);
        void SetSymbolType(int16_t symbolType);
        void SetStorageClass(int8_t storageClass);
        void SetAuxiliaryCount(int8_t auxiliaryCount);

        bool NeedsAddressFromStringTable();
        std::string GetStringTableString();

		void AddAuxiliarySymbol(AuxSymbol& aux);
		size_t GetAuxiliaryCount();

		std::string GetSymbolName();

        void Write(std::ofstream& stream);

        static const size_t Size = 3 * sizeof(int8_t) + 2 * sizeof(int16_t) + sizeof(int32_t);

    private:
        int8_t m_symbolName[8];
        int32_t m_symbolValue;
        int16_t m_sectionNumber;
        int16_t m_symbolType;
        int8_t m_storageClass;
        int8_t m_auxiliaryCount;

        int32_t m_zeroes;
        int32_t m_offset;

        std::string m_stringTableString;
		std::vector<AuxSymbol> m_auxiliarySymbols;
    };
}
