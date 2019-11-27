#pragma once

#include "Expression.h"
#include "Number.h"
#include "Variable.h"
#include <Backend/CodeGen/IR/Call.h>

#include "String.h"

namespace Frontend
{
    namespace AST
    {
        class Call : public Expression
        {
        public:
            Call(std::string identifier, node_and_expr_args arguments);
            ~Call();

            std::string GetIdentifier();

            std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;
        private:
            std::string m_identifier;
            node_and_expr_args m_arguments;
        };
    }
}
