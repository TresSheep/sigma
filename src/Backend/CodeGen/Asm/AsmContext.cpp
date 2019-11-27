#include "AsmContext.h"

namespace Backend::CodeGen::Asm
{
    AsmContext::AsmContext() :
        m_currentPos(0), m_functionOffset(0), m_types(0)
    {
    }

    AsmContext::~AsmContext()
    {
    }

    void AsmContext::AddFunction(std::shared_ptr<Function> func)
    {
        func->SetPosition(m_functionOffset);
        m_functions.push_back(func);

        // Temporary calculation of offset
        AsmWriter writer;
        m_functionOffset += func->Asm(writer)->textBytes.size();
    }

    void AsmContext::SetLabelPosition(std::pair<std::string, size_t> label)
    {
        m_labels.push_back(label);
    }

    size_t AsmContext::GetCurrentVariablePosition()
    {
        return m_currentPos;
    }
}