#include "ExternFunction.h"

namespace Frontend
{
    namespace AST
    {
        ExternFunction::ExternFunction(std::unique_ptr<Prototype> proto) :
            m_proto(std::move(proto))
        {
        }

        ExternFunction::~ExternFunction()
        {
        }

        std::vector<std::unique_ptr<Expression>>& ExternFunction::GetArguments()
        {
            return m_arguments;
        }

        void ExternFunction::SetType(Backend::CodeGen::IR::DT type)
        {
            m_type = type;
        }

        std::string ExternFunction::GetIdentifier()
        {
            return m_identifier;
        }

        Backend::CodeGen::IR::DT ExternFunction::GetFunctionType()
        {
            return m_type;
        }

        std::unique_ptr<Backend::CodeGen::IR::Value> ExternFunction::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
        {
            std::shared_ptr<Backend::CodeGen::IR::IRContext> con(new Backend::CodeGen::IR::IRContext("forward"));

            std::unique_ptr<Backend::CodeGen::IR::Function> func = std::move(m_proto->GenerateCode(con, irGenerator));
            if (!func)
            {
                printf("ERROR: Expected prototype\n");
            }

            func->SetForward(true);

            irGenerator.AddFunction(std::move(func));
            return nullptr;
        }
    }
}