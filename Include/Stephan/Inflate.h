// //////////////////////////////////////////////////////////
// Inflate.h
// Copyright (c) 2011 Stephan Brumme. All rights reserved.
//

#pragma once

#pragma warning(disable: 4530) // exception handling disabled
#include <vector>
#include <string>

#include "HuffmanTree.h" // HuffmanTree::Code
class BinaryInputBuffer;


/// decompress data previously crunshed with Deflate algorithm (GZ, PNG, ...)
class Inflate : public std::vector<unsigned char>
{
public:
  /// decode a file
  explicit Inflate(const std::string& filename, bool isRawStream = false, bool checkCrc = true);
  /// decode a in-memory buffer
           Inflate(void* data, size_t numBytes, bool isRawStream = false, bool checkCrc = true);

  /// errors
  enum Error
  {
    Successful,
    NotStarted,
    Working,
    InvalidPointer,
    InvalidFile,
    InvalidHeaderID,
    InvalidCompressionAlgorithm,
    InvalidBlockMethod,
    InvalidData,
    InvalidCrc,
    FilesizeMismatch
  };
  /// get error code
  Error getError() const { return _error; }
  /// error code translated to English (empty if Successful)
  const char* getErrorText() const;
  /// true, if everything is okay
  bool  isValid()  const { return _error == Successful; }

  /// original filename (empty if not present in GZip header)
  std::string  getFilename()  const { return _filename; }
  /// original filename (empty if not present in GZip header)
  std::string  getComment()   const { return _comment; }
  /// get timestamp (might be missing => 0)
  time_t       getTimestamp() const { return _timestamp; }
  /// compression level (might be non-sense, depending on encoder)
  unsigned int getCompressionLevel() const { return _compressionLevel; }
  /// compressed size
  size_t       sizeCompressed()      const { return _sizeCompressed; }

private:
  /// main decoder, does everything at once (invoked by constructor), true if successful
  bool load        (BinaryInputBuffer& buffer, bool isRawStream, bool checkCrc);

  /// parse header, true if okay
  bool parseHeader (BinaryInputBuffer& buffer);
  /// decode block (any method), true if okay
  bool decodeBlock (BinaryInputBuffer& buffer, bool& isFinal);
  /// decode block (method 0), true if okay
  bool copyBlock   (BinaryInputBuffer& buffer);
  /// decode block (method 1&2), true if okay
  bool inflateBlock(BinaryInputBuffer& buffer, const HuffmanTree& tree, const HuffmanTree& distanceTree);

  /// extract token from buffer, based on current Huffman tree
  HuffmanTree::Code nextToken(BinaryInputBuffer& buffer, const HuffmanTree& tree);

  /// error code
  Error _error;

  /// filename (as stored in header)
  std::string  _filename;
  /// comment
  std::string  _comment;
  /// timestamp
  time_t       _timestamp;
  /// compression level
  unsigned int _compressionLevel;

  /// compressed size
  size_t _sizeCompressed;
  /// bytes parsed yet (for debugging)
  size_t _sizeParsed;

  /// default bitlength Huffman tree
  static HuffmanTree _defaultTree;
  /// default empty Huffman tree
  static HuffmanTree _emptyTree;
};
