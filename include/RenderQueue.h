#pragma once

#include "graphics.h"
#include <list>
#include <map>
#include <vector>


class Mesh;
class RenderSystem;


class  RenderQueue
{
public:

  RenderQueue();
  ~RenderQueue();

  // Execute the queued elements, in efficient order
  void draw(GLint uniformML, GLint uniformDiffuse, RenderSystem* rs);

  // Getting ready to submit
  void setProgram(GLint program);
  //void setMesh(Mesh* mesh);
  void setMesh(int meshIndex);
  void setMVP(glm::mat4 mvp);
  void setDiffuse(glm::vec3 d);
  void setPallette(std::vector<int> p);

  // Reset
  void clear();

  // Caputre the state of current drawing elements
  void submit();

protected:

  //typedef std::list<glm::mat4> TransformLevel;
  struct Transform
  {
    glm::mat4 x;
    glm::vec3 diffuse;
    bool setDiffuse = false;
    std::vector<int> pallette_id;
    bool setPallette = false;
  };
  Transform m_currentTransform;
  typedef std::list<Transform> TransformLevel;
  typedef std::map<Mesh*, TransformLevel> MeshLevel;
  typedef std::map<GLint, MeshLevel> ProgramLevel;
  ProgramLevel m_programs;

  MeshLevel* defaultMeshLevel = 0;
  TransformLevel* defaultTransformLevel = 0;

  MeshLevel* m_currentMeshLevel = defaultMeshLevel;
  TransformLevel* m_currentTransformLevel = defaultTransformLevel;
};
