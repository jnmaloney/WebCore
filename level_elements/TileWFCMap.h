#ifdef TILE_WFC
#pragma once


#include <string>
#include <vector>
#include "wave0.h"


class TileWFCMap
{
public:
    TileWFCMap();
    ~TileWFCMap();

    void setInput(std::string inputFile);

    void clear();

    void stamp(int x, int y, int tile_type);

    void generate();

    int getMapWidth() { return mapwidth; }
    int getMapHeight() { return mapheight; }

    bool calcPatch(int x, int y, bool do_stamp, bool fast);

    //
    // Map Data
    //

    std::vector<int> data;
    Output m_outputNoStamp;
    Output m_outputStamp;
    Output* m_output = 0;
    Image m_image;

    // ?
    const int tileheight = 32;
    const int tilewidth = 32;

    int mapwidth = 125;
    int mapheight = 125;

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
    Model* m_modelFast;
};

#endif
