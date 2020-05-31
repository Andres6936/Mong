// Joan Andrés (@Andres6936) Github.

#ifndef MONG_CHUNK_HPP
#define MONG_CHUNK_HPP

#include "Definitions.hpp"

#include <vector>
#include <string>

namespace Mong
{

	class Chunk
	{

	private:

		// Its a attribute derived.
		// Equals to data.size();
		UInt32 length = 0;

		UInt32 cyclicRedundancyCheck = 0;

		std::string type;

		std::vector<std::byte> data;

	public:

		// Setters

		void setLength(UInt32 _length);

		void setData(const std::vector<std::byte>& _data);

		void setType(const std::string& _type);

		void setCyclicRedundancyCheck(UInt32 _cyclicRedundancyCheck);

	};

}

#endif //MONG_CHUNK_HPP
