#ifdef TILE_WFC
#include "TileWFCLevel.h"
#include "TileSet.h"
#include "TileWFCMap2.h"
#include <iostream>


TileWFCLevel::TileWFCLevel()
{
  mMap = new TileWFCMap2();
  mSet = new TileSet();
}


TileWFCLevel::~TileWFCLevel()
{

}


void TileWFCLevel::clear()
{
  mMap->clear();
}


int TileWFCLevel::getMapWidth()
{
  return mMap->getMapWidth();
}


int TileWFCLevel::getMapHeight()
{
  return mMap->getMapHeight();
}


void TileWFCLevel::generateCollisionShapes(int x, int y)
{
  // Tile id
  int id = 0;

  for (int j = 0; j < getMapHeight(); ++j)
  {
    for (int i = 0; i < getMapWidth(); ++i)
    {
      int t = i + j * getMapWidth();
      id = mMap->m_data[t] - 1;

      if (id == -1) continue;

      int x_off = i * mMap->tilewidth;
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
  //mPhysicsLevel.finishAddingTIles();
}


void TileWFCLevel::init(const std::string& mapFile, const std::string& pngFile)
{
  mMap->setInput(mapFile);
  mSet->init(pngFile.c_str(), mMap->tilewidth, mMap->tileheight);
}


void TileWFCLevel::generate()
{
  // dep'c
  mMap->clear();
  mPhysicsLevel.init();
  generateCollisionShapes(mMap->tilewidth, mMap->tileheight);
}


void TileWFCLevel::generate_start()
{
  mMap->clear();
  m_index_i = 0;
  m_index_j = 0;
}


int TileWFCLevel::generate_continue()
{
  // if (m_index_i >= 125) return -1;
  // if (m_index_j >= 125) return -1;
  if (m_index_i >= 101) return -1;
  if (m_index_j >= 101) return -1;

  // bool fast = true;
  // if (m_index_j == 50 && (m_index_i == 25 || m_index_i == 50 || m_index_i == 75)) fast = false;

  // if (m_index_i == 50 && m_index_j == 50)
  // {
  //   mMap->calcPatch(m_index_i, m_index_j, true, fast);
  // }
  // else
  // {
  //   mMap->calcPatch(m_index_i, m_index_j, false, fast);
  // }
  bool result = mMap->calcPatch(m_index_i, m_index_j);

  if (result)
  {
    //m_index_j += 25;
    m_index_j += 23;
    //if (m_index_j >= 125)
    if (m_index_j >= 101)
    {
      m_index_j = 0;
      //m_index_i += 25;
      m_index_i += 23;
    }
  }

  return m_index_i * 125 + m_index_j * 25;
}


void TileWFCLevel::generate_end()
{
  mPhysicsLevel.init();
  generateCollisionShapes(mMap->tilewidth, mMap->tileheight);
}


#endif
