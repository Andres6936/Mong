// //////////////////////////////////////////////////////////
// uncompress.cpp
// Copyright (c) 2011 Stephan Brumme. All rights reserved.
//

#include "Stephan/Inflate.h"
#include <iostream>
#include <fstream>
#include <ctime>
#pragma warning (disable: 4996) // ctime unsafe


int main(int argc, char* argv[])
{
  // file name via command-line
  if (argc != 2)
  {
    std::cout << "Syntax: uncompress file.gz" << std::endl;
    return 1;
  }
  const char* filename = argv[1];

  // decompress
  std::cout << "Decompressing " << filename << " ..." << std::endl;
  clock_t startTime =  clock();
  Inflate decoded(filename);
  double duration   = (clock() - startTime) / double(CLOCKS_PER_SEC);

  // no problem during decompression and checksum correct ?
  if (!decoded.isValid())
  {
    std::cout << "!!! FAILED, error " << decoded.getError()
                              << " (" << decoded.getErrorText() << ") !!!" << std::endl;
    return 2;
  }

  // write uncompressed data to disk
  std::string outputFilename = decoded.getFilename();
  if (outputFilename.empty())
    outputFilename = "decompressed.data";
  std::ofstream output(outputFilename.c_str(), std::ios::binary);
  output.write((const char*)&decoded[0], decoded.size());
  output.close();

  // display some statistics
  time_t timestamp = decoded.getTimestamp();
  std::cout << "file: " << decoded.getFilename() << ", timestamp: " << ctime(&timestamp) << std::endl
            << duration << "s => "
            << decoded.sizeCompressed()/(duration*1024*1024) << "MByte/s (gz), "
            << decoded.size()          /(duration*1024*1024) << "MByte/s (raw)" << std::endl;

  return 0;
}
