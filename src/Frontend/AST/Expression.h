#pragma once

#include <Backend/CodeGen/IR/IRGenerator.h>
#include <Backend/CodeGen/IR/Value.h>
#include <Backend/CodeGen/IR/IRContext.h>

#include <string>
#include <memory>

typedef std::vector<std::pair<std::string, std::string>> syntax_args;

namespace Frontend
{
    namespace AST
    {
        class Expression
        {
        public:
            Expression()
            {
            }

            virtual std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) = 0;
        };
    }
}

typedef std::vector<std::pair<syntax_args, std::unique_ptr<Frontend::AST::Expression>>> node_and_expr_args;
