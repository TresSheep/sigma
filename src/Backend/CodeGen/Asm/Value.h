#pragma once

#include <memory>
#include <string>
#include <vector>
#include "AsmWriter.h"
#include "Registers.h"

namespace Backend::CodeGen::Asm
{
    typedef struct _Info
    {
        size_t textPosition;
        size_t dataPosition;
        std::vector<std::pair<std::string, bool>> functions;
    } Info;

    enum class ValueType
    {
        VAR,
        ADD,
        CALL,
        BLOCK,
        CMP,
        CONST,
        ELEMENT,
        JMP,
        MOV,
        RET,
        STR,
        ARRAY,
        DIV
    };

    class Value
    {
    public:
        Value();
        ~Value();

        std::string_view GetIdentifier();

        void SetIdentifier(std::string_view identifier);

        virtual std::unique_ptr<Command::AsmValue> Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition) = 0;
        virtual ValueType GetType() = 0;

    protected:
        std::string _identifier;
    };
}
