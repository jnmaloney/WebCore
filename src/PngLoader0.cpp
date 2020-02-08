// #include "PngLoader.h"
// #include <iostream>
// #include "stb_image.h"
//
//
// PngLoader::PngLoader()
// {
//
// }
//
//
// PngLoader::~PngLoader()
// {
//   if (buffer) stbi_image_free((void*)buffer);
// }
//
//
// int PngLoader::load_mem(const char* data, unsigned int numBytes)
// {
//   if (buffer) stbi_image_free((void*)buffer);
//
//   int n;
//
//   //buffer = stbi_load_from_memory(reinterpret_cast<const unsigned char*>(data), numBytes, &x, &y, &n, 0);
//   unsigned char* new_data = new unsigned char[numBytes];
//   for (int i = 0; i < numBytes; ++i)
//     new_data[i] = data[i]; //+ 128;
//   buffer = stbi_load_from_memory(new_data, numBytes, &x, &y, &n, 0);
//   delete[] new_data;
//
//   return 0;
// }
//
//
// int PngLoader::load(const char* filename)
// {
//   // Basic usage (see HDR discussion below for HDR usage):
//   //    int x,y,n;
//   //    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
//   //    // ... process data if not NULL ...
//   //    // ... x = width, y = height, n = # 8-bit components per pixel ...
//   //    // ... replace '0' with '1'..'4' to force that many components per pixel
//   //    // ... but 'n' will always be the number that it would have been if you said 0
//   //    stbi_image_free(data)
//
//   return 0;
// }
