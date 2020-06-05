// Joan Andrés (@Andres6936) Github.

#ifndef MONG_CHUNK_HPP
#define MONG_CHUNK_HPP

#include "Definitions.hpp"
#include "CRC.hpp"

#include <vector>
#include <string>
#include <string_view>

namespace Mong
{

	class Chunk
	{

	private:

		/**
		 * Chunks that are not strictly necessary in order
		 * to meaningfully display the contents of the file
		 * are known as “ancillary” chunks. A decoder
		 * encountering an unknown chunk in which the ancillary
		 * bit is 1 can safely ignore the chunk and proceed to
		 * display the image. The time chunk (tIME) is an
		 * example of an ancillary chunk.
		 *
		 * Chunks that are necessary for successful display of
		 * the file’s contents are called “critical” chunks.
		 * A decoder encountering an unknown chunk in which the
		 * ancillary bit is 0 must indicate to the user that the
		 * image contains information it cannot safely interpret.
		 * The image header chunk (IHDR) is an example of a
		 * critical chunk.
		 *
		 * For defect all the chunk are ancillary (not critical).
		 */
		bool ancillary = true;

		/**
		 * For defect all chunk are private.
		 */
		bool privateChunk = true;

		/**
		 * For defect all chunk are reserved.
		 */
		bool reserved = true;

		/**
		 * For defect all chunk are safe to copy.
		 */
		bool safeCopy = true;

		/**
		 * Its a attribute derived.
		 * Equals to data.size();
		 */
		UInt32 length = 0;

		UInt32 cyclicRedundancyCheck = 0;

		std::string type;

		std::vector<std::byte> data;

	public:

		// Methods

		/**
		 * Each chunk in a PNG image is verified for corrupted
		 * data using a CRC32 checksum, where CRC stands for
		 * Cyclic Redundancy Checksum.
		 *
		 * @param _crc Struct with the table cyclic redundancy
		 *  check constructed (Better Performance).
		 *
		 * @return True if the CRC is correct, false otherwise.
		 */
		bool verifyCyclicRedundancyCheck(const CRC& _crc) const;

		void determineProperties();

		/**
		 * Determine if the type of chunk is equals to type
		 * passed for parameter.
		 *
		 * @param _type The type to verify.
		 * @return True if the types of chunks are equals.
		 */
		bool equalsTypeTo(std::string_view _type) const;

		// Getter

		ConstIterator getIterator() const;

		// Setters

		void setLength(UInt32 _length);

		void setData(const std::vector<std::byte>& _data);

		void setType(const std::string& _type);

		void setCyclicRedundancyCheck(UInt32 _cyclicRedundancyCheck);

		void printProperties();

	};

}

#endif //MONG_CHUNK_HPP
