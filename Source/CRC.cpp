// Joan Andrés (@Andres6936) Github.

#include <iostream>
#include <cstddef>

#include "Mong/CRC.hpp"

using namespace Mong;

CRC::CRC()
{
	// The following sample code represents a practical
	// implementation of the CRC (Cyclic Redundancy Check)
	// employed in PNG chunks.

	// See also ISO 3309 [ISO-3309] or ITU-T V.42 [ITU-T-V42]
	// for a formal specification.

	for (int n = 0; n < table.size(); ++n)
	{
		UInt32 c = n;

		for (int k = 0; k < 8; ++k)
		{
			if (c bitand 1)
			{
				c = (c >> 1) xor 0xEDB88320;
			}
			else
			{
				c = (c >> 1) xor 0;
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
		std::cout << std::hex << value << "\n";
	}

	std::cout << "\n\n";
}

UInt32 CRC::getCyclicRedundancyCheck(const std::vector<std::byte>& _buffer) const
{
	UInt32 c = 0xFF'FF'FF'FF;

	for (int n = 0; n < _buffer.size(); ++n)
	{
		UInt8 byte = std::to_integer<UInt8>(_buffer.at(n));

		c = table.at((c xor byte) bitand 0xFF) xor (c >> 8);
	}

	return c xor 0xFF'FF'FF'FF;
}
