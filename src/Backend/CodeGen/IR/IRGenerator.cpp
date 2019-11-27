#include "IRGenerator.h"

namespace Backend::CodeGen::IR
{
    IRGenerator::IRGenerator() :
        m_globalSize(0), m_jmpTemp(0), m_tempNum(0)
    {
        m_functionTable = std::make_unique<FunctionTable>();
    }

    IRGenerator::~IRGenerator()
    {
        m_code.clear();
    }

    std::stringstream& IRGenerator::GetOutput()
    {
        return m_code;
    }

    void IRGenerator::AddFunction(std::shared_ptr<Value> function)
    {
        m_jmpTemp = 0;

        //m_functionTable->AddEntry(std::move(function));
        for (auto var : m_localVariables)
        {
            m_functionTable->ToArray().back()->AddLocalVariable(var);
        }
        m_localVariables.clear();
        // Generate Function

        std::string s;
        s += function->IR();
        m_code << s;
    }

    void IRGenerator::AddLocalVariable(std::shared_ptr<Variable> var)
    {
        m_localVariables.push_back(var);
    }

    std::shared_ptr<Variable> IRGenerator::GetLocalVariable(std::string name)
    {
        for (auto var : m_localVariables)
        {
            if (var->GetIdentifier().compare(name) == 0)
            {
                return var;
            }
        }

        return nullptr;
    }

    const std::string IRGenerator::AddGlobal(std::string_view type, std::string_view content)
    {
        return "";
    }

    std::unique_ptr<FunctionTable> IRGenerator::GetFunctionTable()
    {
        return std::move(m_functionTable);
    }

    const size_t IRGenerator::GetJmpTemp()
    {
        m_jmpTemp++;
        return m_jmpTemp - 1;
    }

    std::unique_ptr<Variable> IRGenerator::GenerateAdd(std::unique_ptr<Value> lhs, std::unique_ptr<Value> rhs)
    {
        //std::unique_ptr<Variable> var(new Variable("T0", DTAuto(), false));
        //m_code << var->GetIdentifier() << " = add " << lhs->IR() << " " << rhs->IR() << "\n";
        //return var;
        return nullptr;
    }

    void IRGenerator::GenerateStructure(std::unique_ptr<Structure> structure)
    {
        std::shared_ptr<Structure> strct = std::make_shared<Structure>(structure->GetId(), std::move(structure->GetBody()), structure->IsUnion());
        m_code << strct->IR();
        m_structures.push_back(strct);
    }

    void IRGenerator::RegisterType(DT dt)
    {
        m_types.push_back(dt);
    }

    void IRGenerator::ReRegisterType(DT dt)
    {
        for (auto& type : m_types)
        {
            if (dt.GetIdentifier().compare(type.GetIdentifier()) == 0)
                type = dt;
        }
    }

    size_t IRGenerator::IsType(std::string_view type)
    {
        for (auto t : m_types)
        {
            if (t.GetIdentifier().compare(type) == 0)
                return t.GetByteCount();
        }

        return 0;
    }

    bool IRGenerator::IsStructureType(std::string_view type)
    {
        for (auto t : m_types)
        {
            if (t.GetIdentifier().compare(type) == 0)
                return true;
        }

        return false;
    }
}
