#include "If.h"

namespace Frontend::AST
{
    If::If(std::unique_ptr<Log> log, std::vector<std::unique_ptr<Expression>> body) :
        m_log(std::move(log)), m_body(std::move(body)), m_repeat(false)
    {
    }

    If::~If()
    {
    }

    void If::SetRepeat(bool repeat)
    {
        m_repeat = repeat;
    }

    std::unique_ptr<Backend::CodeGen::IR::Value> If::GenerateCode(std::shared_ptr<Backend::CodeGen::IR::IRContext> context, Backend::CodeGen::IR::IRGenerator& irGenerator)
    {
        size_t tempNum = irGenerator.GetTempVarNum();

        std::string_view parentContextName = context->GetName();

        std::unique_ptr<Backend::CodeGen::IR::Jump> jmp(new Backend::CodeGen::IR::Jump("resume" + std::to_string(tempNum)));

        switch (m_log->GetType())
        {
        case LogType::Equ:
            jmp->SetType(Backend::CodeGen::IR::JumpCommands::jne);
            break;
        case LogType::Neq:
            jmp->SetType(Backend::CodeGen::IR::JumpCommands::je);
            break;
        }

        std::unique_ptr<Backend::CodeGen::IR::Value> expr = std::move(m_log->GenerateCode(context, irGenerator));

        // Add entry context to temp_if%

        std::vector<std::unique_ptr<Backend::CodeGen::IR::Value>> body;

        std::unique_ptr<Backend::CodeGen::IR::Block> block(new Backend::CodeGen::IR::Block("L" + std::to_string(tempNum), true));

        body.push_back(std::move(expr));
        body.push_back(std::move(jmp));
        std::shared_ptr<Backend::CodeGen::IR::IRContext> con(new Backend::CodeGen::IR::IRContext("L" + std::to_string(tempNum)));
        con->SetParent(context);

        // Copy entry context to if-context

        for (auto var : context->GetLocalVariables())
        {
            con->AddLocalVar(var);
        }

        for (auto& part : m_body)
        {
            body.push_back(part->GenerateCode(con, irGenerator));
        }


        if (m_repeat)
        {
            // Repeat
            std::unique_ptr<Backend::CodeGen::IR::Jump> j(new Backend::CodeGen::IR::Jump("L" + std::to_string(tempNum)));
            j->SetType(Backend::CodeGen::IR::JumpCommands::jmp);
            body.push_back(std::move(j));
        }

        std::unique_ptr<Backend::CodeGen::IR::Block> b(new Backend::CodeGen::IR::Block("resume" + std::to_string(tempNum)));
        body.push_back(std::move(b));
        block->AddBody(std::move(body));

        return std::move(block);
    }
}