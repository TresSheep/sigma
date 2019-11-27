#pragma once

#include <vector>
#include <string>
#include <type_traits>
#include "Function.h"
#include "Types.h"

namespace Backend::CodeGen::Asm
{

    class AsmContext
    {
    public:
        AsmContext();
        ~AsmContext();

        void AddFunction(std::shared_ptr<Function> func);

        void AddLocalItem(Var t)
        {
            m_currentPos += t.size;
            t.position = m_currentPos;
            m_variables.push_back(t);
            m_items.push_back(t);
        }

        void AddLocalItem(_Array a)
        {
            m_currentPos += a.arraySize * a.size;
            a.position = m_currentPos;
            m_arrays.push_back(a);
            m_items.push_back(a);
        }

        void AddType(Type u)
        {
            m_types.push_back(u);
        }

        size_t TypeToSize(std::string_view type)
        {
            if (type.compare("i32") == 0)
                return 4;

            for (auto t : m_types)
            {
                if (t.id.compare(type) == 0)
                {
                    return t.size;
                }
            }

            return -1;
        }

        //Var GetLocalVariable(std::string_view s)
        //{
        //    for (auto var : m_variables)
        //    {
        //        if (var.id.compare(s) == 0)
        //            return var;
        //    }

        //    Var v;
        //    v.size = -1;
        //    return v;
        //}
        //
        //_Array GetLocalArray(std::string_view s)
        //{
        //    for (auto arr : m_arrays)
        //    {
        //        if (arr.id.compare(s) == 0)
        //            return arr;
        //    }
        //    _Array arr;
        //    arr.size = -1;
        //    return arr;
        //}

        Var GetLastVariable()
        {
            Var v = m_variables.back();
            m_currentPos -= v.size;
            m_variables.pop_back();
            return v;
        }

        _Array GetLastArray()
        {
            _Array v = m_arrays.back();
            m_currentPos -= v.size;
            m_arrays.pop_back();
            return v;
        }

        //Item GetItem(std::string_view s)
        //{
        //    for (auto item : m_items)
        //    {
        //        if (item.id.compare(s) == 0)
        //            return item;
        //    }

        //    Item i;
        //    i.id = "null";
        //    return i;
        //}

        Var GetVar(std::string_view s)
        {
            for (auto var : m_variables)
            {
                if (var.id.compare(s) == 0)
                    return var;
            }

            Var v;
            v.size = -1;
            return v;
        }

        _Array GetArray(std::string_view s)
        {
            for (auto a : m_arrays)
            {
                if (a.id.compare(s) == 0)
                    return a;
            }

            _Array a;
            a.size = -1;
            return a;
        }

        Type GetType(std::string_view s)
        {
            for (auto a : m_types)
            {
                if (a.id.compare(s) == 0)
                    return a;
            }

            Type a;
            a.size = -1;
            return a;
        }

        const std::vector<Type>& GetTypes()
        {
            return m_types;
        }

        void SetLabelPosition(std::pair<std::string, size_t> label);

        size_t GetCurrentVariablePosition();

        const std::vector<std::shared_ptr<Function>>& GetFunctions()
        {
            return m_functions;
        }

    private:
        std::vector<Var> m_variables;
        std::vector<_Array> m_arrays;
        std::vector<Item> m_items;
        size_t m_currentPos;
        size_t m_functionOffset;
        std::vector<std::pair<std::string, size_t>> m_labels;
        std::vector<std::shared_ptr<Function>> m_functions;

        std::vector<Type> m_types;
    };
}
