#pragma once

// Intermediate code generator

#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <fstream>
#include "FunctionTable.h"
#include "Structure.h"

namespace Backend::CodeGen::IR
{
    class IRGenerator
    {
    public:
        IRGenerator();
        ~IRGenerator();

        std::stringstream& GetOutput();

        void AddFunction(std::shared_ptr<Value> function);
        void AddLocalVariable(std::shared_ptr<Variable> var);
        std::shared_ptr<Variable> GetLocalVariable(std::string name);
        const std::string AddGlobal(std::string_view type, std::string_view content);
        void GenerateStructure(std::unique_ptr<Structure> structure);

        std::unique_ptr<FunctionTable> GetFunctionTable();

        const size_t GetJmpTemp();

        std::unique_ptr<Variable> GenerateAdd(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs);

        const size_t GetTempVarNum()
        {
            m_tempNum++;
            return m_tempNum - 1;
        }

        void RegisterType(DT dt);
        void ReRegisterType(DT dt);
        DT GetType(std::string_view type)
        {
            for (auto t : m_types)
            {
                if (t.GetIdentifier().compare(type) == 0)
                    return t;
            }

            DT dt;
            dt.SetIdentifier("empty");
            return dt;
        }
        size_t IsType(std::string_view type);
        bool IsStructureType(std::string_view type);

        std::vector<std::shared_ptr<Structure>>& GetStructures()
        {
            return m_structures;
        }

    private:
        std::stringstream m_code;
        std::unique_ptr<FunctionTable> m_functionTable;
        std::vector<std::shared_ptr<Variable>> m_localVariables;
        size_t m_globalSize;
        size_t m_jmpTemp;
        size_t m_tempNum;
        std::vector<DT> m_types;
        std::vector<std::shared_ptr<Structure>> m_structures;
    };
}