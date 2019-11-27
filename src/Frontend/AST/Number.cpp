#include "Number.h"

namespace Frontend::AST
{
    Number::Number(std::string number) :
        m_number(number)
    {
    }

    Number::~Number()
    {
    }

    Backend::CodeGen::IR::DT Number::DetectType(std::string number)
    {
        if (number.find(".") != std::string::npos)
        {
            // Double or float
            if (number.back() == 'f')
            {
                return Backend::CodeGen::IR::Constant::GetFloat();
            }
            else
            {
                return Backend::CodeGen::IR::Constant::GetDouble();
            }
        }
        else
        {
            // Default to int32
            return Backend::CodeGen::IR::Constant::GetInt32();
        }
    }

    void Number::SetType(Backend::CodeGen::IR::DT type)
    {
        m_type = type;
    }

    std::unique_ptr<Backend::CodeGen::IR::Value> Number::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
    {
        m_type = DetectType(m_number);

        std::unique_ptr<Backend::CodeGen::IR::DTInt> number(new Backend::CodeGen::IR::DTInt(4));
        number->SetValue(m_number);

        return std::move(number);
    }
}