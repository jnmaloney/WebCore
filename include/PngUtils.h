#pragma once


#include <PngLoader.h>
#include <vector>


class TileSet;


class PngUtils
{
public:
  PngUtils();
  ~PngUtils();

  //Rect collisionRect(png_bytep buffer);
  void prepareCollisionShapes(PngLoader* loader, TileSet* tileset);
};
