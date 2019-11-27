#pragma once

#include <vector>
#include <string>
#include <Backend/OutputFormats/PE/PE.h>
#include <Backend/OutputFormats/PE/Symbol.h>

namespace Backend::CodeGen::Asm::Command
{
    static std::shared_ptr<OutputFormats::PE::Symbol> extrn(std::string name, std::string& debug);

    std::shared_ptr<OutputFormats::PE::Symbol> extrn(std::string name, std::string& debug)
    {
#ifdef DEBUG
        debug = "extern " + name + "\n";
#endif
        std::shared_ptr<OutputFormats::PE::Symbol> symbol(new OutputFormats::PE::Symbol());
        symbol->SetSymbolName(name.c_str());
        symbol->SetStorageClass((int16_t)OutputFormats::PE::ImageSymbolClass::EXTERNAL);
        return symbol;
    }
}