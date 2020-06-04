// Joan Andrés (@Andres6936) Github.

#ifndef MONG_CRC_HPP
#define MONG_CRC_HPP

#include <array>
#include <vector>

#include "Definitions.hpp"

namespace Mong
{

	class CRC
	{

	private:

		std::array<UInt64, 256> table;

	public:

		// Construct

		CRC();

		// Methods

		UInt64 getCyclicRedundancyCheck(const std::vector<std::byte>& _buffer);

		void showTable();

	};

}

#endif //MONG_CRC_HPP
