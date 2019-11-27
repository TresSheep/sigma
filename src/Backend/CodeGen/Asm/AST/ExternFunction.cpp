#include "ExternFunction.h"

namespace Backend::CodeGen::Asm::AST
{
    ExternFunction::ExternFunction(std::unique_ptr<Prototype> proto) :
        m_proto(std::move(proto))
    {
    }

    ExternFunction::~ExternFunction()
    {
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> ExternFunction::GenerateCode(Asm::AsmContext& context)
    {
        Asm::AsmContext temp;
        std::shared_ptr<Asm::Function> function = m_proto->GenerateCode(temp);
        function->SetExternal(true);
        // Args


        //asmWriter.AddFunction(std::move(function));
        context.AddFunction(function);

        return nullptr;
    }
}