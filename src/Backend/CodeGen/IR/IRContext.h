#pragma once

#include <vector>
#include <string>
#include "Variable.h"

namespace Backend::CodeGen::IR
{
    class IRContext
    {
    public:
        IRContext(std::string_view name, bool isStruct = false);
        ~IRContext();

        void AddLocalVar(std::shared_ptr<Variable> var);
        std::shared_ptr<Variable> GetLocalVariable(std::string_view name);
        std::vector<std::shared_ptr<Variable>> GetLocalVariables();

        std::string_view GetName();

        void SetParent(std::shared_ptr<IRContext> parent);
        bool IsStruct()
        {
            return m_isStruct;
        }

        size_t TempNumber = 0;

    private:
        std::string m_name;
        std::vector<std::shared_ptr<Variable>> m_localVars;
        size_t m_tempConst;
        std::shared_ptr<IRContext> m_parent;
        bool m_isStruct;
    };
}