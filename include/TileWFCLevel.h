#ifdef TILE_WFC
#pragma once


#include "graphics.h"
#include <string>
#include <vector>
#include "PhysicsLevel2D.h"


class Texture;
class TileSet;
class TileWFCMap2;


class TileWFCLevel
{
public:
    TileWFCLevel();
    ~TileWFCLevel();

    void clear();

    void init(
      const std::string& mapFile, // Map input
      const std::string& pngFile);// TileSet

    PhysicsLevel2D mPhysicsLevel;

    TileWFCMap2* getMap() { return mMap; }
    TileSet* getSet() { return mSet; }

    void generate();
    void generate_start();
    int generate_continue();
    void generate_end();


    int getMapWidth();
    int getMapHeight();

  protected:

    void generateCollisionShapes(int x, int y);
    void generateTiles();

    TileSet* mSet = 0; // Texture / Collision Shape Set
    TileWFCMap2* mMap = 0; // The map

    int m_index_i = 0;
    int m_index_j = 0;
};

#endif
