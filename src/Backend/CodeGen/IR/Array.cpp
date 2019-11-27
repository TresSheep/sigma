#include "Array.h"

namespace Backend::CodeGen::IR
{
    Array::Array(std::string_view id, const DT& type, const size_t numberOfElements) :
        m_id(id), m_type(type), m_numberOfElements(numberOfElements)
    {
    }

    Array::~Array()
    {
    }

    const std::string Array::IR()
    {
        std::string str = "array ";
        str += m_type.IR();
        str += m_id;
        str += " ";
        str += std::to_string(m_numberOfElements);
        return str;
    }
}