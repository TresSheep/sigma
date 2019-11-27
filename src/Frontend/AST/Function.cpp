#include "Function.h"

namespace Frontend
{
    namespace AST
    {
        Function::Function()
        {
        }

        Function::Function(std::vector<std::pair<std::string, std::string>> prototype)
        {
        }

        Function::Function(std::unique_ptr<Prototype> prototype, std::vector<std::unique_ptr<Expression>> body) :
            m_prototype(std::move(prototype)), m_body(std::move(body))
        {
        }

        std::unique_ptr<Backend::CodeGen::IR::Value> Function::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
        {
            std::shared_ptr<Backend::CodeGen::IR::IRContext> con(new Backend::CodeGen::IR::IRContext("entry"));

            std::unique_ptr<Backend::CodeGen::IR::Function> func = std::move(m_prototype->GenerateCode(con, irGenerator));
            if (!func)
            {
                printf("ERROR: Expected prototype\n");
            }

            func->SetExternal(false);

            std::unique_ptr<Backend::CodeGen::IR::Block> block(new Backend::CodeGen::IR::Block("entry"));
            func->Body.push_back(std::move(block));

            bool retFound = false;
            for (auto& expr : m_body)
            {
                if (auto ret = dynamic_cast<Return*>(expr.get()))
                {
                    retFound = true;
                }
                func->Body.push_back(std::move(expr->GenerateCode(con, irGenerator)));
            }

            if (!func->IsExternal())
            {
                if (func->GetFunctionType().ToEnum() != Backend::CodeGen::IR::Void)
                {
                    if (!retFound)
                    {
                        std::string s = "ERROR: Expected return in function: ";
                        s += func->GetIdentifier();
                        printf(s.c_str());
                        exit(1);
                    }
                }
            }

            irGenerator.AddFunction(std::move(func));
            return nullptr;
        }
    }
}
