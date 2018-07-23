#pragma once

#include "graphics.h"
#include <string>
#include <vector>
#include <map>


class Texture;


class Mesh
{

public:

  static GLuint attribute_v_normal;
  static GLuint attribute_v_coord;
  static GLuint attribute_v_uv;

  Mesh();
  ~Mesh();

  void load_obj(const char* filename);
  void upload_obj();

  void beSquare();

  // Submit to render queues
  void submitQueue();

  void draw(GLuint uniformDiffuse);
  void drawWireframe(GLuint uniformDiffuse = 0, int tag = 0);
  void draw_bbox();

  std::vector<glm::vec3> m_colours;


  //
  // Loading
  //

  //std::map< std::string,  >
  std::vector< std::string > m_uniqueVerts;
  int addUniqueVertex(std::string& vertexString); // Add or get the value
  std::vector<glm::vec4> m_vertP;
  std::vector<glm::vec3> m_vertN;
  std::vector<glm::vec2> m_vertT;

  std::vector<glm::vec4> m_obj_vertices;
  std::vector<glm::vec3> m_obj_normals;
  std::vector<glm::vec2> m_obj_uvs;
  //std::vector<GLushort> m_obj_elements;
  std::map< std::string, std::vector<GLushort> > m_matElements;

  std::string m_active;

  //
  // Rendering
  //

  GLuint m_vbo_normals = 0;
  GLuint m_vbo_vertices = 0;
  GLuint m_vbo_uvs = 0;
  //GLuint m_ibo_elements = 0;
  std::map< std::string, GLuint > m_matIboElements;


  Texture* texture = 0;

protected:

  // material mode
  void setColourSceme(int i);

  void setRenderColour(int i, GLuint uniformDiffuse = 0);



};
