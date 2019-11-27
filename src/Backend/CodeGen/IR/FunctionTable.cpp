#include "FunctionTable.h"

namespace Backend::CodeGen::IR
{
    FunctionTable::FunctionTable() :
        m_functionTable(0)
    {
    }

    FunctionTable::~FunctionTable()
    {
    }

    void FunctionTable::AddEntry(std::shared_ptr<Function> function)
    {
        m_functionTable.push_back(function);
    }
}