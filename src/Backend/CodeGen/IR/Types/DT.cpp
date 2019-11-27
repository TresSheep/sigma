#include "DT.h"

namespace Backend::CodeGen::IR
{
    DT::DT() :
        _byteCount(0), _ptr(false)
    {
        _identifier = "";
    }

    DT::~DT()
    {
    }

    Types DT::ToEnum()
    {
        return _enum;
    }

    size_t DT::GetByteCount()
    {
        return _byteCount;
    }

    bool DT::IsPtr()
    {
        return _ptr;
    }

    const std::string DT::IR()
    {
        if (_ptr)
            return _identifier + "*";

        return _identifier;
    }

    void DT::SetOperEqu(std::unique_ptr<Value> val)
    {
        m_operEqu = val->IR();
    }

    const std::string& DT::OperEqu()
    {
        return m_operEqu;
    }
}