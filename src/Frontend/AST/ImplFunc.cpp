#include "ImplFunc.h"

namespace Frontend
{
    namespace AST
    {
        ImplFunc::ImplFunc()
        {
        }

        ImplFunc::ImplFunc(std::vector<std::pair<std::string, std::string>> prototype)
        {
        }

        ImplFunc::ImplFunc(std::unique_ptr<Prototype> prototype, std::vector<std::unique_ptr<Expression>> body) :
            m_prototype(std::move(prototype)), m_body(std::move(body))
        {
        }

        std::string_view ImplFunc::GetIdentifier()
        {
            return m_prototype->GetIdentifier();
        }

        void ImplFunc::SetParent(std::string_view parent)
        {
            m_parent = parent;
        }

        std::unique_ptr<Backend::CodeGen::IR::Value> ImplFunc::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
        {
            std::shared_ptr<Backend::CodeGen::IR::IRContext> con(new Backend::CodeGen::IR::IRContext("entry"));
            con = context;

            std::string type = GetIdentifier().data();

            std::string id = m_parent += "__";
            id += m_prototype->GetIdentifier().data();
            m_prototype->SetIdentifier(id);

            m_prototype->SetImpl(true);

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

            if (type.compare("oper_equ") == 0)
            {
                return std::move(func);
            }

            irGenerator.AddFunction(std::move(func));

            return nullptr;
        }
    }
}
