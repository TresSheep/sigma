#pragma once

#include <vector>
#include <string>
#include "../Registers.h"

namespace Backend::CodeGen::Asm::Command
{
    typedef struct _AsmVariable : public AsmValue
    {
    private:
        std::string debug;
    public:
        size_t size;
        size_t offset;

        std::string ToString()
        {
            return debug;
        }

        std::string DataToString()
        {
            return "";
        }

        std::vector<uint8_t> GetTextBytes()
        {
            std::vector<uint8_t> bytes;
            //uint8_t byte = 0x00;
            //byte |= (1 << 6);
            //register_to_binary(RBP, byte, 2);
            //bytes.push_back(byte);

            //debug += "[rbp - " + std::to_string(offset) + "]";

            //byte = 0x00 - offset;
            //bytes.push_back(byte);
            return bytes;
        }

        std::vector<uint8_t> GetDataBytes()
        {
            std::vector<uint8_t> bytes;
            return bytes;
        }
    } AsmVariable;
}