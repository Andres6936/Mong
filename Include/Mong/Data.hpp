// Joan Andrés (@Andres6936) Github.

#ifndef MONG_DATA_HPP
#define MONG_DATA_HPP

#include "Chunk.hpp"
#include "Information.hpp"

namespace Mong
{

	class Data
	{

	private:

		// Const Fields

		const Chunk IDAT;

		const Information IHDR;

	public:

		// Construct

		Data(const Chunk& _chunk, const Information& _info);

	};

}

#endif //MONG_DATA_HPP
