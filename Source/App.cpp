// Design by Joan Andrés.

#include <iostream>
#include <cstddef>
#include <bitset>
#include <bit>

#include "Mong/CRC.hpp"
#include "Mong/App.hpp"
#include "Mong/Palette.hpp"
#include "Mong/Information.hpp"

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

	if (verifyChunkOrdering())
	{
		std::cout << "The order of chunks is correct.\n";
	}
	else
	{
		std::cout << "The order of chunks is incorrect.\n";
	}

	if (verifyCRCForAllChunks())
	{
		std::cout << "All Chunk with Cyclic Redundancy Check (CRC) Correct.\n";
	}
	else
	{
		std::cout << "Error with Cyclic Redundancy Check (CRC).\n";
	}

	readImageHeader();
}

bool App::verifySignaturePNG()
{
	// (decimal) 			 137 80 78 71 13 10 26 10
	// (hexadecimal) 		  89 50 4e 47 0d 0a 1a 0a
	// (ASCII C notation) 	\211 P N G \r \n \032 \n

	// This signature both identifies the file as a PNG file
	// and provides for immediate detection of common
	// file-transfer problems.

	// The first two bytes distinguish PNG files on
	// systems that expect the first two bytes to identify the
	// file type uniquely.

	// The first byte is chosen as a non-ASCII
	// value to reduce the probability that a text file may be
	// mis-recognized as a PNG file; also, it catches bad file
	// transfers that clear bit 7.

	// Bytes two through four name the format.

	// The CR-LF sequence catches bad file transfers
	// that alter newline sequences.

	// The control-Z character stops file display under MS-DOS.

	// The final line feed checks for the inverse of the CR-LF
	// translation problem.

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

		std::vector<std::byte> dataChunk(iterator, iterator + lengthChunk);

		// Advance the length of chunk
		iterator = std::next(iterator, lengthChunk);

		const UInt32 crcChunk = getCyclicRedundancyCheck(iterator);

		std::cout << "CRC:" << crcChunk << "\n";

		// Advance the 4 bytes of CRC Chunk
		iterator = std::next(iterator, 4);

		Chunk chunk;

		chunk.setLength(lengthChunk);
		chunk.setType(typeChunk);
		chunk.setData(dataChunk);
		chunk.setCyclicRedundancyCheck(crcChunk);
		chunk.determineProperties();
		chunk.printProperties();

		chunks.push_back(chunk);

		std::cout << "\n\n";

		// Verify if the actual chunk is IEND,
		if (typeChunk == "IEND") isEndChunk = true;
	}
}

UInt32 App::getLengthChunk(ConstIterator _it)
{
	return readUInt32From4Bytes(_it);
}

std::string App::getTypeChunk(ConstIterator _it)
{
	// Read the 4 bytes
	Int8 letter1 = std::to_integer<Int8>(*(_it + 0));
	Int8 letter2 = std::to_integer<Int8>(*(_it + 1));
	Int8 letter3 = std::to_integer<Int8>(*(_it + 2));
	Int8 letter4 = std::to_integer<Int8>(*(_it + 3));

	return { letter1, letter2, letter3, letter4 };
}

UInt32 App::getCyclicRedundancyCheck(ConstIterator _it)
{
	return readUInt32From4Bytes(_it);
}

UInt32 App::readUInt32From4Bytes(ConstIterator _it)
{
	// Read the 4 bytes
	UInt8 byte1 = std::to_integer<UInt8>(*(_it + 0));
	UInt8 byte2 = std::to_integer<UInt8>(*(_it + 1));
	UInt8 byte3 = std::to_integer<UInt8>(*(_it + 2));
	UInt8 byte4 = std::to_integer<UInt8>(*(_it + 3));

	// Prepare the space for save the 4 bytes
	UInt32 result = 0;

	if constexpr (std::endian::native == std::endian::little)
	{
		result += byte1 << 24;
		result += byte2 << 16;
		result += byte3 << 8;
		result += byte4 << 0;
	}
	else if constexpr (std::endian::native == std::endian::big)
	{
		// Implement Big Endian
	}

	return result;
}

void App::readImageHeader()
{
	Information info(chunks.at(0));

	if (info.areVariantsSatisfied())
	{
		std::cout << "Yes, variant satisfied.\n";
	}
	else
	{
		std::cout << "No, variant unsatisfied.\n";
	}
}

bool App::verifyCRCForAllChunks()
{
	CRC crc;

	for (const auto& chunk : chunks)
	{
		if (chunk.verifyCyclicRedundancyCheck(crc))
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool App::verifyChunkOrdering()
{
	// Standard: The IDHR should be the first chunk.
	if (not chunks.at(0).equalsTypeTo("IHDR"))
	{
		return false;
	}

	// Rest 1 because begin to count from 0
	const auto LAST_POSITION = chunks.size() - 1;

	// Standard: The IEDN should be the last chunk.
	if (not chunks.at(LAST_POSITION).equalsTypeTo("IEND"))
	{
		return false;
	}

	return true;
}

std::optional<App::ConstIteratorChunk> App::findChunkType(std::string_view _type)
{
	// Search from the begin to end of vector
	ConstIteratorChunk it = std::find_if(chunks.cbegin(), chunks.cend(),
			// The element that coincide with we criteria
			// In this case, that the chunk will be of type pass for parameter
			[&](const Chunk& _chunk){return _chunk.equalsTypeTo(_type);});

	// If std::find_if not found the element,
	// it return a iterator a the last position,
	// you can think that the last position is
	// a element valid, however we have as convention
	// that the last element is a chunk of type IEND
	// that not is used in the program more that for
	// mark the end of png
	if (it == chunks.cend())
	{
		// Element not found, return null
		return std::nullopt;
	}
	else
	{
		// Deduce of template C++17
		return std::optional{it};
	}
}

void App::readImagePalette()
{
	std::optional<ConstIteratorChunk> it = findChunkType("PLTE");

	if (it)
	{
		// Remember, we use a optional, the way of get the value
		// in a std::optional is of two ways: the first is using
		// the operator * and the second is using the method value()

		// Remember, the optional store a reference valid to iterator,
		// and the way of get the value to which the iterator point is
		// with the operator *

		// So, that is valid two syntax: *(it.value()) and *(*it)
		// Which is more clear?

		Palette palette(*(it.value()));
	}
	else
	{
		// Not exist chunk of type PLTE
		return;
	}
}
