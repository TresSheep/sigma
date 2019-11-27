#pragma once

#include <vector>
#include "mov.h"

namespace Backend::CodeGen::Asm::Command
{
    static std::vector<uint8_t> call(std::string name, int32_t offset, std::string& debug)
    {
#ifdef DEBUG
        debug = "call " + name;
#endif
        std::vector<uint8_t> vec;

        vec.push_back(0xE8);
        if (offset == 0)
        {
            vec.push_back(0x00);
            vec.push_back(0x00);
            vec.push_back(0x00);
            vec.push_back(0x00);
        }
        else
        {
            offset -= 5;
            vec.push_back((offset >> 0) & 0xFF);
            vec.push_back((offset >> 8) & 0xFF);
            vec.push_back((offset >> 16) & 0xFF);
            vec.push_back((offset >> 24) & 0xFF);
        }

        return vec;
    }
}
