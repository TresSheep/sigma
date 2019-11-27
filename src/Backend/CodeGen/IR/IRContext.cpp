#include "IRContext.h"

namespace Backend::CodeGen::IR
{
    IRContext::IRContext(std::string_view name, bool isStruct) :
        m_name(name), m_localVars(0), m_tempConst(0), m_isStruct(isStruct)
    {
    }

    IRContext::~IRContext()
    {
    }

    void IRContext::AddLocalVar(std::shared_ptr<Variable> var)
    {
        m_localVars.push_back(var);
    }

    std::shared_ptr<Variable> IRContext::GetLocalVariable(std::string_view name)
    {
        for (auto var : m_localVars)
        {
            if (var->GetIdentifier().compare(name) == 0)
                return var;
        }

        return nullptr;
    }

    std::vector<std::shared_ptr<Variable>> IRContext::GetLocalVariables()
    {
        return m_localVars;
    }

    std::string_view IRContext::GetName()
    {
        return m_name;
    }

    void IRContext::SetParent(std::shared_ptr<IRContext> parent)
    {
        m_parent = parent;
    }
}