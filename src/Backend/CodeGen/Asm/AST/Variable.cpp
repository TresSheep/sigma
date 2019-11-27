#include "Variable.h"

namespace Backend::CodeGen::Asm::AST
{
    Variable::Variable(std::string id, std::string type, bool ptr, bool lval) :
        m_id(id), m_type(type), m_ptr(ptr), m_lval(lval)
    {
    }

    Variable::~Variable()
    {
    }

    void Variable::SetOfffset(size_t offset)
    {
        m_offset = offset;
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Variable::GenerateCode(Asm::AsmContext& context)
    {
        Var v = context.GetVar(m_id);
        if (v.id.compare("null") == 0)
        {
            std::string s = "ERROR: Unexpected variable: " + m_id + "!";
            printf(s.c_str());
            exit(1);
        }

        std::unique_ptr<Asm::Variable> variable(new Asm::Variable(m_id, m_type, m_ptr, m_lval));
        variable->SetSize(v.size);
        //variable->SetPointer(v.ptr);
        variable->SetOffset(v.position);
        return std::move(variable);
    }
}
