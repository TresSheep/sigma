#include "Union.h"

namespace Frontend::AST
{
    Union::Union(std::string id, std::vector<std::unique_ptr<Expression>> body) :
        m_id(id), m_body(std::move(body))
    {
    }

    Union::~Union()
    {
    }


    std::unique_ptr<Backend::CodeGen::IR::Value> Union::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
    {
        std::vector<std::unique_ptr<Backend::CodeGen::IR::Value>> body;
        std::shared_ptr<Backend::CodeGen::IR::IRContext> con = std::make_shared<Backend::CodeGen::IR::IRContext>("union " + m_id);
        Backend::CodeGen::IR::DT dataType;
        dataType.SetIdentifier(m_id);
        dataType.SetByteCount(8);
        for (auto& part : m_body)
        {
            body.push_back(std::move(part->GenerateCode(con, irGenerator)));
        }

        std::unique_ptr<Backend::CodeGen::IR::Structure> structure(new Backend::CodeGen::IR::Structure(m_id, std::move(body), true));
        irGenerator.GenerateStructure(std::move(structure));
        irGenerator.RegisterType(dataType);
        return std::move(structure);
    }
}