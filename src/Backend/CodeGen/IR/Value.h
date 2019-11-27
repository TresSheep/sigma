#pragma once

#include <memory>
#include <string>

namespace Backend::CodeGen::IR
{
    class Value
    {
    public:
        Value();
        virtual ~Value();

        virtual std::string_view GetIdentifier();

        virtual void SetIdentifier(std::string_view identifier);
        virtual std::string_view GetValue();

		virtual const std::string IR() = 0;

    protected:
        std::string _identifier;
    };
}