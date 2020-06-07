// Joan Andrés (@Andres6936) Github.

#ifndef MONG_PALETTE_HPP
#define MONG_PALETTE_HPP

#include "Chunk.hpp"

#include <Cup/Object/Color.hpp>
#include <vector>

namespace Mong
{

	using namespace Cup::Object;

	class Palette
	{

	private:

		// Fields

		std::vector<Color> entries;

		// Const Fields

		const Chunk PLTE;

		// Methods Invariant

		bool verifyDivisibleBy3();

	public:

		// Construct

		Palette(const Chunk& _chunk);

		// Methods

		void showEntries();

	};

}

#endif //MONG_PALETTE_HPP
