// Joan Andrés (@Andres6936) Github.

#include <Mong/Chunk.hpp>
#include <iostream>

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

void Chunk::determineProperties()
{
	// Ancillary bit: bit 5 of first byte
	// 0 (uppercase) = critical, 1 (lowercase) = ancillary.
	if (std::isupper(type[0])) ancillary = false;

	// Private bit: bit 5 of second byte
	// 0 (uppercase) = public, 1 (lowercase) = private.
	if (std::isupper(type[1])) privateChunk = false;

	// Reserved bit: bit 5 of third byte
	// Must be 0 (uppercase) in files conforming to this version of PNG.
	if (std::isupper(type[2])) reserved = false;

	// Safe-to-copy bit: bit 5 of fourth byte
	// 0 (uppercase) = unsafe to copy, 1 (lowercase) = safe to copy
	if (std::isupper(type[3])) safeCopy = false;
}

void Chunk::printProperties()
{
	std::cout << "Ancillary: " << ancillary << "\n";
	std::cout << "Private: " << privateChunk << "\n";
	std::cout << "Reserved: " << reserved << "\n";
	std::cout << "Safe to Copy: " << safeCopy << "\n";
}

ConstIterator Chunk::getIterator() const
{
	return data.cbegin();
}

bool Chunk::verifyCyclicRedundancyCheck(const CRC& _crc) const
{
	// The four parts of a chunk are:

	// 1. (4 Bytes) length field.
	// 2. (4 Bytes) chunk name.
	// 3. (Length) data.
	// 4. (4 Bytes) checksum Cyclic Redundancy Check.

	// The checksum is created from the chunk name
	// field and the data, therefore not including
	// the length field and the checksum.

	// As we divided the chunk, is necessary create a new
	// struct that store the data and chunk name (aka. type)

	std::vector<std::byte> stream;

	// Store first the name chunk (aka. type)
	// Precondition: the type have a length of 4 characters (bytes)
	// Post-condition: the buffer have a length of 4 bytes
	for(const auto letter : type)
	{
		stream.push_back(std::byte(letter));
	}

	// In this case, already have the 4 bytes of type, now is
	// necessary store the data
	// Begin say a stream that the news information are stored
	// at end of this (the stream) and that begin fill from the
	// start of data to end data.

	// In resume: copy the information of data to end of stream
	stream.insert(stream.end(), data.begin(), data.end());

	const UInt32 hash = _crc.getCyclicRedundancyCheck(stream);

	if (cyclicRedundancyCheck == hash)
	{
		return true;
	}
	else
	{
		return false;
	}
}
