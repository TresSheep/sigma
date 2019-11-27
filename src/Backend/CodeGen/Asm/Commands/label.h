#pragma once

#include <stdint.h>
#include <vector>
#include <string>

namespace Backend::CodeGen::Asm::Command
{
    static std::vector<uint8_t> label(std::string name, std::string& debug);

    std::vector<uint8_t> label(std::string name, std::string& debug)
    {
#ifdef DEBUG
        debug = name;
        debug += ":\n";
#endif
        std::vector<uint8_t> vec;

        return vec;
    }
}
