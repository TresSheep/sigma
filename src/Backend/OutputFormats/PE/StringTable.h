#pragma once

#include <stdint.h>
#include <vector>
#include <fstream>
#include <string>

namespace Backend::OutputFormats::PE
{
	class StringTable
	{
	public:
		StringTable();
		~StringTable();

		int32_t AddString(std::string str);

		void Write(std::ofstream& stream);

	private:
		std::vector<std::string> m_stringTable;
	};
}
