// Joan Andrés (@Andres6936) Github.

#include <iostream>
#include "Mong/Palette.hpp"

using namespace Mong;

Palette::Palette(const Chunk& _chunk) : PLTE(_chunk)
{
	if (verifyDivisibleBy3())
	{
		std::cout << "The Chunk PLTE is divisible by 3.\n";
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
