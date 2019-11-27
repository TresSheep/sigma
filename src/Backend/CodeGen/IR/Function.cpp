#include "Function.h"

namespace Backend::CodeGen::IR
{
    Function::Function(std::string_view identifier) :
        m_identifier(identifier), m_external(false), m_forward(false), m_inl(false)
    {
    }

    Function::~Function()
    {
    }

    std::string_view Function::GetIdentifier()
    {
        return m_identifier;
    }

    void Function::SetFunctionType(DT functionType)
    {
        m_functionType = functionType;
    }

    void Function::AddArgument(std::unique_ptr<Value> var)
    {
        m_args.push_back(std::move(var));
    }

    void Function::AddLocalVariable(std::shared_ptr<Variable> var)
    {
        m_localVars.push_back(var);
    }

    std::shared_ptr<Variable> Function::GetLocalVariable(std::string_view name)
    {
        for (auto& var : m_localVars)
        {
            if (var->GetIdentifier().compare(name) == 0)
            {
                return var;
            }
        }

        return nullptr;
    }

    void Function::SetExternal(bool external)
    {
        m_external = external;
    }

    DT Function::GetFunctionType()
    {
        return m_functionType;
    }

    const std::string Function::IR()
    {
        std::string ir;
        if (m_inl)
            ir += "__inl ";

        if (m_external)
        {
            ir += "extern ";
        }
        if (m_forward)
        {
            ir += "forward ";
        }
        ir += m_functionType.IR() + " ";
        ir += m_identifier.c_str();
        ir += "(";
        for (auto& arg : m_args)
        {
            ir += arg->IR();
            ir += ", ";
        }
        if (ir.back() != '(')
        {
            ir.pop_back();
            ir.pop_back();
        }
        ir += ")";
        if (m_external)
        {
            ir += "\n";
        }
        else if (m_forward)
        {
            ir += "\n";
        }
        else
        {
            ir += " {\n";

            // Body

            for (auto& expr : Body)
            {
                if (expr)
                {
                    ir += expr->IR();
                    ir += "\n\t";
                }
            }

            ir.pop_back();
            ir += "}\n\n";
        }

        return ir;
    }
}