#pragma once

#include "graphics.h"
#include <string>
#include <vector>
#include <map>


class Texture;
class RenderSystem;


class Pallette
{
public:
  Pallette() {}
  ~Pallette() {}
  std::vector<glm::vec3> colours;
};


struct MeshDef;


class Mesh
{

public:

  Mesh();
  ~Mesh();

  void load_obj(const char* filename);
  void upload_obj();

  void bind(RenderSystem* rs);

  void draw();
  void drawWireframe(GLuint uniformDiffuse = 0, int tag = 0);
  void draw_bbox();

  Texture* texture = 0;
  Pallette* pallette = 0;

protected:

  MeshDef* m_def;
public:
  GLuint m_vbo_normals = 0;
  GLuint m_vbo_vertices = 0;
  GLuint m_vbo_uvs = 0;;

  // ? ?
  struct IboElement
  {
    std::string name;
    int size = 0;
    int index = 0;
    GLuint elements;
  };
  std::map< int, IboElement > m_matIboElements;

  // Still have to factor out the unique verts v/t/n ourself
  std::vector< int > m_uniqueVerts;
  int encodeVert(int, int, int);
  void decodeVert(int, int&, int&, int&);
};
