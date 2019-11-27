#pragma once

#include <string>

namespace Driver::Build
{
    enum class LINKERS
    {
        SIGMA,
        MS,
    };

    enum class TARGETS
    {
        X64,
    };

    enum class PLATFORMS
    {
        _WINDOWS,
        _LINUX
    };

    enum class TYPE
    {
        _DEBUG_,
        _RELEASE_
    };

    class BuildfileBuilder
    {
    public:
        BuildfileBuilder();
        ~BuildfileBuilder();

        void SetSrcPath(const std::string& path);
        void SetLibPath(const std::string& path);
        void SetBinPath(const std::string& path);

        void SetLinker(const LINKERS linker);
        void SetTarget(const TARGETS target);
        void SetPlatform(const PLATFORMS platform);
        void SetType(const TYPE type);

        void SetBinaryName(const std::string& name);

        const std::string& GetSrcPath();
        const std::string& GetLibPath();
        const std::string& GetBinPath();

        const LINKERS GetLinker();
        const TARGETS GetTarget();
        const PLATFORMS GetPlatform();
        const TYPE GetType();

        const std::string& GetBinaryName();

    private:
        std::string m_srcPath;
        std::string m_libPath;
        std::string m_binPath;
        LINKERS m_linker;
        TARGETS m_target;
        PLATFORMS m_platform;
        TYPE m_type;
        std::string m_binaryName;
    };
}