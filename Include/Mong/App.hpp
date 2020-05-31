// Design by Joan Andrés.

#ifndef MONG_APP_HPP
#define MONG_APP_HPP

#include <Cup/Properties/Readable.h>

#include "Chunk.hpp"

namespace Mong
{

	using namespace Cup;

	class App : private Properties::Readable
	{

	private:

		std::string_view filename;

		std::vector<std::byte> dataRaw;

		std::vector<Chunk> chunks;

		/**
		 * The first eight bytes of a PNG file
		 * always contain the following (decimal)
		 * values: 137 80 78 71 13 10 26 10
		 *
		 * @return True if the signature is
		 *  correct, false otherwise.
		 */
		bool verifySignaturePNG();

		void readChunksFromDataRaw();

	public:

		App(std::string_view _filename);

		void run();

	};

}

#endif //MONG_APP_HPP
