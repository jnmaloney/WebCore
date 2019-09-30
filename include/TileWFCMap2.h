#ifdef TILE_WFC
#pragma once


#include <string>
#include <vector>
#include "wave0.h"


class TileWFCMap2
{
public:
    TileWFCMap2();
    ~TileWFCMap2();

    void setInput(std::string inputFile);

    void clear();

    void stamp(int x, int y, int tile_type);

    int getMapWidth() { return mapwidth; }
    int getMapHeight() { return mapheight; }

    bool calcPatch(int x, int y);

    //
    // Map Data
    //

    std::vector<int> m_data;
    Output m_output;
    Image m_image;

    // Shouldn't this be in the tileset..?
    const int tileheight = 16;
    const int tilewidth = 16;

    const int mapwidth = 125;
    const int mapheight = 125;

    //
    // Generator
    //
    class Settings
    {
    public:
      int    n              = 3;
      size_t map_width      = 8;
      size_t map_height     = 8;
      size_t symmetry       = 8;
      bool   periodic_out   = true;
      bool   periodic_in    = true;
      //bool   has_foundation = false;
    };

    Settings m_settings;
    Model* m_model;

    int m_seed = 0;
};

#endif
