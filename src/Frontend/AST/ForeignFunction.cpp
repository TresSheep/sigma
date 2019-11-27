#include "ForeignFunction.h"

namespace Frontend
{
    namespace AST
    {
        ForeignFunction::ForeignFunction(std::unique_ptr<Prototype> proto) :
            m_proto(std::move(proto))
        {
        }

        ForeignFunction::~ForeignFunction()
        {
        }

        std::vector<std::unique_ptr<Expression>>& ForeignFunction::GetArguments()
        {
            return m_arguments;
        }

        void ForeignFunction::SetType(Backend::CodeGen::IR::DT type)
        {
            m_type = type;
        }

        std::string ForeignFunction::GetIdentifier()
        {
            return m_identifier;
        }

        Backend::CodeGen::IR::DT ForeignFunction::GetFunctionType()
        {
            return m_type;
        }

        std::unique_ptr<Backend::CodeGen::IR::Value> ForeignFunction::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
        {
            std::shared_ptr<Backend::CodeGen::IR::IRContext> con(new Backend::CodeGen::IR::IRContext("extern"));

            std::unique_ptr<Backend::CodeGen::IR::Function> func = std::move(m_proto->GenerateCode(con, irGenerator));
            if (!func)
            {
                printf("ERROR: Expected prototype\n");
            }

            func->SetExternal(true);

            irGenerator.AddFunction(std::move(func));
            return nullptr;
        }
    }
}