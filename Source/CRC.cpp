// Joan Andrés (@Andres6936) Github.

#include <iostream>
#include <cstddef>

#include "Mong/CRC.hpp"

using namespace Mong;

CRC::CRC()
{
	for (int n = 0; n < table.size(); ++n)
	{
		UInt64 c = static_cast<UInt64>(n);

		for (int k = 0; k < 8; ++k)
		{
			if (c bitand 1)
			{
				c = 0xedb88320L xor (c >> 1);
			}
			else
			{
				c = c >> 1;
			}
		}

		table[n] = c;
	}
}

void CRC::showTable()
{
	std::cout << "\n\n";

	for (const auto& value : table)
	{
		std::cout << value << "\n";
	}

	std::cout << "\n\n";
}

UInt64 CRC::getCyclicRedundancyCheck(const std::vector<std::byte>& _buffer)
{
	UInt64 c = static_cast<UInt64>(0xFF'FF'FF'FF);

	for (int n = 0; n < table.size(); ++n)
	{
		UInt8 byte = std::to_integer<UInt8>(_buffer.at(n));

		c = table.at((c xor byte) bitand 0xFF) xor (c >> 8);
	}

	return c;
}
