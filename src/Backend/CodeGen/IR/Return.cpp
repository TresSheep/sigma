#include "Return.h"

namespace Backend::CodeGen::IR
{
    Return::Return(std::unique_ptr<Value> value) :
        m_value(std::move(value))
    {
    }

    Return::~Return()
    {
    }

    const std::string Return::IR()
    {
        std::string s = "return ";
        s += m_value->IR();
        return s;
    }
}