#pragma once

#include <vector>
#include <string>

namespace Backend::CodeGen::Asm::Command
{
    static std::vector<uint8_t> leave(std::string& debug);

    std::vector<uint8_t> leave(std::string& debug)
    {
#ifdef DEBUG
        debug = "\nleave";
#endif
        std::vector<uint8_t> vec;
        vec.push_back(0xC9);

        return vec;
    }
}