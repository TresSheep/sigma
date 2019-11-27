#pragma once

#include "Lexer.h"
#include "AbstractSyntaxTree.h"

#include <filesystem>

#include <codecvt>

#include <string>
#include <Frontend/LexicalAnalysis/Lexer.h>
#include <Frontend/LexicalAnalysis/AbstractSyntaxTree.h>

#include <Backend/CodeGen/IR/IRGenerator.h>

#include <Backend/CodeGen/Asm/AsmWriter.h>
#include <Backend/CodeGen/Asm/Lexer.h>
#include <Backend/CodeGen/Asm/AbstractSyntaxTree.h>

#include <Frontend/Preprocessor/Lexer.h>
#include <Frontend/Preprocessor/AbstractSyntaxTree.h>
#include <Frontend/Preprocessor/Generator.h>

#include <Backend/Linker/Linker.h>

#include <Backend/CodeGen/Asm/ObjectFile.h>

#include <Driver/BuildfileBuilder.h>

#include <chrono>

// Command line flags. Will be moved to a separate file. Ex (CLI.cpp, CLI.h)
enum CLIFLAGS
{
    VERBOSE = 0x01,
    TIME = 0x02,
    _OUT = 0x04
};

namespace Driver
{
    class Driver
    {
    public:
        Driver();
        ~Driver();

        bool ParseFile(std::string file, uint32_t flags, std::string name);
        bool CompileFile(std::string file, uint32_t flags);
        bool Link(Build::BuildfileBuilder& builder, std::vector<std::string> files, std::vector<std::string> libs);
        bool ParseInclude(std::string file);

    private:
        std::vector<std::string> m_include;
        size_t m_includePos;
        std::vector<std::unique_ptr<Backend::CodeGen::Asm::ObjectFile<Backend::OutputFormats::PE::PE>>> m_files;
    };
}
