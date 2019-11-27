#include "DTCustom.h"

namespace Backend::CodeGen::IR
{
    DTCustom::DTCustom(std::string_view id, bool ptr) :
        m_id(id)
    {
        _identifier = m_id;
    }

    DTCustom::~DTCustom()
    {
    }

    const std::string DTCustom::IR()
    {
        return m_id;
    }
}