#include "Element.h"

namespace Backend::CodeGen::IR
{
    Element::Element(std::unique_ptr<Value> dst, std::unique_ptr<Value> value) :
        m_dst(std::move(dst)), m_value(std::move(value))
    {
    }

    Element::~Element()
    {
    }

    const std::string Element::IR()
    {
        std::string s;
        s += "element ";
        s += m_dst->IR();
        s += " ";
        s += m_value->IR();
        return s;
    }
}