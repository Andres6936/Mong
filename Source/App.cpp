// Design by Joan Andrés.

#include <iostream>
#include <cstddef>
#include <array>
#include <bitset>

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
	// Advance and skip the signature
	ConstIterator iterator = dataRaw.cbegin() + 8;

	const UInt32 lengthChunk = getLengthChunk(iterator);

	std::cout << "Length: " << lengthChunk << "\n";

	const Byte4 typeChunk = *(iterator + 4) | *(iterator + 5) | *(iterator + 6) | *(iterator + 7);

	std::cout << "Type: " << std::to_integer<UInt32>(typeChunk) << "\n";
}

UInt32 App::getLengthChunk(ConstIterator _it)
{
	// Read the first 4 bytes
	const Byte4 lengthChunk = *(_it + 0) | *(_it + 1) | *(_it + 2) | *(_it + 3);

	return std::to_integer<UInt32>(lengthChunk);
}
