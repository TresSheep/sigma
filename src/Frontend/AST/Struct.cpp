#include "Struct.h"

namespace Frontend::AST
{
    Struct::Struct(std::string id, std::vector<std::unique_ptr<Expression>> body) :
        m_id(id), m_body(std::move(body))
    {
    }

    Struct::~Struct()
    {
    }


    std::unique_ptr<Backend::CodeGen::IR::Value> Struct::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
    {
        std::vector<std::unique_ptr<Backend::CodeGen::IR::Value>> body;
        std::shared_ptr<Backend::CodeGen::IR::IRContext> con = std::make_shared<Backend::CodeGen::IR::IRContext>(m_id, true);

        Backend::CodeGen::IR::DT dataType;
        dataType.SetIdentifier(m_id);
        dataType.SetByteCount(8);
        irGenerator.RegisterType(dataType);
        std::vector<std::unique_ptr<Backend::CodeGen::IR::Value>> functions;
        for (auto& part : m_body)
        {
            if (auto impl = dynamic_cast<ImplFunc*>(part.get()))
            {
                irGenerator.ReRegisterType(dataType);
                if (impl->GetIdentifier().compare("oper_equ") == 0)
                {
                    impl->SetParent(m_id);
                    // Generate Call to func
                    std::string name = m_id + "__";
                    name += impl->GetIdentifier().data();
                    std::unique_ptr<Backend::CodeGen::IR::Call> call(new Backend::CodeGen::IR::Call(name));
                    dataType.SetOperEqu(std::move(call));
                    functions.push_back(std::move(impl->GenerateCode(con, irGenerator)));
                }
            }
            else
                body.push_back(std::move(part->GenerateCode(con, irGenerator)));
        }
        irGenerator.ReRegisterType(dataType);

        std::unique_ptr<Backend::CodeGen::IR::Structure> structure(new Backend::CodeGen::IR::Structure(m_id, std::move(body)));
        irGenerator.GenerateStructure(std::move(structure));
        for (auto& func : functions)
        {
            irGenerator.AddFunction(std::move(func));
        }
        return std::move(structure);
    }
}