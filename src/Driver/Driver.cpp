#include "Driver.h"

namespace Driver
{
    Driver::Driver()
    {
    }

    Driver::~Driver()
    {
    }

    bool Driver::ParseFile(std::string file, uint32_t flags, std::string name)
    {
        auto start = std::chrono::high_resolution_clock::now();

        // Parse buildfile
        ::Driver::Build::Lexer lexer(file);
        Build::BuildfileBuilder bfb;
        Build::AbstractSyntaxTree<Build::BuildfileBuilder> ast(lexer.GetTokenStream(), bfb);

        // Sources
        std::vector<std::string> files;
        std::string srcPath = bfb.GetSrcPath();
        for (auto& file : std::filesystem::directory_iterator(srcPath))
        {
            if (file.path().generic_string().find(".si") != std::string::npos)
            {
                files.push_back(file.path().generic_string());
                CompileFile(file.path().generic_string(), flags);
                std::cout << "> " << file.path().generic_string() << " Succeeded!" << std::endl;
            }
        }

        // Libraries
        std::vector<std::string> libs;
        std::string libPath = bfb.GetLibPath();
        for (auto& file : std::filesystem::directory_iterator(libPath))
        {
            if ((file.path().generic_string().find(".lib") != std::string::npos) || (file.path().generic_string().find(".a") != std::string::npos))
                libs.push_back(file.path().generic_string());
        }

        Link(bfb, files, libs);

        auto current = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time = current - start;

        if (flags & TIME)
        {
            std::cout << std::endl;
            std::cout << "[Total compile] time: " << time.count() << "sec";
            std::cout << std::endl;
        }

        return true;
    }

    bool Driver::CompileFile(std::string file, uint32_t flags)
    {
        // Preprocess
        Frontend::Preprocessor::Lexer lex(file);
        Frontend::Preprocessor::Generator gen;
        m_include.insert(m_include.end(), lex.GetFilesToLink().begin(), lex.GetFilesToLink().end());
        //Frontend::Preprocessor::AbstractSyntaxTree<Frontend::Preprocessor::Generator> tree(lex.GetTokenStream(), gen);

        std::stringstream stream;

        stream << lex.GetStream().rdbuf();

        // Frontend
        auto start = std::chrono::high_resolution_clock::now();
        Lexer lexer(stream);
        Backend::CodeGen::IR::IRGenerator irGenerator;
        Frontend::LexicalAnalysis::AbstractSyntaxTree ast(lexer.GetTokenStream(), irGenerator);

        if (flags & VERBOSE)
        {
            std::string str = irGenerator.GetOutput().str();
            std::cout << "---------- [ Intermediate Code Output ] ----------" << std::endl << std::endl;
            std::cout << str << std::endl;
        }

        auto current = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time = current - start;

        if (flags & TIME)
        {
            std::cout << "[Frontend] time: " << time.count() << "sec";
        }

        Backend::CodeGen::Asm::Lexer irToAsmLexer(irGenerator.GetOutput());

        file.pop_back();
        file.pop_back();
        file.pop_back();
        file.append(".o");
        // TODO: Make builder available here
        Backend::CodeGen::Asm::AsmContext con; // Global context
        Backend::CodeGen::Asm::AbstractSyntaxTree astBackend(irToAsmLexer.GetTokenStream(), con);
        //writer.generate_assembly();

        //Backend::CodeGen::Asm::AsmWriter<Backend::OutputFormats::PE::PE> writer(file, true);
        std::unique_ptr<Backend::CodeGen::Asm::ObjectFile<Backend::OutputFormats::PE::PE>> obj(
            new Backend::CodeGen::Asm::ObjectFile<Backend::OutputFormats::PE::PE>(file, false));
        obj->GetContextInfo(con);
        obj->Save();

        current = std::chrono::high_resolution_clock::now();
        time = current - start;

        if (flags & TIME)
        {
            std::cout << std::endl;
            std::cout << "[Backend] time: " << time.count() << "sec";
            std::cout << std::endl;
        }

        m_files.push_back(std::move(obj));

        return true;
    }

    bool Driver::Link(Build::BuildfileBuilder& builder, std::vector<std::string> files, std::vector<std::string> libs)
    {
        // Link

        // Choose linker
        if (builder.GetLinker() == Build::LINKERS::SIGMA)
        {
            // Sigma linker
#ifdef WINDOWS
            Backend::Linker::Linker<Backend::OutputFormats::PE::PE> sigmaLinker("b:/sigma/test/bin/output.exe");

            sigmaLinker.AddLib("C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.17763.0\\um\\x64\\kernel32.lib");
            sigmaLinker.AddLib("opengl32.lib");
            for (auto lib : libs)
            {
                sigmaLinker.AddLib(lib.data());
            }

            for (auto& f : m_files)
            {
                sigmaLinker.AddFile(f->GetFormat());
            }

            sigmaLinker.Write();
#endif

            return true;
        }
        else if (builder.GetLinker() == Build::LINKERS::MS)
        {
            // MS linker

#ifndef WINDOWS
#error "MS linker only available in Windows"
#endif
            std::cout << "Linking...";

            std::string link;
            link.append("link");
            for (auto file : files)
            {
                file.pop_back(); // p
                file.pop_back(); // e
                file.pop_back(); // .

                link.append(" " + file + ".o ");
            }
            std::vector<std::string> included;
            bool found = false;
            for (auto include : m_include)
            {
                include.pop_back();
                include.pop_back();
                include.pop_back();

                for (auto i : included)
                {
                    if (i.compare(include) == 0)
                        found = true;
                }
                if (!found)
                {
                    CompileFile(include + ".si", 0);
                    link.append(include + ".o ");
                }

                included.push_back(include);
            }
            if (builder.GetType() == Build::TYPE::_DEBUG_)
            {
                link.append("/DEBUG ");
            }
            link.append("/SUBSYSTEM:CONSOLE /LARGEADDRESSAWARE:NO /NOLOGO /ENTRY:main /nodefaultlib /cgthreads:4 ");
            link.append("kernel32.lib opengl32.lib ");
            for (auto lib : libs)
            {
                link.append(lib + " ");
            }
            link.append("/LIBPATH:\"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.17763.0\\um\\x64\" ");
            link.append("/OUT:" + builder.GetBinPath() + builder.GetBinaryName() + ".exe");

            std::string str = "if not exist bin ( mkdir bin )";
            std::system(str.c_str());
            std::system(link.c_str());

            std::cout << std::endl;
        }
        return true;
    }

    bool Driver::ParseInclude(std::string file)
    {
        return true;
    }
}
