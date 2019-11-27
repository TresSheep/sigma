#include "Call.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>
#include <vector>
#include <memory>
#include <string>

namespace Backend::CodeGen::Asm
{
    Call::Call(std::string_view identifier, std::vector<std::unique_ptr<Value>> args, bool extrn, bool forward, size_t offset) :
        m_identifier(identifier), m_args(std::move(args)), m_extrn(extrn), m_offset(offset), m_forward(forward)
    {
    }

    Call::~Call()
    {
    }

    std::string_view Call::GetIdentifier()
    {
        return m_identifier;
    }

    ValueType Call::GetType()
    {
        return ValueType::CALL;
    }

    std::unique_ptr<Command::AsmValue> Call::Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        // Use fastcall if extern otherwise use sigma calling convention

        std::vector<uint8_t> bytes;
        std::vector<uint8_t> dataBytes;
        std::string debug;
        std::string dataDebug;
        std::unique_ptr<Command::AsmValue> b(new Command::AsmValue());

        // Mov variables

        size_t i = 0;
        for (auto& arg : m_args)
        {
            if (arg->GetType() == ValueType::CONST)
            {
                bool push = false;
                auto p = arg->Asm(writer, textPosition, dataPosition);
                std::vector<uint8_t> vec;
                if (m_extrn)
                {
                    if (p->size >= 8)
                    {
                        if (i == 0)
                            vec = Command::AsmMov<8>::GetBytes<Reg64::RCX>(p->offset);
                        else if (i == 1)
                            vec = Command::AsmMov<8>::GetBytes<Reg64::RDX>(p->offset);
                        else if (i == 2)
                            vec = Command::AsmMov<8>::GetBytes<Reg64::R8>(p->offset);
                        else if (i == 3)
                            vec = Command::AsmMov<8>::GetBytes<Reg64::R9>(p->offset);
                        else
                        {
                            // Push to stack
                            vec = Command::AsmMov<8>::GetBytes<Reg64::RSP>(p->offset, -(i * 8)); // TODO
                        }
                    }
                    else if (p->size <= 4)
                    {
                        if (i == 0)
                            vec = Command::AsmMov<4>::GetBytes<Reg32::ECX>(p->offset);
                        else if (i == 1)
                            vec = Command::AsmMov<4>::GetBytes<Reg32::EDX>(p->offset);
                        else if (i == 2)
                            vec = Command::AsmMov<4>::GetBytes<Reg32::R8D>(p->offset);
                        else if (i == 3)
                            vec = Command::AsmMov<4>::GetBytes<Reg32::R9D>(p->offset);
                        else
                        {
                            // Push to stack
                            vec = Command::AsmMov<4>::GetBytes<Reg32::ESP>(p->offset, -(i * 8)); // TODO
                        }
                    }
                }
                else
                {
                    if (i == 0)
                        vec = Command::AsmMov<8>::GetBytes<Reg64::RDI>(p->offset);
                    else if (i == 1)
                        vec = Command::AsmMov<8>::GetBytes<Reg64::R8>(p->offset);
                }

                bytes.insert(bytes.end(), vec.begin(), vec.end());
                if (p->size >= 8)
                    debug += Command::AsmMov<8>::GetDebug();
                else if (p->size <= 4)
                    debug += Command::AsmMov<4>::GetDebug();
            }
            else if (arg->GetType() == ValueType::VAR)
            {
                auto p = arg->Asm(writer, textPosition, dataPosition);

                bool lval = false;

                if (p->textDebug.compare("lval") == 0)
                    lval = true;

                std::vector<uint8_t> vec;
                if (m_extrn)
                {
                    if (p->size <= 4)
                    {
                        if (i == 0)
                        {
                            vec = Command::AsmMov<4>::GetBytes<Reg32::ECX, Reg32::EBP>(p->offset, lval);
                        }
                        else if (i == 1)
                            vec = Command::AsmMov<4>::GetBytes<Reg32::EDX, Reg32::EBP>(p->offset, lval);
                        else if (i == 2)
                            vec = Command::AsmMov<4>::GetBytes<Reg32::R8D, Reg32::EBP>(p->offset, lval);
                        else if (i == 3)
                            vec = Command::AsmMov<4>::GetBytes<Reg32::R9D, Reg32::EBP>(p->offset, lval);
                        else
                        {
                            // Push to stack
                        }
                    }
                    else
                    {
                        if (i == 0)
                        {
                            vec = Command::AsmMov<8>::GetBytes<Reg64::RCX, Reg64::RBP>(p->offset, lval);
                        }
                        else if (i == 1)
                            vec = Command::AsmMov<8>::GetBytes<Reg64::RDX, Reg64::RBP>(p->offset, lval);
                        else if (i == 2)
                            vec = Command::AsmMov<8>::GetBytes<Reg64::R8, Reg64::RBP>(p->offset, lval);
                        else if (i == 3)
                            vec = Command::AsmMov<8>::GetBytes<Reg64::R9, Reg64::RBP>(p->offset, lval);
                        else
                        {
                            // Push to stack
                        }
                    }
                }
                else
                {
                    if (i == 0)
                        vec = Command::AsmMov<8>::GetBytes<Reg64::RDI, Reg64::RBP>(p->offset, lval);
                    else if (i == 1)
                        vec = Command::AsmMov<8>::GetBytes<Reg64::R8, Reg64::RBP>(p->offset, lval);
                    else if (i == 2)
                        vec = Command::AsmMov<8>::GetBytes<Reg64::R9, Reg64::RBP>(p->offset, lval);
                    else if (i == 3)
                        vec = Command::AsmMov<8>::GetBytes<Reg64::R10, Reg64::RBP>(p->offset, lval);
                }

                bytes.insert(bytes.end(), vec.begin(), vec.end());
                if (p->size >= 8)
                    debug += Command::AsmMov<8>::GetDebug();
                else if (p->size <= 4)
                    debug += Command::AsmMov<4>::GetDebug();
            }
            else if (arg->GetType() == ValueType::STR)
            {
                // Create a new string
                // Assign it to rax
                // Insert proper argument

                auto p = arg->Asm(writer, textPosition, dataPosition);
                dataDebug = p->dataDebug;
                std::vector<uint8_t> vec = p->dataBytes;
                dataBytes.insert(dataBytes.end(), vec.begin(), vec.end());

                vec = Command::AsmMov<8>::GetBytes<Reg64::RAX>(p->textDebug, p->offset);
                bytes.insert(bytes.end(), vec.begin(), vec.end());
                //vec = p->textBytes;
                //bytes.insert(bytes.end(), vec.begin(), vec.end());
                debug += Command::AsmMov<8>::GetDebug();
                debug.pop_back(); // \n
                debug.pop_back(); // 0
                debug.pop_back();
                debug.pop_back();
                debug.pop_back();
                debug += p->textDebug;
                debug += "\n";

                vec.clear();

                //// Add string
                // pe.AddRelocation(".data", textPosition + bytes.size() - 4, OutputFormats::PE::ADDR64, ".text");
                writer.AddRelocation(textPosition + bytes.size() - 8, ".data", ADDR64, TEXT);

                if (m_extrn)
                {
                    if (i == 0)
                        vec = Command::AsmMov<8>::GetBytes<Reg64::RCX, Reg64::RAX, true>();
                    else if (i == 1)
                        vec = Command::AsmMov<8>::GetBytes<Reg64::RDX, Reg64::RAX, true>();
                    else if (i == 2)
                        vec = Command::AsmMov<8>::GetBytes<Reg64::R8, Reg64::RAX, true>();
                    else if (i == 3)
                        vec = Command::AsmMov<8>::GetBytes<Reg64::R9, Reg64::RAX, true>();
                    else
                    {
                        // Push to stack
                    }
                }
                else
                {
                    if (i == 0)
                        vec = Command::AsmMov<8>::GetBytes<Reg64::RDI, Reg64::RAX, true>();
                    else if (i == 1)
                        vec = Command::AsmMov<8>::GetBytes<Reg64::R8, Reg64::RAX, true>();
                    else if (i == 2)
                        vec = Command::AsmMov<8>::GetBytes<Reg64::R9, Reg64::RAX, true>();
                    else if (i == 3)
                        vec = Command::AsmMov<8>::GetBytes<Reg64::R10, Reg64::RAX, true>();
                }

                bytes.insert(bytes.end(), vec.begin(), vec.end());
                debug += Command::AsmMov<8>::GetDebug();
            }

            i++;
        }
 
