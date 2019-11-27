#pragma once

#include <string>
#include <vector>
#include "Variable.h"
#include <Backend/CodeGen/IR/Types/DTCustom.h>

namespace Frontend
{
    namespace AST
    {
        class Prototype
        {
        public:
            Prototype(
                std::string identifier, std::vector<std::pair<std::string, std::string>> arguments, std::vector<std::pair<std::string, std::string>> end);

            void SetIdentifier(std::string_view id);
            std::string_view GetIdentifier();
            void SetImpl(bool impl);

            std::unique_ptr<Backend::CodeGen::IR::Function> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator);

        private:
            std::string m_identifier;
            std::vector<std::pair<std::string, std::string>> m_arguments;
            std::vector<std::pair<std::string, std::string>> m_end;
            bool m_impl;
        };
    }
}