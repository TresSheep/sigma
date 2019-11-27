#include "ForwardFunction.h"

namespace Backend::CodeGen::Asm::AST
{
    ForwardFunction::ForwardFunction(std::unique_ptr<Prototype> proto) :
        m_proto(std::move(proto))
    {
    }

    ForwardFunction::~ForwardFunction()
    {
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> ForwardFunction::GenerateCode(Asm::AsmContext& context)
    {
        Asm::AsmContext temp;
        std::shared_ptr<Asm::Function> function = m_proto->GenerateCode(temp);
        function->SetForward(true);
        // Args


        //asmWriter.AddFunction(std::move(function));
        context.AddFunction(function);

        return nullptr;
    }
}