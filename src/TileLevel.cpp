#ifdef USE_BULLET
#include "TileLevel.h"
#include "TileSet.h"
#include "TileMap.h"
#include <iostream>


TileLevel::TileLevel()
{

}


TileLevel::~TileLevel()
{

}


void TileLevel::clear()
{
  mMap->clear();
}


void TileLevel::generateCollisionShapes(int x, int y)
{
  // First calculate the texture shapes

  for (auto layer : mMap->layers)
  {
    // Tile id
    int id = 0;

    for (int j = 0; j < mMap->height; ++j)
    {
      for (int i = 0; i < mMap->width; ++i)
      {
        int t = i + j * mMap->width;
        id = layer.data[t] - 1;

        if (id == -1) continue;

        int x_off = i * mMap->tilewidth;
        //int y_off = (mMap->height - j) * mMap->tileheight;
        int y_off = j * mMap->tileheight;

        // Collision shape for the tile
        TileSet::Rect r = mSet->getCollisionShape(id);

        // Offset Rect to tile position
        r.x_min += x_off;
        r.x_max += x_off;
        r.y_min += y_off;
        r.y_max += y_off;

        // Add  it to the Collision scene
        mPhysicsLevel.addTile(r.x_min, r.x_max, r.y_min, r.y_max, t);
      }
    }
    //mPhysicsLevel.addTile(0, 0, 0, 0); // ?
    break;
  }
}


void TileLevel::loadTMX(const std::string& filename)
{
  mMap->clear();
  mMap->loadTMX(filename);
}


void TileLevel::loadTMX_Base64(const std::string& filename)
{
  mMap->clear();
  mMap->loadTMX_Base64(filename);
}


void TileLevel::init(const std::string& mapFile, const std::string& pngFile, float gravity)
{
  mMap = new TileMap();
  mSet = new TileSet();

  loadTMX_Base64(mapFile);

  // Initialise the Tile Set
  mSet->init(pngFile.c_str(), mMap->tilewidth, mMap->tileheight);

  // Initialise the Physics Level
  mPhysicsLevel.init(gravity);

  // Create Tile Shapes
  generateCollisionShapes(mMap->tilewidth, mMap->tileheight);

  // Create Object Entities
  generateObjects();
}


void TileLevel::generateObjects()
{
  // for (const auto& i : mMap->objects)
  // {
  //   std::string& t = i.type;
  //   // Object from type?
  //   // new Enemy(&mPhysicsLevel);
  // }
}


#endif
