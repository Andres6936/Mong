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

		/**
		 * Width the image dimensions in pixels.
		 *
		 * @note Zero is an invalid value.
		 */
		UInt32 width = 0;

		/**
		 * Height the image dimensions in pixels.
		 *
		 * @note Zero is an invalid value.
		 */
		UInt32 height = 0;

		/**
		 * Bit depth is the number of bits per sample
		 * or per palette index (not per pixel).
		 *
		 * @note Valid values are 1, 2, 4, 8, and 16,
		 * although not all values are allowed for
		 * all color types.
		 */
		UInt8 bitDepth = 0;

		/**
		 * Color type describes the interpretation of the
		 * image data. Color type codes represent sums of
		 * the following values: 1 (palette used),
		 * 2 (color used), and 4 (alpha channel used).
		 *
		 * @note Valid values are 0, 2, 3, 4, and 6.
		 */
		UInt8 colorType = 0;

		/**
		 * Compression method indicates the method used to
		 * compress the image data. At present, only compression
		 * method 0 (deflate/inflate compression with a sliding
		 * window of at most 32768 bytes) is defined. All standard
		 * PNG images must be compressed with this scheme.
		 * The compression method field is provided for possible
		 * future expansion or proprietary variants.
		 *
		 * @note Decoders must check this byte and report an error
		 * if it holds an unrecognized code.
		 */
		UInt8 compressionMethod = 0;
		UInt8 filterMethod = 0;
		UInt8 interlaceMethod = 0;

		const Chunk IHDR;

		// Methods Variant

		bool isBitDepthValueValid();

		bool isColorTypeValueValid();

		bool isEachPixelGrayscaleSample();

		bool isEachPixelRGBTriple();

		bool isEachPixelPaletteIndex();

		bool isEachPixelGrayscaleSampleFollowedAlphaSample();

		bool isEachPixelRGBTripleFollowedAlphaSample();

	public:

		PNGInfo(const Chunk& _chunk);

		bool areVariantsSatisfied();

		UInt32 readUInt32From4Bytes(ConstIterator _it);

		UInt8 readUInt8FromByte(ConstIterator _it);

	};

}

#endif //MONG_PNGINFO_HPP
