#include "Div.h"

namespace Backend::CodeGen::IR
{
    Div::Div(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs, bool isModulo) :
        m_lhs(std::move(lhs)), m_rhs(std::move(rhs)), m_isModulo(isModulo)
    {
        _identifier = "%";
    }

    Div::~Div()
    {
    }

    const std::string Div::IR()
    {
        std::string str;
        //str += m_lhs->IR();
        if (m_isModulo)
            str += "modulo ";
        else
            str += "div ";
        str += m_lhs->GetIdentifier();
        str += " ";
        str += m_rhs->IR();
        return str;
    }
}