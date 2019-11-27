#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Expression.h"
#include "Prototype.h"
#include "Function.h"

namespace Frontend
{
    namespace AST
    {
        class ForeignFunction : public Expression
        {
        public:
            ForeignFunction(std::unique_ptr<Prototype> proto);
            ~ForeignFunction();

            std::vector<std::unique_ptr<Expression>>& GetArguments();
            void SetType(Backend::CodeGen::IR::DT type);

            std::string GetIdentifier();
            Backend::CodeGen::IR::DT GetFunctionType();
            
            std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

        private:
            std::unique_ptr<Prototype> m_proto;
            std::string m_identifier;
            std::vector<std::unique_ptr<Expression>> m_arguments;
            Backend::CodeGen::IR::DT m_type;
        };
    }
}