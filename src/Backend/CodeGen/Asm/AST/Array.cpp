#include "Array.h"

namespace Backend::CodeGen::Asm::AST
{
    Array::Array(const std::string& type, const std::string& id, const std::string& size) :
        m_type(type), m_id(id), m_size(size)
    {
    }

    Array::~Array()
    {
    }

    std::unique_ptr<Backend::CodeGen::Asm::Value> Array::GenerateCode(Asm::AsmContext& context)
    {
        _Array a = context.GetArray(m_id);
        if (a.size == -1)
        {
            Asm::_Array arr;
            arr.id = m_id;
            arr.type = m_type;
            if (arr.type.compare("i8") == 0)
                arr.size = 1;
            else if (arr.type.compare("i32") == 0)
                arr.size = 4;
            arr.arraySize = std::stol(m_size);
            arr.ptr = false;
            context.AddLocalItem(arr);
        }


        _Array aUsage = context.GetArray(m_id);

        // Usage
        std::unique_ptr<Asm::Array> arr(new Asm::Array(aUsage.position, aUsage.size));

        return std::move(arr);
    }
}
