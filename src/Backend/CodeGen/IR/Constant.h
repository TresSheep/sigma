#pragma once

#include "Types/DTInt.h"
#include "Types/DTVoid.h"
#include "Types/DTFloat.h"
#include "Types/DTString.h"

namespace Backend::CodeGen::IR
{
    class Constant : public Value
    {
    public:
        static const DTInt GetInt8(bool ptr = false);
        static const DTInt GetInt16(bool ptr = false);
        static const DTInt GetInt32(bool ptr = false);
        static const DTVoid GetVoid(bool ptr = false);
        static const DTFloat GetFloat();
        static const DTFloat GetDouble();

        void SetConstant(std::string_view constant);

        const std::string IR() override;

    private:
        std::string m_ir;
        std::string m_constant;
    };
}
