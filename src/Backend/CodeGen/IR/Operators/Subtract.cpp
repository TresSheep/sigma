#include "Subtract.h"

namespace Backend::CodeGen::IR
{
    Subtract::Subtract(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs) :
        m_lhs(std::move(lhs)), m_rhs(std::move(rhs))
    {
        _identifier = "%";
    }

    Subtract::~Subtract()
    {
    }

    const std::string Subtract::IR()
    {
        std::string str;
        str += m_lhs->IR();
        return str.c_str();
    }
}