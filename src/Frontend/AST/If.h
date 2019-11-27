#pragma once

#include "Expression.h"
#include <Backend/CodeGen/IR/Block.h>

#include <Backend/CodeGen/IR/Logic/Compare.h>
#include <Backend/CodeGen/IR/Jump.h>
#include "Log.h"

namespace Frontend::AST
{
    class If : public Expression
    {
    public:
        If(std::unique_ptr<Log> log, std::vector<std::unique_ptr<Expression>> body);
        ~If();

        void SetRepeat(bool repeat);

        std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

    private:
        std::unique_ptr<Log> m_log;
        std::vector<std::unique_ptr<Expression>> m_body;
        bool m_repeat;
    };
}
