#include "Value.h"

namespace Backend::CodeGen::IR
{
    Value::Value()
    {
    }

    Value::~Value()
    {
    }

    std::string_view Value::GetIdentifier()
    {
        return _identifier;
    }

    void Value::SetIdentifier(std::string_view identifier)
    {
        _identifier = identifier;
    }

    std::string_view Value::GetValue()
    {
        return "";
    }
}