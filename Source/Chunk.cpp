// Joan Andrés (@Andres6936) Github.

#include <Mong/Chunk.hpp>

using namespace Mong;

Chunk::Chunk(std::vector<std::byte>&& _data) : data(std::move(_data))
{
	length = data.size();
}

void Chunk::setType(const std::string& _type)
{
	type = _type;
}

void Mong::Chunk::setCyclicRedundancyCheck(UInt32 _cyclicRedundancyCheck)
{
	cyclicRedundancyCheck = _cyclicRedundancyCheck;
}

