#pragma once

#include "Mesh.h"
#include <string>
#include <vector>
#include <map>


// Modified OBJ-loading extensions for Mesh class
class Mesh_pile : public Mesh
{

public:

  Mesh_pile();
  ~Mesh_pile();

  void load_obj(const char* filename);
  
  void load_obj_data(const char* data, unsigned int size);
 
protected:
  void load_stream(std::istream& stream);
};
