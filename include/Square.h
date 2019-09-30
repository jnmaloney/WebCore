#pragma once

#include "graphics.h"
#include <string>
#include <vector>
#include <map>


class RenderSystem;


class Square
{

public:

  Square();
  ~Square();

  void initVerts(int tile_x, int tile_y);
  void bind(RenderSystem* rs);
  void draw();

  //
  // Rendering
  //
  GLuint m_vbo_vertices = -1;
  GLuint m_vbo_uvs = -1;
  GLuint m_ibo_elements = -1;

  float x_res = 16;
  float y_res = 32;

  // This gets sent to the render queue
  // struct IboElement
  // {
  //   std::string name;
  //   int size = 0;
  //   int index = 0;
  //   GLuint elements;
  // };
  // std::map< int, IboElement > m_matIboElements;

protected:

};
