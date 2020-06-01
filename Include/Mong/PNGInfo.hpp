// Joan Andrés (@Andres6936) Github.

#ifndef MONG_PNGINFO_HPP
#define MONG_PNGINFO_HPP

#include "Chunk.hpp"
#include "Definitions.hpp"

namespace Mong
{

	class PNGInfo
	{

	private:

		UInt32 width = 0;
		UInt32 height = 0;
		UInt8 bitDepth = 0;
		UInt8 colorType = 0;
		UInt8 compressionMethod = 0;
		UInt8 filterMethod = 0;
		UInt8 interlaceMethod = 0;

		const Chunk IHDR;

	public:

		PNGInfo(const Chunk& _chunk);

		UInt32 readUInt32From4Bytes(ConstIterator _it);

		UInt8 readUInt8FromByte(ConstIterator _it);

	};

}

#endif //MONG_PNGINFO_HPP
