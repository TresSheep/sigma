#pragma once

#include <string>
#include <vector>

namespace Frontend::Preprocessor
{
    class Generator
    {
    public:
        Generator();
        ~Generator();

        void AddImport(std::string name);

        // Get
        std::vector<std::string>& GetImports();

    private:
        std::vector<std::string> m_imports;
    };
}