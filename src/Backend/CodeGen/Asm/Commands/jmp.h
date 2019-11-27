#pragma once

#include <vector>
#include <string>

namespace Backend::CodeGen::Asm::Command
{
    static std::vector<uint8_t> je(std::string name, size_t offset, std::string& debug)
    {
#ifdef DEBUG
        debug = "je ." + name + "\n";
#endif
        std::vector<uint8_t> vec;
        vec.push_back(0x74);
        vec.push_back(offset);

        return vec;
    }

    static std::vector<uint8_t> jne(std::string name, size_t offset, std::string& debug)
    {
#ifdef DEBUG
        debug = "jne ." + name + "\n";
#endif
        std::vector<uint8_t> vec;
        vec.push_back(0x75);
        vec.push_back(offset);

        return vec;
    }

    static std::vector<uint8_t> jmp(std::string name, size_t offset, std::string& debug)
    {
#ifdef DEBUG
        debug = "jmp ." + name + "\n";
#endif
        std::vector<uint8_t> vec;
        vec.push_back(0xEB);
        vec.push_back(offset);

        return vec;
    }
}