#include "AuxSymbolFilename.h"

namespace Backend::OutputFormats::PE
{
	AuxSymbolFilename::AuxSymbolFilename() :
		m_filename()
	{
	}

	AuxSymbolFilename::~AuxSymbolFilename()
	{
	}

	void AuxSymbolFilename::SetFilename(const char* filename)
	{
		memcpy(m_filename, filename, sizeof(m_filename));
	}

	void AuxSymbolFilename::Write(std::ofstream& stream)
	{
		stream.write(reinterpret_cast<char*>(&m_filename), sizeof(int8_t[18]));
	}
}
