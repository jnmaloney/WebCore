#pragma once

#include "Mesh.h"
#include <string>
#include <vector>
#include <map>


// OBJ-loading extensions for Mesh class
class Mesh_obj : public Mesh
{

public:

  Mesh_obj();
  ~Mesh_obj();

  void load_obj(const char* filename);
  
  void load_obj_data(const char* data, unsigned int size);
 
protected:
  void load_stream(std::istream& stream);
  int addUniqueVertex(std::string& vertexString); // Add or get the value
};
