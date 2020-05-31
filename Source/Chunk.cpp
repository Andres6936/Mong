// Joan Andrés (@Andres6936) Github.

#include <Mong/Chunk.hpp>

using namespace Mong;

void Chunk::setLength(UInt32 _length)
{
	length = _length;
}

void Chunk::setType(const std::string& _type)
{
	type = _type;
}

void Chunk::setData(const std::vector<std::byte>& _data)
{
	data = _data;
}

void Mong::Chunk::setCyclicRedundancyCheck(UInt32 _cyclicRedundancyCheck)
{
	cyclicRedundancyCheck = _cyclicRedundancyCheck;
}

