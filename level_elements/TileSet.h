#pragma once


#include "Texture.h"
#include <vector>


class TileSet
{
public:
  TileSet();
  ~TileSet();

  void init(const char* textureFileName, int tileWidth, int tileHeight);

  //Rect getShape(1);

  Texture mTexture;
  int mTileX;
  int mTileY;

  struct Rect { float x_min; float y_min; float x_max; float y_max; };

  std::vector<Rect> mCollisionShapes;
  Rect getCollisionShape(int i);

protected:


};
