// Joan Andrés (@Andres6936) Github.

#ifndef MONG_CHUNK_HPP
#define MONG_CHUNK_HPP

#include "Definitions.hpp"

#include <vector>

namespace Mong
{

	class Chunk
	{

	private:

		UInt32 length = 0;

		UInt32 type = 0;

		std::vector<std::byte> data;

		UInt32 cyclicRedundancyCheck = 0;

	public:

	};

}

#endif //MONG_CHUNK_HPP
