#include "Call.h"

namespace Backend::CodeGen::IR
{
    Call::Call(std::string_view name) :
        m_name(name)
    {
    }

    Call::~Call()
    {
    }

    const std::string Call::IR()
    {
        std::string str = "call " + m_name + "(";
        for (auto& arg : m_args)
        {
            str += arg->IR();
            str += ", ";
        }
        if (str.back() != '(')
        {
            str.pop_back();
            str.pop_back();
        }
        str += ")";
        return str.c_str();
    }

    void Call::AddArg(std::unique_ptr<Value> arg)
    {
        m_args.push_back(std::move(arg));
    }
}