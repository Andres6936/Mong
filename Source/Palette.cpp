// Joan Andrés (@Andres6936) Github.

#include <iostream>
#include <cstddef>

#include "Mong/Palette.hpp"

using namespace Mong;

Palette::Palette(const Chunk& _chunk) : PLTE(_chunk)
{
	if (verifyDivisibleBy3())
	{
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
			color.setRed(std::to_integer<UInt8>(*(it + 1)));
			color.setGreen(std::to_integer<UInt8>(*(it + 2)));
			color.setBlue(std::to_integer<UInt8>(*(it + 3)));

			// Advance 3 bytes
			it = std::next(it, 3);
		}

		std::cout << "Total of entries: " << entries.size() << "\n";
	}
	else
	{
		std::cerr << "Error: The chunk PLTE not is divisible by 3.\n";
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

void Palette::showEntries()
{
	for (const Color& color: entries)
	{
		std::cout << "R: " << (int) color.getRed() << " G: " << (int) color.getGreen() << " B: " << (int) color.getBlue() << "\n";
	}
}
