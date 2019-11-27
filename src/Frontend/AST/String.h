#pragma once

#include "Expression.h"
#include <Backend/CodeGen/IR/Types/DTString.h>

namespace Frontend
{
    namespace AST
    {
        class String : public Expression
        {
        public:
            String(std::vector<std::string> str);
            String(std::string str);
            ~String();

            std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

        private:
            std::vector<std::string> m_str;
        };
    }
}
