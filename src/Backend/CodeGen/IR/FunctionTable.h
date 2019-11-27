#pragma once

#include "Function.h"

namespace Backend::CodeGen::IR
{
    class FunctionTable
    {
    public:
        FunctionTable();
        ~FunctionTable();

        void AddEntry(std::shared_ptr<Function> function);

        std::vector<std::shared_ptr<Function>>& ToArray() { return m_functionTable; }

    private:
        std::vector<std::shared_ptr<Function>> m_functionTable;
    };
}