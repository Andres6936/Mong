// Joan Andrés (@Andres6936) Github.

#include <iostream>
#include <cstddef>

#include "Mong/Palette.hpp"

using namespace Mong;

Palette::Palette(const Chunk& _chunk) : PLTE(_chunk)
{
	if (verifyDivisibleBy3())
	{
		std::cout << "The Chunk PLTE is divisible by 3.\n";
		// According to standard: The PLTE chunk contains from
		// 1 to 256 palette entries, each a three-byte series.
		// The number of entries is determined from the chunk
		// length.
		entries.resize(PLTE.getLength() / 3);

		ConstIterator it = PLTE.getIteratorBegin();

		for (Color& color : entries)
		{
			// Read the three bytes of data, that represent
			// the component red, green and blue
			color.setRed(std::to_integer<UInt8>(*(it + 0)));
			color.setGreen(std::to_integer<UInt8>(*(it + 1)));
			color.setBlue(std::to_integer<UInt8>(*(it + 2)));

			// Advance 3 bytes
			std::next(it, 3);
		}
	}
	else
	{
		std::cout << "Error: The chunk PLTE not is divisible by 3.\n";
	}
}

bool Palette::verifyDivisibleBy3()
{
	if (PLTE.getLength() % 3 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
