#include "Variable.h"

namespace Backend::CodeGen::IR
{
    Variable::Variable(const bool decl) :
        m_type(), m_decl(decl), m_lvalue(false)
    {
        _identifier = "";
    }

    Variable::Variable(std::string_view identifier, DT type, const bool decl) :
        m_type(type), m_decl(decl), m_lvalue(false)
    {
        _identifier = identifier;
    }

    Variable::~Variable()
    {
    }

    void Variable::SetIdentifier(std::string_view identifier)
    {
        _identifier = identifier;
    }

    std::string_view Variable::GetIdentifier()
    {
        return _identifier;
    }

    void Variable::SetType(DT type)
    {
        m_type = type;
    }

    void Variable::AddBinaryOp(std::unique_ptr<Value> val)
    {
        m_binOp = std::move(val);
    }

    DT Variable::GetType()
    {
        return m_type;
    }

    const std::string Variable::IR()
    {
        if (m_decl)
        {
            return "decl " + _identifier + " " + m_type.IR();
        }
        else
        {
            if (m_lvalue)
                return "address_of " + _identifier;

            return _identifier;
        }

        return "";
    }
}