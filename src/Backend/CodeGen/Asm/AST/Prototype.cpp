#include "Prototype.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>

namespace Backend::CodeGen::Asm::AST
{
    Prototype::Prototype(std::string identifier, std::vector<std::pair<std::string, std::string>> args, std::string type) :
        m_identifier(identifier), m_args(std::move(args))
    {
    }
    
    Prototype::~Prototype()
    {
    }

    std::string Prototype::GetIdentifier()
    {
        return m_identifier;
    }

    std::unique_ptr<Asm::Function> Prototype::GenerateCode(Asm::AsmContext& context)
    {
        std::unique_ptr<Function> function(new Function(m_identifier));
        std::vector<std::shared_ptr<Asm::Variable>> args;

        if (!m_args.empty())
        {
            size_t i = 0;
            while (true)
            {
                if (m_args.size() < 3)
                {
                    std::unique_ptr<Asm::Variable> var(new Asm::Variable(m_args[i].second, m_args[i + 1].second));
                    var->SetPointer(false);
                    var->SetSize(context.TypeToSize(m_args[i + 1].second));
                    args.push_back(std::move(var));

                    Var v;
                    v.id = m_args[i].second;
                    v.type = m_args[i + 1].second;
                    v.size = TypeToSize(v.type);
                    v.ptr = false;
                    context.AddLocalItem(v);
                    break;
                }

                bool ptr = false;
                //if (m_args.size() > i)
                //    ptr = (m_args[i + 2].first.compare("ptr") == 0);

                try
                {
                    ptr = (m_args.at(i+2).first.compare("ptr") == 0);
                }
                catch (std::out_of_range e)
                {
                    ptr = false;
                }

                if (ptr)
                {
                    std::unique_ptr<Asm::Variable> var(new Asm::Variable(m_args[i].second, m_args[i + 1].second));
                    var->SetPointer(true);
                    var->SetSize(8);
                    args.push_back(std::move(var));

                    Var v;
                    v.id = m_args[i].second;
                    v.type = m_args[i + 1].second;
                    v.size = TypeToSize("i64"); // A pointer is 8 bytes (64 bits)
                    v.ptr = ptr;
                    context.AddLocalItem(v);

                    if (m_args.size() < (i + 4))
                        break;
                    else
                        i += 3;
                }
                else
                {
                    std::unique_ptr<Asm::Variable> var(new Asm::Variable(m_args[i].second, m_args[i + 1].second)); // Set size?
                    var->SetPointer(false);
                    var->SetSize(context.TypeToSize(m_args[i + 1].second));
                    args.push_back(std::move(var));

                    Var v;
                    v.id = m_args[i].second;
                    v.type = m_args[i + 1].second;
                    v.size = context.TypeToSize(v.type);
                    v.ptr = ptr;
                    context.AddLocalItem(v);

                    if (m_args.size() < (i + 3))
                        break;
                    else
                        i += 2;
                }
            }
        }

        function->AddVariableTable(args);
        function->SetArgs(args);
        return std::move(function);
    }
}
