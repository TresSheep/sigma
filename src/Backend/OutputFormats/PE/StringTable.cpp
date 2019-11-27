#include "StringTable.h"
#include <stdint.h>
#include <vector>
#include <fstream>
#include <string>


namespace Backend::OutputFormats::PE
{
	StringTable::StringTable() :
		m_stringTable(0)
	{
	}

	StringTable::~StringTable()
	{
	}

	// Returns the offset
	int32_t StringTable::AddString(std::string str)
	{
		int32_t ret = 0;
		for (std::string str : m_stringTable)
		{
			ret += str.length();
		}

		m_stringTable.push_back(str);
		m_stringTable.back() += '\0';

		return ret;
	}

	void StringTable::Write(std::ofstream& stream)
	{
		// String table size
		int32_t size = sizeof(int32_t);
		for (auto str : m_stringTable)
		{
			size += str.length();
		}
		stream.write(reinterpret_cast<char*>(&size), sizeof(int32_t));

		// String table
		for (std::string entry : m_stringTable)
		{
			stream.write(entry.c_str(), entry.length());
		}
	}
}
