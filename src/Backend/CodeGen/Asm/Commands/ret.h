#pragma once

#include <vector>
#include <string>
#include <stdint.h>

namespace Backend::CodeGen::Asm::Command
{
    static std::vector<uint8_t> ret(std::string& debug);

    std::vector<uint8_t> ret(std::string& debug)
    {
#ifdef DEBUG
        debug = "\nret\n\n";
#endif
        std::vector<uint8_t> vec;
        vec.push_back(0xC3);

        return vec;
    }
}
