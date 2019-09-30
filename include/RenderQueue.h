#pragma once

#include "graphics.h"
#include <list>
#include <map>
#include <vector>
#include "Square.h"


class RenderSystem;


class  RenderQueue
{
public:

  RenderQueue();
  ~RenderQueue();

  // Execute the queued elements, in efficient order
  void draw(RenderSystem* rs);

  // Getting ready to submit
  void setMVP(glm::mat4 mvp);
  void setTile(int t);

  // Reset
  void clear();

  // Caputre the state of current drawing elements
  void submit();

  // Tiles
  float x_res = 16;
  float y_res = 32;
  int mod_vert = 10;
  int div_vert = 10;

protected:

  //typedef std::list<glm::mat4> TransformLevel;
  struct Transform
  {
    glm::mat4 x;
    // glm::vec3 diffuse;
    // bool setDiffuse = false;
    // std::vector<int> pallette_id;
    // bool setPallette = false;
  };
  Transform m_currentTransform;
  typedef std::list<Transform> TransformLevel;
  typedef std::map<int, TransformLevel> TileLevel;

  TileLevel m_queue;

  TransformLevel* m_currentTransformLevel = 0;

  //Square m_square;
  std::map<int, Square> m_tiles;
};
