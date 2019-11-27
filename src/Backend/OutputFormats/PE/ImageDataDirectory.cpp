#include "ImageDataDirectory.h"

namespace Backend::OutputFormats::PE
{
    ImageDataDirectory::ImageDataDirectory()
    {
    }

    ImageDataDirectory::~ImageDataDirectory()
    {
    }

    void ImageDataDirectory::Write(std::ofstream& stream)
    {
        m_exportTable.Write(stream);
        m_importTable.Write(stream);
    }

    void ImageDataDirectory::SetExportTable(ExportDirectoryTable table)
    {
        m_exportTable = table;
    }

    void ImageDataDirectory::SetImportTable(ImportDirectoryTable table)
    {
        m_importTable = table;
    }
}