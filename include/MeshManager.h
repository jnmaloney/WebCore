#pragma once


#include "Mesh.h"
#include <vector>
#include <map>


class MeshManager
{
public:

  static MeshManager* get();

  MeshManager();
  ~MeshManager();

  void load();

  Mesh* getMesh(int index);

  int getMeshIndex(int code, int index);

  //void tick();

protected:

  std::vector<Mesh*> m_meshes;
  std::map<int, int> m_index;

};
