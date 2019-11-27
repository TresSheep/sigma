#pragma once

#include <vector>
#include <string>

namespace Backend::CodeGen::Asm::Command
{
    static std::vector<uint8_t> number(int32_t number, std::string& debug)
    {
#ifdef DEBUG
        debug = std::to_string(number) + "\n";
#endif
        std::vector<uint8_t> vec;
        vec.push_back((number >> 0) & 0xFF);
        vec.push_back((number >> 8) & 0xFF);
        vec.push_back((number >> 16) & 0xFF);
        vec.push_back((number >> 24) & 0xFF);

        return vec;
    }
}