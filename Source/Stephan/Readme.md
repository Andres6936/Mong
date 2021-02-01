# Uncompressing DEFLATE Data

###### posted November 27, 2011 by Stephan Brumme

## The Most Common Compression Algorithm

Everyone knows the widespread ZIP file format. Some Windows users may have never
heard of GZIP, but all Unix users did. 99% percent of all ZIPs are encoded with
the so-called DEFLATE algorithm, specified
as [RFC 1951](http://www.ietf.org/rfc/rfc1951.txt). The same holds true for PNG
images, some PDFs, compressed HTTP data transfer and many more.

I wanted to have a C++ implementation without strange dependencies and weird
pointer arithmentic. I wanted something like this:

```cpp
#include
"Inflate.h"
std::vector<unsigned char> uncompressed = Inflate("filename.gz");
```

So I wrote my own DEFLATE decoder in pure C++/STL. It's reasonably fast -
somewhere between 50 and 100 MByte/s (uncompressed data) - and compiles easily
with Visual C++ and GCC (older version should be fine, too).

If you encounter any bugs/problems or have ideas for improving future versions,
please write me an email: create@stephan-brumme.com

### Code Structure

The main class Inflate, which derives from std::vector<unsigned char> contains
the DEFLATE decompression algorithm, accesses three helper classes:
BinaryInputBuffer, HuffmanTree and Hash:

- BinaryInputBuffer steps bitwise through a file or a memory buffer
- HuffmanTree provides a fast Huffman tree data structure, optimized for DEFLATE
- Hash computes the CRC32 [hash](https://create.stephan-brumme.com/crc32/)
  (see here for more information)

These three helper classes are completely independent of each other. They have
simple #includes such as string, vector and fstream.

However, you don't need to worry about them. They are automatically included by
Inflate.

Copyright
to [Stephan Brumme](https://create.stephan-brumme.com/deflate-decoder/)