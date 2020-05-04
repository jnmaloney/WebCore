#pragma once

#include "Mesh.h"
#include <string>
#include <vector>
#include <map>


class Mesh_obj : public Mesh
{

public:

  Mesh_obj();
  ~Mesh_obj();

  void load_obj(const char* filename);
 
protected:
  int addUniqueVertex(std::string& vertexString); // Add or get the value



};
