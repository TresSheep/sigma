#pragma once

#include "Expression.h"
#include <Backend/CodeGen/IR/Constant.h>

namespace Frontend::AST
{
    class Number : public Expression
    {
    public:
        Number(std::string number);
        ~Number();

        Backend::CodeGen::IR::DT DetectType(std::string number);
        void SetType(Backend::CodeGen::IR::DT type);

        std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

    private:
        std::string m_number;
        Backend::CodeGen::IR::DT m_type;
    };
}
