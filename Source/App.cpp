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
	// Skip the initial signature of 8 bytes
	ConstIterator iterator = dataRaw.cbegin() + 8;

	bool isEndChunk = false;

	while (not isEndChunk)
	{
		const UInt32 lengthChunk = getLengthChunk(iterator);

		std::cout << "Length: " << lengthChunk << "\n";

		// Advance the 4 bytes of Chunk Length
		iterator = std::next(iterator, 4);

		const std::string typeChunk = getTypeChunk(iterator);

		std::cout << "Type: " << typeChunk << "\n";

		// Advance the 4 bytes of Chunk Type
		iterator = std::next(iterator, 4);

		if (lengthChunk not_eq 0)
		{
			std::vector<std::byte> dataChunk(iterator, iterator + lengthChunk);

			// Advance the length of chunk
			iterator = std::next(iterator, lengthChunk);
		}

		const UInt32 crcChunk = getCyclicRedundancyCheck(iterator);

		std::cout << "CRC:" << crcChunk << "\n\n";

		// Advance the 4 bytes of CRC Chunk
		iterator = std::next(iterator, 4);

		// Verify if the actual chunk is IEND,
		if (typeChunk == "IEND") isEndChunk = true;
	}
}

UInt32 App::getLengthChunk(ConstIterator _it)
{
	// Read the 4 bytes
	const Byte4 lengthChunk = *(_it + 0) | *(_it + 1) | *(_it + 2) | *(_it + 3);

	return std::to_integer<UInt32>(lengthChunk);
}

std::string App::getTypeChunk(App::ConstIterator _it)
{
	// Read the 4 bytes
	Int8 letter1 = std::to_integer<Int8>(*(_it + 0));
	Int8 letter2 = std::to_integer<Int8>(*(_it + 1));
	Int8 letter3 = std::to_integer<Int8>(*(_it + 2));
	Int8 letter4 = std::to_integer<Int8>(*(_it + 3));

	return { letter1, letter2, letter3, letter4 };
}

UInt32 App::getCyclicRedundancyCheck(App::ConstIterator _it)
{
	// Read the 4 bytes
	const Byte4 crcChunk = *(_it + 0) | *(_it + 1) | *(_it + 2) | *(_it + 3);

	return std::to_integer<UInt32>(crcChunk);
}
