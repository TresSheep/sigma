#pragma once

#include <string>
#include "Expression.h"

#include <Backend/CodeGen/IR/Element.h>
#include <Backend/CodeGen/IR/IRContext.h>
#include <Backend/CodeGen/IR/Types/DTInt.h>

namespace Frontend::AST
{
    class Index : public Expression
    {
    public:
        Index(std::string dst, std::string value);
        ~Index();

        std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

    private:
        std::string m_dst;
        std::string m_value;
    };
}