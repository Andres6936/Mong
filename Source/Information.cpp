// Joan Andrés (@Andres6936) Github.

#include "Mong/Information.hpp"

#include <cstddef>
#include <bit>

using namespace Mong;

Information::Information(const Chunk& _chunk) : IHDR(_chunk)
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

UInt32 Information::readUInt32From4Bytes(ConstIterator _it)
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

UInt8 Information::readUInt8FromByte(ConstIterator _it)
{
	return std::to_integer<UInt8>(*_it);
}

bool Information::areVariantsSatisfied()
{
	if (isBitDepthValueValid() and isColorTypeValueValid())
	{
		// Bit depth restrictions for each color type are imposed
		// to simplify implementations and to prohibit combinations
		// that do not compress well. Decoders must support all valid
		// combinations of bit depth and color type.
		// The allowed combinations are:

		switch (colorType)
		{
		case 0:
			return isEachPixelGrayscaleSample();
		case 2:
			return isEachPixelRGBTriple();
		case 3:
			// Condition: A PLTE chunk must appear.
			return isEachPixelPaletteIndex();
		case 4:
			return isEachPixelGrayscaleSampleFollowedAlphaSample();
		case 6:
			return isEachPixelRGBTripleFollowedAlphaSample();
		default:
			return false;
		}
	}

	return false;
}

bool Information::isBitDepthValueValid()
{
	switch (bitDepth)
	{
	case 1:
	case 2:
	case 4:
	case 8:
	case 16:
		return true;
	default:
		return false;
	}
}

bool Information::isColorTypeValueValid()
{
	switch (colorType)
	{
	case 0:
	case 2:
	case 3:
	case 4:
	case 6:
		return true;
	default:
		return false;
	}
}

bool Information::isEachPixelGrayscaleSample()
{
	switch (bitDepth)
	{
	case 1:
	case 2:
	case 4:
	case 8:
	case 16:
		return true;
	default:
		return false;
	}
}

bool Information::isEachPixelRGBTriple()
{
	switch (bitDepth)
	{
	case 8:
	case 16:
		return true;
	default:
		return false;
	}
}

bool Information::isEachPixelPaletteIndex()
{
	switch (bitDepth)
	{
	case 1:
	case 2:
	case 4:
	case 8:
		return true;
	default:
		return false;
	}
}

bool Information::isEachPixelGrayscaleSampleFollowedAlphaSample()
{
	switch (bitDepth)
	{
	case 8:
	case 16:
		return true;
	default:
		return false;
	}
}

bool Information::isEachPixelRGBTripleFollowedAlphaSample()
{
	switch (bitDepth)
	{
	case 8:
	case 16:
		return true;
	default:
		return false;
	}
}
