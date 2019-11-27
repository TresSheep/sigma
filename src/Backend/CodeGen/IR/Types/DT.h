#pragma once

// DT = DataType

#include <string>
#include "../Value.h"

namespace Backend::CodeGen::IR
{
    enum Types
    {
        Int8,
        Int16,
        Int32,
        Int64,
        Float,
        Double,
        String,
        Void,
        Auto,
    };

    class DT : public Value
    {
    public:
        DT();
        ~DT();

        void SetIdentifier(std::string_view id) override
        {
            _identifier = id;
        }
        std::string_view GetIdentifier() override
        {
            return _identifier;
        }

        void SetByteCount(size_t byteCount)
        {
            _byteCount = byteCount;
        }

        Types ToEnum();

        size_t GetByteCount();
        void SetPtr(bool ptr)
        {
            _ptr = ptr;
        }
        bool IsPtr();

        const std::string IR() override;

        void SetOperEqu(std::unique_ptr<Value> val);
        const std::string& OperEqu();

        bool operator==(DT& rhs)
        {
            if (_enum == rhs._enum)
                return true;
            else
                return false;
        }

    protected:
        size_t _byteCount;
        Types _enum;
        bool _ptr;
        std::string _identifier;
        std::string m_operEqu;
    };
}