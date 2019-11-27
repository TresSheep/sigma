#include "Variable.h"

namespace Frontend
{
    namespace AST
    {
        Variable::Variable(std::string_view identifier) :
            m_identifier(identifier), m_type(), m_decl(false), m_ptr(false), m_lvalue(false)
        {
            m_dt.SetIdentifier("empty");
        }

        Variable::Variable(std::string_view identifier, std::string_view type) :
            m_identifier(identifier), m_type(), m_decl(true), m_ptr(false), m_lvalue(false)
        {
            m_dt.SetIdentifier("empty");
            SetType(type);
        }

        Variable::Variable(std::string_view identifier, std::string_view type, std::string_view pointer) :
            m_identifier(identifier), m_type(), m_decl(true), m_ptr(false), m_lvalue(false)
        {
            if (pointer.compare("*") == 0)
                m_ptr = true;

            m_dt.SetIdentifier("empty");

            SetType(type);
        }

        Variable::Variable(const syntax_args& args) :
            m_args(args), m_decl(true), m_ptr(false), m_identifier(""), m_type(), m_lvalue(false)
        {
            m_dt.SetIdentifier("empty");
        }

        Variable::Variable(std::string_view identifier, Backend::CodeGen::IR::DT dt) :
            m_identifier(identifier), m_dt(dt), m_decl(true)
        {
            if (m_dt.GetIdentifier().compare("empty") == 0)
                m_decl = false;
        }

        Variable::~Variable()
        {
        }

        void Variable::SetIdentifier(std::string_view identifier)
        {
            m_identifier = identifier;
        }

        std::string_view Variable::GetIdentifier()
        {
            return m_identifier;
        }

        void Variable::SetDecl(bool decl)
        {
            m_decl = decl;
        }

        void Variable::SetType(std::string_view type)
        {
            m_type = type;
        }

        void Variable::SetType(const Backend::CodeGen::IR::DT& dt)
        {
            m_dt = dt;
        }

        std::string_view Variable::GetType()
        {
            return m_type;
        }

        std::unique_ptr<Backend::CodeGen::IR::Value> Variable::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
        {
            if (!m_decl)
            {
                if (m_dt.GetIdentifier().compare("empty") != 0)
                {
                    std::unique_ptr<Backend::CodeGen::IR::Variable> v(new Backend::CodeGen::IR::Variable(m_identifier, m_dt, false));

                    if (context->IsStruct())
                    {
                        bool foundThis = false;
                        for (auto var : context->GetLocalVariables())
                        {
                            if (var->GetIdentifier().compare(m_identifier) == 0)
                                break;

                            if (var->GetIdentifier().compare("this") == 0)
                            {
                                foundThis = true;
                                break;
                            }
                        }
                        if (foundThis)
                        {
                            // Not a structure var
                            return std::move(v);
                        }

                        std::shared_ptr<Backend::CodeGen::IR::Variable> dstV = context->GetLocalVariable("this");
                        std::unique_ptr<Backend::CodeGen::IR::Variable> dst(new Backend::CodeGen::IR::Variable("this", dstV->GetType(), false));
                        std::unique_ptr<Backend::CodeGen::IR::Element> el(new Backend::CodeGen::IR::Element(std::move(dst), std::move(v)));

                        return std::move(el);
                    }

                    return std::move(v);
                }

                // Variable use
                std::shared_ptr<Backend::CodeGen::IR::Variable> var = context->GetLocalVariable(m_identifier);

                std::unique_ptr<Backend::CodeGen::IR::Variable> v(new Backend::CodeGen::IR::Variable(m_identifier, var->GetType(), false));
                v->SetLvalue(m_lvalue);
                return std::move(v);
            }

            if (m_identifier.empty())
            {
                if (m_args.size() > 0)
                {
                    m_identifier = m_args[0].second;

                    if (m_args.size() > 1)
                    {
                        if (m_args[1].first.compare("ptr") == 0)
                        {
                            m_ptr = true;
                        }
                        else
                        {
                            // Type
                            m_type = m_args[1].second;
                        }

                        if (m_args.size() > 2)
                        {
                            if (m_args[2].first.compare("type") == 0)
                            {
                                m_type = m_args[2].second;
                            }
                            else
                            {
                                // Number, array
                                m_num = m_args[2].second;
                            }
                        }
                    }
                }
                else
                {
                    printf("UNEXPECTED ERRROR IN FRONTEND::VARIABLE\n");
                }
            }

            if (m_dt.GetIdentifier().compare("empty") != 0)
            {
                std::unique_ptr<Backend::CodeGen::IR::Variable> v(new Backend::CodeGen::IR::Variable(m_identifier, m_dt, true));
                std::shared_ptr<Backend::CodeGen::IR::Variable> var(new Backend::CodeGen::IR::Variable(m_identifier, m_dt, true));
                context->AddLocalVar(var);
                return std::move(v);
            }


            Backend::CodeGen::IR::DT dt;
            // Check if type exists
            if (m_type.compare("int") == 0)
                dt = Backend::CodeGen::IR::Constant::GetInt32(m_ptr);
            else if (m_type.compare("short") == 0)
                dt = Backend::CodeGen::IR::DTInt(2, m_ptr);
            else if (m_type.compare("long") == 0)
                dt = Backend::CodeGen::IR::DTInt(8, m_ptr);
            else if (m_type.compare("byte") == 0)
                dt = Backend::CodeGen::IR::DTInt(1, m_ptr);
            else if (m_type.compare("string") == 0)
                dt = Backend::CodeGen::IR::DTString("");
            else
            {
                // Check if the type exist
                size_t byteCount = irGenerator.IsType(m_type);
                if (byteCount == 0)
                {
                    std::string s = "ERROR: Variable type: ";
                    s += m_type;
                    s += " does not exist!\n";
                    printf(s.c_str());
                    exit(1);
                }

                dt.SetIdentifier(m_type);
                dt.SetByteCount(0);
                dt.SetPtr(m_ptr);
            }

            if (context->GetLocalVariable(m_identifier))
            {
                std::string s = "ERROR: Variable: " + m_identifier + " is already declared!\n";
                printf(s.c_str());
                exit(1);
            }

            std::shared_ptr<Backend::CodeGen::IR::Variable> var(new Backend::CodeGen::IR::Variable(m_identifier, dt, true));
            context->AddLocalVar(var);

            if (!m_num.empty())
            {
                // Array
                std::unique_ptr<Backend::CodeGen::IR::Array> arr(new Backend::CodeGen::IR::Array(m_identifier, dt, std::stoi(m_num)));
                return std::move(arr);
            }

            std::unique_ptr<Backend::CodeGen::IR::Variable> v(new Backend::CodeGen::IR::Variable(m_identifier, dt, true));
            return std::move(v);
        }
    }
}