// Joan Andrés (@Andres6936) Github.

#ifndef MONG_CRC_HPP
#define MONG_CRC_HPP

#include <array>
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

		void showTable();

	};

}

#endif //MONG_CRC_HPP
