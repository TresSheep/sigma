#include "Generator.h"

namespace Frontend::Preprocessor
{
    Generator::Generator()
    {
    }

    Generator::~Generator()
    {
    }

    void Generator::AddImport(std::string name)
    {
        m_imports.push_back(name);
    }

    std::vector<std::string>& Generator::GetImports()
    {
        return m_imports;
    }
}