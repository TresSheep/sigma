#pragma once

#include <string>
#include <vector>
#include <Backend/OutputFormats/PE/PE.h>
#include <Backend/CodeGen/Asm/ObjectFile.h>
#include <Backend/OutputFormats/PE/Section.h>

namespace Backend::Linker
{
    template <typename OutputFormat>
    class Linker
    {
    public:
        Linker(std::string_view output)
        {
        }

        ~Linker()
        {
        }

        void Write()
        {
        }

        void AddFile(OutputFormat file)
        {
            m_files.push_back(file);
        }

        void AddLib(const std::string& lib);

    private:
        std::vector<OutputFormat> m_files;
        std::unique_ptr<OutputFormat> m_format;
        std::vector<std::string> m_libs;
    };
}

#include "Linker.inl"