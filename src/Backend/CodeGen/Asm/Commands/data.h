#pragma once

#include <vector>
#include <string>
#include "../Registers.h"

namespace Backend::CodeGen::Asm::Command
{
    static size_t StringNumber = 0;

    typedef struct _AsmData : public AsmValue
    {
    private:
        std::string debug;
    public:
        std::string str;
        uint32_t offset;

        std::string ToString()
        {
            return "str" + std::to_string(StringNumber - 1);
        }

        std::string DataToString()
        {
            return "str" + std::to_string(StringNumber) + ": db '" + str + "', 0\n";
        }

        std::vector<uint8_t> GetTextBytes()
        {
            std::vector<uint8_t> bytes;

            bytes.push_back((offset >> 0) & 0xFF);
            bytes.push_back((offset >> 8) & 0xFF);
            bytes.push_back((offset >> 16) & 0xFF);
            bytes.push_back((offset >> 24) & 0xFF);

            return bytes;
        }

        std::vector<uint8_t> GetDataBytes()
        {
            std::vector<uint8_t> bytes;
            debug = "str" + std::to_string(StringNumber);
            StringNumber++;
            bool special = false;
            for (char c : str)
            {
                if (special)
                {
                    if (c == 'n')
                    {
                        // Newline
                        bytes.push_back(0x0A);
                    }
                    special = false;
                }
                else
                {
                    if (c != '\\')
                        bytes.push_back((uint8_t)c);
                }

                if (c == '\\')
                {
                    special = true;
                }
            }
            bytes.push_back(0x00);
            return bytes;
        }
    } AsmData;
}