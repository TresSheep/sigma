#include "Prototype.h"

namespace Frontend
{
    namespace AST
    {
        Prototype::Prototype(std::string identifier, std::vector<std::pair<std::string, std::string>> arguments, std::vector<std::pair<std::string, std::string>> end) :
            m_identifier(identifier), m_arguments(arguments), m_end(end), m_impl(false)
        {
        }

        void Prototype::SetIdentifier(std::string_view id)
        {
            m_identifier = id;
        }

        std::string_view Prototype::GetIdentifier()
        {
            return m_identifier;
        }

        void Prototype::SetImpl(bool impl)
        {
            m_impl = impl;
        }

        std::unique_ptr<Backend::CodeGen::IR::Function> Prototype::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
        {
            std::unique_ptr<Backend::CodeGen::IR::Function> func(new Backend::CodeGen::IR::Function(m_identifier));
            //for (auto& arg : m_arguments)
            //    func->AddArgument(arg->GenerateCode(irGenerator));

            if (m_impl)
            {
                // Add "this" argument
                std::unique_ptr<Variable> arg(new Variable("this", "basic_string", "*"));
                func->AddArgument(arg->GenerateCode(context, irGenerator));
            }

            size_t i = 0;
            while (true)
            {
                if (m_arguments.size() == 0)
                    break;

                std::string id = m_arguments[i].second;
                bool ptr = (m_arguments[i + 1].first.compare("ptr") == 0);
                if (ptr)
                {
                    std::unique_ptr<Variable> arg(new Variable(id, m_arguments[i + 2].second, "*"));
                    func->AddArgument(arg->GenerateCode(context, irGenerator));
                }
                else
                {
                    std::unique_ptr<Variable> arg(new Variable(id, m_arguments[i + 1].second));
                    func->AddArgument(arg->GenerateCode(context, irGenerator));
                }

                if (ptr)
                {
                    if (i + 3 < m_arguments.size())
                        i += 3;
                    else
                        break;
                }
                else
                {
                    if (i + 2 < m_arguments.size())
                        i += 2;
                    else
                        break;
                }

            }

            bool ptr = (m_end.size() > 1);

            if (m_end[0].second.compare("int") == 0)
            {
                func->SetFunctionType(Backend::CodeGen::IR::DTInt(4, ptr));
            }
            else if (m_end[0].second.compare("short") == 0)
            {
                func->SetFunctionType(Backend::CodeGen::IR::DTInt(2, ptr));
            }
            else if (m_end[0].second.compare("byte") == 0)
            {
                func->SetFunctionType(Backend::CodeGen::IR::DTInt(1, ptr));
            }
            else if (m_end[0].second.compare("void") == 0)
            {
                func->SetFunctionType(Backend::CodeGen::IR::DTVoid());
            }
            else if (m_end[0].second.compare("string") == 0)
            {
                func->SetFunctionType(Backend::CodeGen::IR::DTString(""));
            }
            else
            {
                func->SetFunctionType(Backend::CodeGen::IR::DTCustom(m_end[0].second));
            }

            return func;
        }
    }
}
