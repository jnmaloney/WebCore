#pragma once
#define USE_BULLET 1


#include "graphics.h"
#include <string>
#include <vector>
#ifdef USE_BULLET
#include "PhysicsLevel2D.h"
#endif


class Texture;
class TileSet;
class TileMap;
class RenderQueue;


class TileLevel
{
public:
    TileLevel();
    ~TileLevel();

    void clear();

    void init(
      const std::string& mapFile,
      const std::string& pngFile,
      float gravity);

    #ifdef USE_BULLET
    PhysicsLevel2D mPhysicsLevel;
    #endif

    TileMap* getMap() { return mMap; }
    TileSet* getSet() { return mSet; }

    void createRenderQueue(RenderQueue* a_queue);

  protected:

    void generateCollisionShapes(int x, int y);
    void generateObjects(); // unused

    void loadTMX(const std::string& filename);
    void loadTMX_Base64(const std::string& filename);

    TileSet* mSet = 0; // Texture / Collision Shape Set
    TileMap* mMap = 0; // The map

};
