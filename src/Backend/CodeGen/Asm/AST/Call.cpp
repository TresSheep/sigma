#include "Call.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>
#include "../Call.h"

namespace Backend::CodeGen::Asm::AST
{
    Call::Call(std::string identifier, std::string type, node_and_expr_args args) :
        m_identifier(identifier), m_args(std::move(args))
    {
    }

    Call::~Call()
    {
    }

    void Call::SetCallee(std::string name)
    {
        m_callee = name;
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Call::GenerateCode(Asm::AsmContext& context)
    {
        // Add arguments

        // Create call

        size_t offset = 0;

        std::vector<std::unique_ptr<Value>> args;

        for (auto& arg : m_args)
        {
            args.push_back(SyntaxToExpression(arg.first, context)->GenerateCode(context));
        }

        bool extrn = false;
        bool forward = false;
        for (auto func : context.GetFunctions())
        {
            if (m_identifier.compare(func->GetIdentifier()) == 0)
            {
                // Found function
                // Is it extern?
                extrn = func->IsExternal();

                if (!extrn)
                {
                    // Set offset
                    offset = func->GetOffset();
                }

                if (func->IsForward())
                {
                    forward = true;
                }
            }
        }

        std::unique_ptr<Asm::Call> call(new Asm::Call(m_identifier, std::move(args), extrn, forward, offset));

        return std::move(call);
    }
}
