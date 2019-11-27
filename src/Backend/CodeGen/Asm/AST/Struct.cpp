#include "Struct.h"

namespace Backend::CodeGen::Asm::AST
{
    Struct::Struct(std::string id, std::vector<std::unique_ptr<Expression>> body) :
        m_id(id), m_body(std::move(body))
    {
    }

    Struct::~Struct()
    {
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Struct::GenerateCode(Asm::AsmContext& context)
    {
        // Add structure

        Asm::AsmContext con;

        std::vector<Var> vars;
        size_t size = 0;
        for (auto& var : m_body)
        {
            if (auto v = dynamic_cast<Decl*>(var.get()))
            {
                v->GenerateCode(con);
                vars.push_back(con.GetLastVariable());

                // Get the size to calculate
                size += vars.back().size;
            }
            else if (auto arr = dynamic_cast<Array*>(var.get()))
            {
                arr->GenerateCode(con);
            }
            else
            {
                printf("ERROR: For now structs only accept variables and arrays\n");
                exit(1);
            }
        }
        //asmWriter.AddStructure(m_id, vars);
        Type strct;
        strct.id = m_id;
        strct.size = size;
        for (auto var : vars)
            strct.members.push_back(var);

        context.AddType(strct);

        return nullptr;
    }
}