        std::vector<uint8_t> vec;
        //if (m_extrn)
        //{
        //    // Allocate shadow space
        //    if ((i * 8) == 0)
        //    {
        //        vec = Command::AsmSub<Reg64>::GetBytes<Reg64::RSP>(32);
        //    }
        //    else
        //    {
        //        vec = Command::AsmSub<Reg64>::GetBytes<Reg64::RSP>(i * 8);
        //    }
        //    bytes.insert(bytes.end(), vec.begin(), vec.end());
        //    debug += Command::AsmSub<Reg64>::GetDebug();
        //}

        // Set offset
        int32_t offset = 0;
        if (!m_extrn && !m_forward)
            offset = textPosition - m_offset + bytes.size();

        std::string deb;
        vec = Command::call(m_identifier, -offset, deb);
        bytes.insert(bytes.end(), vec.begin(), vec.end());
        debug += deb + "\n";

        // Remove shadow space

        //size_t skipAdd = 0;
        //if (m_extrn)
        //{
        //    if ((i * 8) == 0)
        //    {
        //        vec = Command::AsmAdd<Reg64>::GetBytes<Reg64::RSP>(32);
        //    }
        //    else
        //    {
        //        vec = Command::AsmAdd<Reg64>::GetBytes<Reg64::RSP>(i * 8);
        //    }
        //    bytes.insert(bytes.end(), vec.begin(), vec.end());
        //    debug += Command::AsmAdd<Reg64>::GetDebug();
        //    skipAdd = vec.size();
        //}

        b->textDebug = debug;
        b->textBytes = bytes;
        b->dataBytes = dataBytes;
        b->dataDebug = dataDebug;

        // Add relocation
        if (m_extrn || m_forward)
        {
            // pe.AddRelocation(m_identifier, textPosition + b->textBytes.size(), OutputFormats::PE::REL32, ".text");
            writer.AddRelocation(textPosition + b->textBytes.size() - 4, m_identifier, REL32, TEXT);
        }

        return std::move(b);
    }
}

