#pragma once

#include "graphics.h"
#include <list>
#include <map>


class Mesh;


class  RenderQueue
{
public:

  RenderQueue();
  ~RenderQueue();

  // Execute the queued elements, in efficient order
  void draw(GLint uniformML, GLint uniformDiffuse);

  // Getting ready to submit
  void setProgram(GLint program);
  void setMesh(Mesh* mesh);
  void setMVP(glm::mat4 mvp);

  // Reset
  void clear();

  // Caputre the state of current drawing elements
  void submit();

protected:

  //typedef std::list<glm::mat4> TransformLevel;
  // typedef std::pair<Mesh*, std::list<glm::mat4> > MeshLevel;
  // typedef std::pair<GLUint, std::list<MeshLevel> > ProgramLevel;
  // std::list<ProgramLevel> m_programs;

  typedef std::list<glm::mat4> TransformLevel;
  typedef std::map<Mesh*, TransformLevel> MeshLevel;
  typedef std::map<GLint, MeshLevel> ProgramLevel;
  ProgramLevel m_programs;


  MeshLevel* defaultMeshLevel = 0;
  TransformLevel* defaultTransformLevel = 0;

  MeshLevel* m_currentMeshLevel = defaultMeshLevel;
  TransformLevel* m_currentTransformLevel = defaultTransformLevel;


};
