// Joan Andrés (@Andres6936) Github.

#include "Mong/PNGInfo.hpp"

#include <cstddef>
#include <bit>

using namespace Mong;

PNGInfo::PNGInfo(const Chunk& _chunk) : IHDR(_chunk)
{
	// Iterator for read the data of chunk
	ConstIterator it = IHDR.getIterator();

	width = readUInt32From4Bytes(it);
	// Advance the iterator 4 bytes
	it = std::next(it, 4);

	height = readUInt32From4Bytes(it);
	// Advance the iterator 4 bytes
	it = std::next(it, 4);

	bitDepth = readUInt8FromByte(it);
	// Advance the iterator 1 byte
	it = std::next(it, 1);

	colorType = readUInt8FromByte(it);
	// Advance the iterator 1 byte
	it = std::next(it, 1);

	compressionMethod = readUInt8FromByte(it);
	// Advance the iterator 1 byte
	it = std::next(it, 1);

	filterMethod = readUInt8FromByte(it);
	// Advance the iterator 1 byte
	it = std::next(it, 1);

	interlaceMethod = readUInt8FromByte(it);

	// 13 Bytes in total reads.
}

UInt32 PNGInfo::readUInt32From4Bytes(ConstIterator _it)
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

UInt8 PNGInfo::readUInt8FromByte(ConstIterator _it)
{
	return std::to_integer<UInt8>(*_it);
}
