#pragma once

#include <fstream>
#include <stdint.h>
#include <string>
#include "AuxSymbol.h"

namespace Backend::OutputFormats::PE
{
	class AuxSymbolFilename : public AuxSymbol
	{
	public:
		AuxSymbolFilename();
		~AuxSymbolFilename();

		void SetFilename(const char* filename);

        void Write(std::ofstream& stream) override;

	private:
		int8_t m_filename[18];
	};
}
