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
  int load_mem(const char* data, unsigned int numBytes);

  png_image image; /* The control structure used by libpng */

  /* Image data */
  png_bytep buffer = 0;//unsigned char*
  size_t size = 0;

  int x = 0;
  int y = 0;
};
