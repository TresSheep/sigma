#pragma once

#include "AuxSymbol.h"
#include <stdint.h>
#include <fstream>

namespace Backend::OutputFormats::PE
{
    class AuxSectionDefinition : public AuxSymbol
    {
    public:
        AuxSectionDefinition();
        ~AuxSectionDefinition();

        void SetLength(int32_t length);
        void SetNumberOfRelocations(int16_t numberOfRelocations);
        void SetNumberOfLinenumbers(int16_t numberOfLinenumbers);
        void SetCheckSum(int32_t checkSum);
        void SetNumber(int16_t number);
        void SetSection(int8_t section);

        void Write(std::ofstream& stream) override;

    private:
        int32_t m_length;
        int16_t m_numberOfRelocations;
        int16_t m_numberOfLinenumbers;
        int32_t m_checkSum;
        int16_t m_number;
        int8_t m_section;
        // Plus 3 bytes unused
    };
}
