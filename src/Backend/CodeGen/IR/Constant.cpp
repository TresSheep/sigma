#include "Constant.h"

namespace Backend::CodeGen::IR
{
    const DTInt Constant::GetInt8(bool ptr)
    {
        DTInt dt_int(1, ptr);
        return dt_int;
    }

    const DTInt Constant::GetInt16(bool ptr)
    {
        DTInt dt_int(2, ptr);
        return dt_int;
    }

    const DTInt Constant::GetInt32(bool ptr)
    {
        DTInt dt_int(4, ptr);
        return dt_int;
    }

    const DTVoid Constant::GetVoid(bool ptr)
    {
        DTVoid dt_void(ptr);
        return dt_void;
    }

    const DTFloat Constant::GetFloat()
    {
        DTFloat dt_float(4);
        return dt_float;
    }

    const DTFloat Constant::GetDouble()
    {
        DTFloat dt_float(8);
        return dt_float;
    }

    void Constant::SetConstant(std::string_view constant)
    {
        m_constant = constant;
    }

    const std::string Constant::IR()
    {
        return m_constant;
    }
}