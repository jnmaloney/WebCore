#pragma once
#ifdef 0


#include "graphics.h"
#include <string>
#include <vector>
#include "PhysicsLevel2D.h"


class Texture;
class TileSet;
class TileMap;


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

    PhysicsLevel2D mPhysicsLevel;

    TileMap* getMap() { return mMap; }
    TileSet* getSet() { return mSet; }

  protected:

    void generateCollisionShapes(int x, int y);
    void generateObjects(); // unused

    void loadTMX(const std::string& filename);
    void loadTMX_Base64(const std::string& filename);

    TileSet* mSet = 0; // Texture / Collision Shape Set
    TileMap* mMap = 0; // The map

};

#endif
