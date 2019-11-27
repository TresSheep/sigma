#include "String.h"
#include <Backend/CodeGen/Asm/Commands/Commands.h>
#include <vector>
#include <memory>
#include <string>
#include <stdint.h>
#include "Registers.h"

namespace Backend::CodeGen::Asm
{
    String::String(std::string_view str) :
        m_str(str)
    {
    }

    String::~String()
    {
    }

    ValueType String::GetType()
    {
        return ValueType::STR;
    }

    std::unique_ptr<Command::AsmValue> String::Asm(AsmWriter& writer, size_t textPosition, size_t dataPosition)
    {
        std::string name = "str" + std::to_string(Command::StringNumber);
        Command::StringNumber++;

        std::unique_ptr<Command::AsmValue> data(new Command::AsmValue());
        bool special = false;
        for (char c : m_str)
        {
            if (c == '\\')
            {
                special = true;
            }
            else
            {
                if (special)
                {
                    if (c == 'n')
                    {
                        data->dataBytes.push_back(0x0A);
                        special = false;
                    }
                }
                else
                {
                    data->dataBytes.push_back(c);
                }
            }
        }
        data->dataBytes.push_back(0x00);
        data->offset = dataPosition;
        data->dataDebug = name + ": db '" + m_str + "', 0x00\n";
        data->textDebug = name;

        writer.AddSymbol(name, dataPosition, DATA);

        Command::Int64ToBytes conv = { 0 };
        conv.number = dataPosition;

        data->textBytes.push_back(conv.bytes[0]);
        data->textBytes.push_back(conv.bytes[1]);
        data->textBytes.push_back(conv.bytes[2]);
        data->textBytes.push_back(conv.bytes[3]);
        data->textBytes.push_back(conv.bytes[4]);
        data->textBytes.push_back(conv.bytes[5]);
        data->textBytes.push_back(conv.bytes[6]);
        data->textBytes.push_back(conv.bytes[7]);

        return std::move(data);
    }
}
