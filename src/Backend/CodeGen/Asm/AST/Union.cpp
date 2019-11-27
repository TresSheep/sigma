#include "Union.h"

namespace Backend::CodeGen::Asm::AST
{
    Union::Union(std::string id, std::vector<std::unique_ptr<Expression>> body) :
        m_id(id), m_body(std::move(body))
    {
    }

    Union::~Union()
    {
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Union::GenerateCode(Asm::AsmContext& context)
    {
        // Add structure

        Asm::AsmContext con;

        size_t size = 0;
        std::vector<Var> vars;
        for (auto& var : m_body)
        {
            if (auto v = dynamic_cast<Decl*>(var.get()))
            {
                v->GenerateCode(con);
                Var var = con.GetLastVariable();
                if (var.size > size)
                    size = var.size;
                vars.push_back(var);
            }
            else if (auto arr = dynamic_cast<Array*>(var.get()))
            {
                arr->GenerateCode(con);
                _Array a = con.GetLastArray();
                if (a.arraySize > size)
                    size = a.arraySize;
                vars.push_back(a);
            }
            else
            {
                printf("ERROR: For now unions only accept variables and arrays\n");
                exit(1);
            }
        }
        //asmWriter.AddStructure(m_id, vars);

        Type u;
        u.id = m_id;
        u.size = size;

        for (auto v : vars)
        {
            if (v.size > size)
                size = v.size;

            u.members.push_back(v);
        }

        context.AddType(u);
        return nullptr;
    }
}
