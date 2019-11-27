#include "Import.h"

namespace Frontend::Preprocessor::AST
{
    Import::Import(std::string name) :
        m_name(name)
    {
    }

    Import::~Import()
    {
    }

    void Import::GenerateCode(Generator& generator)
    {
        // Traverse path
        // std path b:/sigma/std
        std::string path = "b:/sigma/std/" + m_name;

        std::ifstream f(path);
        if (!f.is_open())
        {
            // It is a regular file
            path = m_name;
        }

        bool found = false;
        for (auto imprt : generator.GetImports())
        {
            if (imprt.compare(path) == 0)
                found = true;
        }

        if (!found)
            generator.AddImport(path);
    }
}