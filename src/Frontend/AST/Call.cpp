#include "Call.h"

namespace Frontend
{
    namespace AST
    {
        Call::Call(std::string identifier, node_and_expr_args arguments) :
            m_identifier(identifier), m_arguments(std::move(arguments))
        {
        }

        Call::~Call()
        {
        }

        std::string Call::GetIdentifier()
        {
            return m_identifier;
        }
        
        std::unique_ptr<Backend::CodeGen::IR::Value> Call::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
        {
            std::unique_ptr<Backend::CodeGen::IR::Call> call(new Backend::CodeGen::IR::Call(m_identifier));

            for (auto& arg : m_arguments)
            {
                if (arg.second)
                {
                    call->AddArg(std::move(arg.second->GenerateCode(context, irGenerator)));
                }
                else
                {
                    size_t i = 0;
                    while (true)
                    {
                        if (arg.first.size() == 0)
                            break;

                        if (arg.first[i].first.compare("id") == 0)
                        {
                            bool lvalue = false;
                            if (arg.first.size() -1 > 0 && arg.first[i - 1].first.compare("lval") == 0)
                                lvalue = true;
                            std::unique_ptr<Variable> arg(new Variable(arg.first[i].second));
                            arg->SetLvalue(lvalue);
                            call->AddArg(arg->GenerateCode(context, irGenerator));
                        }
                        else if (arg.first[i].first.compare("str") == 0)
                        {
                            std::unique_ptr<String> str(new String(arg.first[i].second));
                            call->AddArg(str->GenerateCode(context, irGenerator));
                        }
                        else if (arg.first[i].first.compare("num") == 0)
                        {
                            std::unique_ptr<Number> num(new Number(arg.first[i].second));
                            call->AddArg(num->GenerateCode(context, irGenerator));
                        }

                        if (i + 1 < arg.first.size())
                            i++;
                        else
                            break;
                    }
                }
            }

            return call;
        }
    }
}
