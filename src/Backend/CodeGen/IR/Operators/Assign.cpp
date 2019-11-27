#include "Assign.h"

namespace Backend::CodeGen::IR
{
    Assign::Assign(IRGenerator& irGenerator, std::shared_ptr<Value> lhs, std::shared_ptr<Value> rhs) :
        m_lhs(lhs), m_rhs(rhs), m_gen(irGenerator)
    {
        _identifier = m_lhs->GetIdentifier();
    }

    Assign::~Assign()
    {
    }

    const std::string Assign::IR()
    {
        std::string str;
        std::string s;
        s += m_lhs->IR();
        if (auto var = dynamic_cast<Variable*>(m_lhs.get()))
        {
            if (!var->GetType().OperEqu().empty())
            {
                if (s.find("decl") != std::string::npos)
                    str += m_lhs->IR() + "\n\t";
                str += var->GetType().OperEqu();
                str.pop_back(); // ")"
                // Add "this"
                str.append("address_of ");
                str.append(m_lhs->GetIdentifier().data());
                str.append(", ");
                str += m_rhs->IR();
                str += ")";
                return str.c_str();
            }
        }

        if (auto var = dynamic_cast<Variable*>(m_rhs.get()))
        {
            if (s.compare((m_rhs->IR())) == 0)
            {
                return "";
            }
            //str += m_rhs->IR() + "\n\t";
            str += "mov ";
            str += m_lhs->IR();
            str += " ";
            str += m_rhs->IR();
        }
        else
        {
            if (s.find("decl") != std::string::npos)
            {
                str += m_lhs->IR() + "\n\t";
                str += "mov ";
                str += m_lhs->GetIdentifier();
                str += " ";
                str += m_rhs->IR();
            }
            else
            {
                str += "mov ";
                str += m_lhs->IR();
                str += " ";
                str += m_rhs->IR();
                //if (str.find("mov " + m_lhs->IR() + " " + m_lhs->IR()) != std::string::npos)
                //{
                //    str.erase(0, str.find("\t") + 1);
                //}
            }
        }

        return str.c_str();
    }
}