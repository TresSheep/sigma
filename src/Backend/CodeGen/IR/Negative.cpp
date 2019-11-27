#include "Negative.h"

namespace Backend::CodeGen::IR
{
    Negative::Negative(std::unique_ptr<Value> expr) :
        m_expr(std::move(expr))
    {
        _identifier = "%";
    }

    Negative::~Negative()
    {
    }

    const std::string Negative::IR()
    {
        if (auto num = dynamic_cast<DTInt*>(m_expr.get()))
        {
            std::string s = "i32 -";
            s += num->GetValue();
            return s.c_str();
        }
        else
        {
            printf("ERROR: Negatives only work on numbers!");
            exit(1);
        }
        return "";
    }
}