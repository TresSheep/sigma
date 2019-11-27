#include "Function.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>

namespace Backend::CodeGen::Asm::AST
{
    Function::Function()
    {
    }

    Function::Function(std::unique_ptr<Prototype> proto, std::vector<std::unique_ptr<Expression>> body) :
        m_proto(std::move(proto)), m_body(std::move(body))
    {
    }

    Function::~Function()
    {
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Function::GenerateCode(Asm::AsmContext& context)
    {
        // COPY GLOBAL CONTEXT TO con
        Asm::AsmContext con = context;

        std::shared_ptr<Asm::Function> function = m_proto->GenerateCode(con);
        for (auto& part : m_body)
        {
            if (auto block = dynamic_cast<Block*>(part.get()))
            {
                block->SetParent(function->GetIdentifier().data());
            }
            function->Body.push_back(std::move(part->GenerateCode(con)));
        }

        function->SetVariableSize(con.GetCurrentVariablePosition());
        //asmWriter.AddFunction(std::move(function));
        context.AddFunction(function);
        return nullptr;
    }
}
