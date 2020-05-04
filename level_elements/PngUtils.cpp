#include "PngUtils.h"
#include <iostream>
#include "TileSet.h"


PngUtils::PngUtils()
{

}


PngUtils::~PngUtils()
{

}


void PngUtils::prepareCollisionShapes(PngLoader* loader, TileSet* tileset)
{
  //
  // Tile iterator
  //
  int x = tileset->mTileX;
  int y = tileset->mTileY;
  for (int j = 0; j < loader->image.height; j += y)
  {
    for (int i = 0; i < loader->image.width; i += x)
    {
      //
      // Pixel iterator
      //
      TileSet::Rect r;
      r.x_min = x;
      r.x_max = 0;
      r.y_min = y;
      r.y_max = 0;
      for (int pj = 0; pj < y; ++pj)
      {
        for (int pi = 0; pi < x; ++pi)
        {
          png_bytep ptrToRow = loader->buffer;
          int t = 4 * (i + pi) +  (j + pj) * PNG_IMAGE_ROW_STRIDE(loader->image);
          unsigned char alpha = ((unsigned char *)loader->buffer)[t + 3];
          if (alpha != 0)
          {
            if (pi < r.x_min) r.x_min = pi;
            if (pi > r.x_max) r.x_max = pi;
            if (pj < r.y_min) r.y_min = pj;
            if (pj > r.y_max) r.y_max = pj;
          }
        }
      }

      if (r.x_max == 0 && r.y_max == 0)
      {
        r.x_min = 0;
        r.x_min = 0;
      }

      //std::cout << r.x_min << ", " << r.y_min << " | " << r.x_max << ", " << r.y_max << std::endl;
      tileset->mCollisionShapes.push_back(r);
    }
  }
}
