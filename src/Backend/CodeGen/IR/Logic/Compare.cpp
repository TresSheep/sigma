#include "Compare.h"

namespace Backend::CodeGen::IR::Logic
{
    Compare::Compare(std::unique_ptr<Value> val1, std::unique_ptr<Value> val2) :
        m_val1(std::move(val1)), m_val2(std::move(val2))
    {
    }

    Compare::~Compare()
    {
    }

    const std::string Compare::IR()
    {
        std::string s = "cmp ";
        s.append(m_val1->IR());
        s += " ";
        s += m_val2->IR();
        s += "\n";
        return s;
    }
}