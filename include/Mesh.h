#pragma once

#include "graphics.h"
#include <string>
#include <vector>
#include <map>


class Texture;


class Mesh
{

public:

  Mesh();
  ~Mesh();

  //
  // Submit to render queues
  //
  void submitQueue();

  //
  // Loading
  //

  std::vector< std::string > m_uniqueVerts;
  int addUniqueVertex(std::string& vertexString); // Add or get the value
  std::vector<glm::vec4> m_vertP;
  std::vector<glm::vec3> m_vertN;
  std::vector<glm::vec2> m_vertT;

  std::vector<glm::vec4> m_obj_vertices;
  std::vector<glm::vec3> m_obj_normals;
  std::vector<glm::vec2> m_obj_uvs;
  std::map< std::string, std::vector<GLushort> > m_matElements;

  std::string m_active;

  //
  // Converting
  //
  void upload();


  //
  // Rendering
  //

  GLuint m_vbo_normals = 0;
  GLuint m_vbo_vertices = 0;
  GLuint m_vbo_uvs = 0;

  // This gets sent to the render queue
  struct IboElement
  {
    std::string name;
    int size = 0;
    int index = 0;
    GLuint elements;
  };
  std::map< int, IboElement > m_matIboElements;

  Texture* texture = 0;

protected:


};
