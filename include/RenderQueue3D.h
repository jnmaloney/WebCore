#pragma once

#include "graphics.h"
#include <list>
#include <map>
#include <vector>


class RenderSystem;
class Mesh;


class  RenderQueue3D
{
public:

  RenderQueue3D();
  ~RenderQueue3D();

  // Execute the queued elements, in efficient order
  void draw(RenderSystem* rs);

  // Getting ready to submit
  void setMVP(glm::mat4 mvp);
  void setMesh(Mesh* mesh);

  // Reset
  void clear();

  // Caputre the state of current drawing elements
  void submit();

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

  std::list<Transform> m_transforms;

  Mesh* m_mesh;
};
