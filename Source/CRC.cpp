// Joan Andrés (@Andres6936) Github.

#include <iostream>
#include <cstddef>

#include "Mong/CRC.hpp"

using namespace Mong;

CRC::CRC()
{
	for (int i = 0; i < table.size(); ++i)
	{
		UInt32 c = i << 24;

		for (int j = 0; j < 8; ++j)
		{
			if (c bitand 0x80'00'00'00)
			{
				c = (c << 1) xor 0x04'C1'1D'B7;
			}
			else
			{
				c = c << 1;
			}
		}

		table[i] = c;
	}
}

void CRC::showTable()
{
	std::cout << "\n\n";

	for (const auto& value : table)
	{
		std::cout << std::hex << value << "\n";
	}

	std::cout << "\n\n";
}

UInt32 CRC::getCyclicRedundancyCheck(const std::vector<std::byte>& _buffer) const
{
	UInt32 c = static_cast<UInt32>(0xFF'FF'FF'FF);

	for (int n = 0; n < _buffer.size(); ++n)
	{
		UInt8 byte = std::to_integer<UInt8>(_buffer.at(n));

		c = table.at((c xor byte) bitand 0xFF) xor (c >> 8);
	}

	return c xor static_cast<UInt32>(0xFF'FF'FF'FF);
}
