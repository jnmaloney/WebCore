#pragma once


#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <png.h>
#include <zlib.h>


class PngLoader
{
public:

  PngLoader();
  ~PngLoader();


  int load(const char* filename);
  int load_mem(const char* data, uint64_t numBytes);

  png_image image; /* The control structure used by libpng */

  /* Image data */
  png_bytep buffer = 0;
  size_t size = 0;

};
