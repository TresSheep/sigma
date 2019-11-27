#pragma once

#include <string>
#include <memory>
#include "Value.h"
#include "Types/DT.h"

namespace Backend::CodeGen::IR
{
    class Variable : public Value
    {
    public:
        Variable(const bool decl = false);
        Variable(std::string_view identifier, DT type, const bool decl);
        ~Variable();

        void SetIdentifier(std::string_view identifier);
        std::string_view GetIdentifier();
        void SetType(DT type);
        void AddBinaryOp(std::unique_ptr<Value> val);

        DT GetType();

        void SetLvalue(bool lval)
        {
            m_lvalue = lval;
        }

            const std::string IR() override;

    private:
        DT m_type;
        std::unique_ptr<Value> m_binOp;
        bool m_decl;
        bool m_lvalue;
    };
}
