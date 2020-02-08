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

  void initVerts(int tile_x, int tile_y, int w, int h);
  void bind(RenderSystem* rs);
  void draw();

  bool isInit() { return m_vbo_vertices != 0; }

protected:
  //
  // Rendering
  //
  GLuint m_vbo_normals = 0;
  GLuint m_vbo_vertices = 0;
  GLuint m_vbo_uvs = 0;

  GLuint m_ibo_elements = 0;

  int m_triangleDrawSize = 0;

};
