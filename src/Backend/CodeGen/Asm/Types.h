#pragma once

namespace Backend::CodeGen::Asm
{
    enum Types
    {
        int8 = 1,
        int16 = 2,
        int32 = 4,
        Auto = 0,
    };

    static Types AsmStringToType(std::string_view str)
    {
        if (str.compare("int8") == 0)
            return int8;
        if (str.compare("int16") == 0)
            return int16;
        if (str.compare("int32") == 0)
            return int32;
        if (str.compare("auto") == 0)
            return Auto;

        return Auto;
    }

    typedef struct _Item
    {
        std::string id;
        size_t size;
    } Item;

    typedef struct _Var : public Item
    {
        std::string type;
        size_t position;
        bool ptr;
    } Var;

    typedef struct _Array : public Var
    {
        size_t arraySize;
    } _Array;

    typedef struct _Type : public Item
    {
        std::vector<Item> members;
    } Type;
}
