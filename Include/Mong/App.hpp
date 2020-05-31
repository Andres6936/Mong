// Design by Joan Andrés.

#ifndef MONG_APP_HPP
#define MONG_APP_HPP

#include <Cup/Properties/Readable.h>

namespace Mong
{

	using namespace Cup;

	class App : private Properties::Readable
	{

	private:

		std::string_view filename;

		std::vector<std::byte> dataRaw;

	public:

		App(std::string_view _filename);

		void run();

	};

}

#endif //MONG_APP_HPP
