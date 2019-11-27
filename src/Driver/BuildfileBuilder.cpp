#include "BuildfileBuilder.h"

namespace Driver::Build
{
    BuildfileBuilder::BuildfileBuilder()
    {
    }

    BuildfileBuilder::~BuildfileBuilder()
    {
    }

    void BuildfileBuilder::SetSrcPath(const std::string& path)
    {
        m_srcPath = path;
    }

    void BuildfileBuilder::SetLibPath(const std::string& path)
    {
        m_libPath = path;
    }

    void BuildfileBuilder::SetBinPath(const std::string& path)
    {
        m_binPath = path;
    }

    void BuildfileBuilder::SetLinker(const LINKERS linker)
    {
        m_linker = linker;
    }

    void BuildfileBuilder::SetTarget(const TARGETS target)
    {
        m_target = target;
    }

    void BuildfileBuilder::SetPlatform(const PLATFORMS platform)
    {
        m_platform = platform;
    }

    void BuildfileBuilder::SetType(const TYPE type)
    {
        m_type = type;
    }

    void BuildfileBuilder::SetBinaryName(const std::string& name)
    {
        m_binaryName = name;
    }

    const std::string& BuildfileBuilder::GetSrcPath()
    {
        return m_srcPath;
    }

    const std::string& BuildfileBuilder::GetLibPath()
    {
        return m_libPath;
    }

    const std::string& BuildfileBuilder::GetBinPath()
    {
        return m_binPath;
    }

    const LINKERS BuildfileBuilder::GetLinker()
    {
        return m_linker;
    }

    const TARGETS BuildfileBuilder::GetTarget()
    {
        return m_target;
    }

    const PLATFORMS BuildfileBuilder::GetPlatform()
    {
        return m_platform;
    }

    const TYPE BuildfileBuilder::GetType()
    {
        return m_type;
    }

    const std::string& BuildfileBuilder::GetBinaryName()
    {
        return m_binaryName;
    }
}