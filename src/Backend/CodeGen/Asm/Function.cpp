#include "Function.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>
#include "Variable.h"
#include <Backend/OutputFormats/PE/PE.h>
#include <Backend/OutputFormats/PE/Relocation.h>
#include <vector>
#include <memory>
#include "Value.h"
#include "CodeBlock.h"
#include <utility>

namespace Backend::CodeGen::Asm
{
    Function::Function(std::string_view identifier) :
        m_identifier(identifier), m_position(0), m_extrn(false), m_size(0), m_forward(false)
    {
    }

    Function::~Function()
    {
    }

    void Function::AddVariableTable(std::vector<std::shared_ptr<Variable>> vars)
    {
        m_variableTable.insert(m_variableTable.end(), vars.begin(), vars.end());
    }

    void Function::SetPosition(uint32_t pos)
    {
        m_position = pos;
        m_offset = pos;
    }

    void Function::SetVariableSize(size_t size)
    {
        m_size = size;
    }

    std::unique_ptr<Command::AsmValue>Function::Asm(AsmWriter& asmWriter)
    {
        std::unique_ptr<Command::AsmValue> value(new Command::AsmValue());
        std::string textDebug;
        std::string dataDebug;
        std::string globalDebug;
        std::vector<uint8_t> textBytes;
        std::vector<uint8_t> dataBytes;
        std::vector<uint8_t> debugBytes;

        size_t dataPosition = 0;

        if (m_extrn || m_forward)
        {
            globalDebug += "extern " + m_identifier + "\n";
            asmWriter.AddSymbolExternal(m_identifier);
        }
        else
        {
            globalDebug += "global " + m_identifier + "\n";
            asmWriter.AddSymbolGlobal(m_identifier, m_position);

            textDebug += m_identifier + ":\n";

            textBytes.push_back(Command::AsmPush<Reg64>::GetByte<Reg64::RBP>());
            textDebug += Command::AsmPush<Reg64>::GetDebug();
            m_position += 1;

            std::vector<uint8_t> ret = Command::AsmMov<8>::GetBytes<Reg64::RBP, Reg64::RSP, true>();
            textDebug += Command::AsmMov<8>::GetDebug();
            m_position += ret.size();
            textBytes.insert(textBytes.end(), ret.begin(), ret.end());

            while ((m_size % 16) != 0)
            {
                m_size++;
            }

            if (m_size < 48)
                m_size = 48;

            ret = Command::AsmSub<Reg64>::GetBytes<Reg64::RSP>(m_size);
            textDebug += Command::AsmSub<Reg64>::GetDebug();
            m_position += ret.size();
            textBytes.insert(textBytes.end(), ret.begin(), ret.end());

            // Arguments
            size_t i = 0;
            size_t offset = 0;
            for (auto& arg : m_args)
            {
                if (i == 0)
                {
                    // RDI
                    if (arg->GetSize() == 4)
                    {
                        //// DWORD
                        ret = Command::AsmMov<4>::GetBytes<Reg32::EBP, Reg32::EDI, true>(offset + 4);
                        textDebug += Command::AsmMov<4>::GetDebug();
                        m_position += ret.size();
                        textBytes.insert(textBytes.end(), ret.begin(), ret.end());

                        offset += 4;
                    }
                    if (arg->GetSize() >= 8)
                    {
                        //// QWORD
                        ret = Command::AsmMov<8>::GetBytes<Reg64::RBP, Reg64::RDI, true>(offset + 8);
                        textDebug += Command::AsmMov<8>::GetDebug();
                        m_position += ret.size();
                        textBytes.insert(textBytes.end(), ret.begin(), ret.end());

                        offset += 8;
                    }
                }
                if (i == 1)
                {
                    // R8
                    if (arg->GetSize() == 4)
                    {
                    }
                    if (arg->GetSize() == 8)
                    {
                        //// QWORD
                        ret = Command::AsmMov<8>::GetBytes<Reg64::RBP, Reg64::R8, true>(offset + 8);
                        textDebug += Command::AsmMov<8>::GetDebug();
                        m_position += ret.size();
                        textBytes.insert(textBytes.end(), ret.begin(), ret.end());

                        offset += 8;
                    }
                }
                i++;
            }

            AsmWriter dummy;
            size_t tempPos = m_position;
            // Dummy Body
            for (auto& part : Body)
            {
                if (part)
                {
                    // Get label position
                    if (auto label = dynamic_cast<CodeBlock*>(part.get()))
                    {
                        m_labels.push_back(std::pair<std::string, size_t>(label->GetIdentifier(), m_position));
                    }
                    auto p = part->Asm(dummy, m_position, dataPosition);
                    if (p)
                    {
                        std::vector<uint8_t> vec = p->textBytes;
                        m_position += vec.size();
                    }
                }
            }

            m_position = tempPos;
            // Body
            for (auto& part : Body)
            {
                if (part)
                {
                    // Set offset for jump
                    if (auto jmp = dynamic_cast<Jump*>(part.get()))
                    {
                        for (auto label : m_labels)
                        {
                            if (label.first.compare(jmp->GetIdentifier()) == 0)
                            {
                                jmp->SetPosition(label.second - m_position);
                            }
                        }
                    }
                    auto p = part->Asm(asmWriter, m_position, dataPosition);
                    if (p)
                    {
                        std::vector<uint8_t> vec = p->textBytes;
                        std::vector<uint8_t> dataVec = p->dataBytes;

                        m_position += vec.size();
                        dataPosition += dataVec.size();

                        textDebug += p->textDebug;
                        dataDebug += p->dataDebug;

                        textBytes.insert(textBytes.end(), vec.begin(), vec.end());
                        dataBytes.insert(dataBytes.end(), dataVec.begin(), dataVec.end());
                    }
                }
            }

            if (m_identifier.compare("main") == 0)
            {
                //std::vector<uint8_t> ret = Command::xor(RDI, debug);
                //position += ret.size();
                //m_dText += debug;
                ret.clear();
                textBytes.insert(textBytes.end(), ret.begin(), ret.end());

                globalDebug += "extern ExitProcess\n";
                asmWriter.AddSymbolExternal("ExitProcess");

                std::string debug;
                ret = Command::call("ExitProcess", 0, debug);
                m_position += ret.size();
                textDebug += debug;
                textBytes.insert(textBytes.end(), ret.begin(), ret.end());

                asmWriter.AddRelocation(m_position - 4, "ExitProcess", REL32, TEXT);

                //std::unique_ptr<OutputFormats::PE::Relocation> reloc(new OutputFormats::PE::Relocation());
                //reloc->SetVirtualAddress(m_position - 4);
                //reloc->SetSymbolTableIndex(pe.GetRelocIndex("ExitProcess"));
                //reloc->SetType(OutputFormats::PE::REL32);

                //m_relocs.push_back(std::move(reloc));
            }

            std::string debug;
            ret = Command::leave(debug);
            m_position += ret.size();
            textDebug += debug;
            textBytes.insert(textBytes.end(), ret.begin(), ret.end());

            ret = Command::ret(debug);
            m_position += ret.size();
            textDebug += debug;
            textBytes.insert(textBytes.end(), ret.begin(), ret.end());
        }

        value->textBytes = textBytes;
        value->dataBytes = dataBytes;
        value->debugBytes = debugBytes;
        value->textDebug = textDebug;
        value->dataDebug = dataDebug;
        value->globalDebug = globalDebug;

        return std::move(value);
    }

    std::vector<std::unique_ptr<OutputFormats::PE::Relocation>> Function::GetRelocs()
    {
        return std::move(m_relocs);
    }

    std::string_view Function::GetIdentifier()
    {
        return m_identifier;
    }

    void Function::SetExternal(bool extrn)
    {
        m_extrn = extrn;
    }

    void Function::SetArgs(std::vector<std::shared_ptr<Variable>> args)
    {
        m_variableTable.insert(m_variableTable.end(), args.begin(), args.end());
        m_args = args;
    }

    bool Function::IsExternal()
    {
        return m_extrn;
    }
}

