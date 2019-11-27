#include "Decl.h"

namespace Backend::CodeGen::Asm::AST
{
    Decl::Decl(std::string id, std::string type, std::string ptr) :
        m_id(id), m_type(type)
    {
        if (ptr.empty())
            m_ptr = false;
        else
            m_ptr = true;
    }

    Decl::~Decl()
    {
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Decl::GenerateCode(Asm::AsmContext& context)
    {
        size_t size = 0;
        if (m_type.compare("i8") == 0)
            size = 1;
        else if (m_type.compare("i16") == 0)
            size = 2;
        else if (m_type.compare("i32") == 0)
            size = 4;
        else
        {
            for (auto type : context.GetTypes())
            {
                if (type.id.compare(m_type) == 0)
                    size = type.size;
            }
        }

        if (m_ptr)
            size = 8;

        Var var;
        var.id = m_id;
        var.type = m_type;
        var.size = size;
        var.ptr = m_ptr;

        context.AddLocalItem(var);
        return nullptr;
    }
}
