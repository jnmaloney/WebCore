#pragma once


#include <map>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <graphics.h>
#include "Square.h"


class RenderSystem;
class MeshBank;
class Palette;


// Kind of a replacement for render queue 2D
class SceneTileBatch
{
public:

  SceneTileBatch();
  ~SceneTileBatch();

  // Set tile size
  void init(int x, int y);

  // Remove everything from the batch
  void clear();

  // Execute the queued elements, in efficient order
  void draw(RenderSystem* rs);

  void addElement(
    int tile,
    glm::mat4 xform
  );

protected:

  // Info containing one instance of transform
  struct TransformInfo
  {
    glm::mat4 xform;
  };

  // A list of transform infos
  typedef std::list<TransformInfo> TransformList;

  // Map mesh index to all transforms used in this batch
  typedef std::map<int, TransformList> TileList;

  //
  TileList m_tiles;

  int m_x = 0;
  int m_y = 0;
  std::vector<Square> m_squares;

};
