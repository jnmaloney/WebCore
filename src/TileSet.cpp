#include "TileSet.h"


TileSet::TileSet()
{

}


TileSet::~TileSet()
{

}


void TileSet::init(const char* textureFileName, int tileWidth, int tileHeight)
{
  mTileX = tileWidth;
  mTileY = tileHeight;
  mTexture.loadPng_withCollisionShapes(textureFileName, this);
}


TileSet::Rect TileSet::getCollisionShape(int i)
{
  //if (i < mCollisionShapes.size())
  return mCollisionShapes[i];
}
