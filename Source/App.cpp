// Design by Joan Andrés.

#include <iostream>
#include <cstddef>
#include <array>

#include "Mong/App.hpp"

using namespace Mong;

App::App(std::string_view _filename) : filename(_filename)
{

}

void App::run()
{
	try
	{
		dataRaw = readBinary(filename);
	}
	catch (std::exception& exception)
	{
		exception.what();
	}

	if (verifySignaturePNG())
	{
		readChunksFromDataRaw();
	}
}

bool App::verifySignaturePNG()
{
	if (dataRaw[0] == std::byte(137) and
		dataRaw[1] == std::byte(80) and
		dataRaw[2] == std::byte(78) and
		dataRaw[3] == std::byte(71) and
		dataRaw[4] == std::byte(13) and
		dataRaw[5] == std::byte(10) and
		dataRaw[6] == std::byte(26) and
		dataRaw[7] == std::byte(10) )
	{
		return true;
	}

	return false;
}

void App::readChunksFromDataRaw()
{
	using ConstIterator = std::vector<std::byte>::const_iterator;
	using Byte4 = std::byte;

	// Advance and skip the signature
	ConstIterator iterator = dataRaw.cbegin() + 8;

	Byte4 lengthChunk = *(iterator + 0) | *(iterator + 1) | *(iterator + 2) | *(iterator + 3);

	std::cout << "Length: " << std::to_integer<int>(lengthChunk) << "\n";

	std::array<std::byte, 4> typeChunk;

	typeChunk[0] = *(iterator + 4);
	typeChunk[1] = *(iterator + 5);
	typeChunk[2] = *(iterator + 6);
	typeChunk[3] = *(iterator + 7);

	for(auto b : typeChunk)
		std::cout << std::to_integer<char>(b) << "\n";
}
