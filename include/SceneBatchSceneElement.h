#pragma once


#include "SceneElement.h"
#include <map>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <graphics.h>


class RenderSystem;
class MeshBank;
class Palette;


// Kind of a replacement for render queue
class SceneBatch0 : public SceneElement
{
public:

  SceneBatch0();
  ~SceneBatch0();

  void setMesh(int) {} // dummy
  void setProgram(int) {} // dummy
  void setMVP(glm::mat4) {} // dummy
  void setDiffuse(glm::vec3) {} // dummy
  void setPallette(std::vector<int>&) {} // dummy

  // Remove everything from the batch
  void clear();

  // From SceneElement
  //void draw();

  // Execute the queued elements, in efficient order
  void draw(RenderSystem* rs, MeshBank* mb);

  // Generate Queues
  void setProgramName(std::string programName);

  void addElement(
    std::string meshID,
    glm::mat4 xform
  );

  int maskID = 0;
  void addElement(
    std::string meshID,
    glm::mat4 xform,
    Palette* palette
  );

  std::set<int>* renderMask = 0;

protected:

  // Info containing one instance of transform
  struct TransformInfo
  {
    glm::mat4 xform;
    //unsigned int attributeSetID = 0; // TODO
    Palette* palette = 0;
    int maskID = 0;
  };

  // A list of transform infos
  typedef std::list<TransformInfo> TransformList;

  // Map mesh index to all transforms used in this batch
  typedef std::map<std::string, TransformList> MeshList;

  // Map programs to mesh lists
  std::map<std::string, MeshList> m_programs;

  std::string m_currentProgramName = "Default";
};
