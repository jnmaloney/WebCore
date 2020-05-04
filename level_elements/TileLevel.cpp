#include "TileLevel.h"
#include "TileSet.h"
#include "TileMap.h"
#include <iostream>
#include "RenderQueue.h"


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
  #ifdef USE_BULLET
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
        //TileSet::Rect r = mSet->getCollisionShape(id);
        //TileSet::Rect r = {0.f, 0.f, 16.f, 16.f};
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
  #endif
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

#ifdef USE_BULLET

  // Initialise the Physics Level
  mPhysicsLevel.init(gravity);

  // Create Tile Shapes
  generateCollisionShapes(mMap->tilewidth, mMap->tileheight);

#endif

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


void TileLevel::createRenderQueue(RenderQueue* a_queue)
{
  if (a_queue == 0) return;
  RenderQueue& queue = *a_queue;

  TileMap* tilemap = mMap;
  queue.clear();
  int z = 0;
  for (int i = 0; i < tilemap->width; ++i)
  {
    for (int j = 0; j < tilemap->height; ++j)
    {
      glm::mat4 mvp(1.0);

      mvp = glm::translate(mvp,
        glm::vec3(
          i * tilemap->tilewidth,
          j * tilemap->tileheight,
          z));

      mvp = glm::scale(mvp,
        glm::vec3(
          tilemap->tilewidth,
          tilemap->tileheight,
          1));

      int t = i + tilemap->width * j;
      int u = tilemap->layers[0].data[t];
      //std::cout << u << std::endl;
      if (u != 0)
      {
        // stamp
        queue.setTile(u);
        queue.setMVP(mvp);
        queue.submit();
      }
    }
  }
}
