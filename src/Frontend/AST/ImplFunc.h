#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Variable.h"
#include "Number.h"
#include "Call.h"
#include "Prototype.h"
#include "Return.h"
#include "Expression.h"

#include <Backend/CodeGen/IR/IRGenerator.h>
#include <Backend/CodeGen/IR/Block.h>
#include <Backend/CodeGen/IR/IRContext.h>

namespace Frontend
{
    namespace AST
    {
        class ImplFunc : public Expression
        {
        public:
            ImplFunc();
            ImplFunc(std::vector<std::pair<std::string, std::string>> prototype);
            ImplFunc(std::unique_ptr<Prototype> prototype, std::vector<std::unique_ptr<Expression>> body);

            std::string_view GetIdentifier();
            void SetParent(std::string_view parent);

            std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;
        private:
            std::unique_ptr<Prototype> m_prototype;
            std::vector<std::unique_ptr<Expression>> m_body;
            std::string m_parent;
        };
    }
}
