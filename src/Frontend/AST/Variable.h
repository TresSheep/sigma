#pragma once

#include <string>
#include "Expression.h"
#include <Backend/CodeGen/IR/Variable.h>
#include <Backend/CodeGen/IR/Constant.h>
#include <Backend/CodeGen/IR/Array.h>
#include <Backend/CodeGen/IR/Element.h>
#include "Number.h"

namespace Frontend
{
    namespace AST
    {
        class Variable : public Expression
        {
        public:
            Variable(std::string_view identifier);
            Variable(std::string_view identifier, std::string_view type);
            Variable(std::string_view identifier, std::string_view type, std::string_view pointer);
            Variable(const syntax_args& args);

            Variable(std::string_view identifier, Backend::CodeGen::IR::DT dt);
            ~Variable();

            void SetIdentifier(std::string_view identifier);

            std::string_view GetIdentifier();
            std::string_view GetType();
            void SetType(std::string_view type);
            void SetType(const Backend::CodeGen::IR::DT& dt);

            void DetectType();

            void SetDecl(bool decl);
            bool IsDecl()
            {
                return m_decl;
            }

            void SetLvalue(bool lval)
            {
                m_lvalue = lval;
            }

            std::unique_ptr<Backend::CodeGen::IR::Value> GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator) override;

        private:
            syntax_args m_args;
            std::string m_identifier;
            std::string m_type;
            std::string m_num;
            Backend::CodeGen::IR::DT m_dt;
            bool m_decl;
            bool m_ptr;
            bool m_lvalue;
        };
    }
}
