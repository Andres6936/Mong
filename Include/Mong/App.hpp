// Design by Joan Andrés.

#ifndef MONG_APP_HPP
#define MONG_APP_HPP

#include <Cup/Properties/Readable.h>

#include "Chunk.hpp"
#include "Information.hpp"

#include <vector>
#include <optional>
#include <string_view>

namespace Mong
{

	using namespace Cup;

	class App : private Properties::Readable
	{

	private:

		// Definitions

		using ConstIteratorChunk = std::vector<Chunk>::const_iterator;

		// Fields

		std::string_view filename;

		/**
		 * Post-condition: The index 0 is the IHDR Chunk
		 * and the last element is the IEND Chunk.
		 */
		std::vector<Chunk> chunks;

		std::vector<std::byte> dataRaw;

		/**
		 * The first eight bytes of a PNG file
		 * always contain the following (decimal)
		 * values: 137 80 78 71 13 10 26 10
		 *
		 * @return True if the signature is
		 *  correct, false otherwise.
		 */
		bool verifySignaturePNG();

		bool verifyChunkOrdering();

		bool verifyCRCForAllChunks();

		void readChunksFromDataRaw();

		void readImagePalette();

		void readImageData(const Information& _info);

		Information readImageHeader();

		/**
		 * Read 4 bytes of 8 bits from a iterator,
		 * and save in a variable of 32 Bits.
		 *
		 * Design for read the length and cyclic
		 * redundancy check of chunk.
		 *
		 * @param _it Iterator to a container with bytes .
		 * @return The result of package 4 bytes into variable.
		 */
		UInt32 readUInt32From4Bytes(ConstIterator _it);

		UInt32 getLengthChunk(ConstIterator _it);

		UInt32 getCyclicRedundancyCheck(ConstIterator _it);

		std::string getTypeChunk(ConstIterator _it);

		std::optional<ConstIteratorChunk> findChunkType(std::string_view _type);

	public:

		App(std::string_view _filename);

		void run();

	};

}

#endif //MONG_APP_HPP
