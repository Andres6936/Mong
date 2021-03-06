// Joan Andrés (@Andres6936) Github.

#include "Mong/Data.hpp"
#include "Cup/Properties/Readable.h"

using namespace Mong;

Data::Data(const Chunk& _chunk, const Information& _info) : IDAT(_chunk), IHDR(_info)
{
	std::vector<std::byte> uncompressed = Cup::Properties::Readable::readBinary("IDAT.uncompress");
}