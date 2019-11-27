#pragma once

#include <string>
#include <vector>
#include "Types/DT.h"
#include <memory>
#include "Value.h"
#include "Variable.h"
#include <map>

namespace Backend::CodeGen::IR
{
    class Function : public Value
    {
    public:
        Function(std::string_view identifier);
        ~Function();

        std::string_view GetIdentifier();
        void SetFunctionType(DT functionType);
        void AddArgument(std::unique_ptr<Value> arg);
        void AddLocalVariable(std::shared_ptr<Variable> var);
        std::shared_ptr<Variable> GetLocalVariable(std::string_view name);

        bool IsExternal() { return m_external; }
        void SetExternal(bool external);
        void SetForward(bool forward)
        {
            m_forward = forward;
        }
        void SetInline(bool inl)
        {
            m_inl = inl;
        }

        DT GetFunctionType();
        const std::string IR();

        std::vector<std::unique_ptr<Value>> Body;

    private:
        std::string m_identifier;
        DT m_functionType;
        std::vector<std::unique_ptr<Value>> m_args;
        std::vector<std::shared_ptr<Variable>> m_localVars;
        bool m_external;
        bool m_forward;
        bool m_inl;
    };
}
