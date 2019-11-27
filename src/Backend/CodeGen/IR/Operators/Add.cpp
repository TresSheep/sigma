#include "Add.h"

namespace Backend::CodeGen::IR
{
    Add::Add(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs) :
        m_lhs(std::move(lhs)), m_rhs(std::move(rhs))
    {
        _identifier = "%";
    }

    Add::~Add()
    {
    }

    const std::string Add::IR()
    {
        std::string str;
        //str += m_lhs->IR();
        str += "add ";
        str += m_lhs->IR();
        str += " ";
        str += m_rhs->IR();
        return str;
    }
}