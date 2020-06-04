// Joan Andrés (@Andres6936) Github.

#include <iostream>
#include <cstddef>

#include "Mong/CRC.hpp"

using namespace Mong;

CRC::CRC()
{
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

	verifyInvariants();
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

bool CRC::verifyInvariants() const
{
	// 32 Bytes of Zeros

	std::vector<std::byte> buffer;

	buffer.push_back(std::byte('a'));

	UInt32 bytesZeros = getCyclicRedundancyCheck(buffer);

	std::cout << std::hex << bytesZeros << "\n";

	return false;
}
