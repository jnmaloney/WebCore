#pragma once


#include "Mesh.h"
#include "Texture.h"


class MeshBank
{
public:

  MeshBank();
  ~MeshBank();

  void add(std::string meshFileName, std::string textureFileName);
  void add(std::string nameID, std::string meshFileName, std::string textureFileName);

  // Load queued files
  void load();

  std::pair<Mesh*, Texture*> get(std::string id);

protected:

  // Mesh Geometry
  std::map<std::string, size_t> m_meshFileIndex;
  std::vector<Mesh*> m_geomData;

  // Tecture files
  std::map<std::string, size_t> m_textureFileIndex;
  std::vector<Texture*> m_textureData;

  // Object made of mesh-tecture pair
  std::vector< std::pair<size_t, size_t> > m_meshObjects;

  // Nicknames for mesh id's
  std::map< std::string, size_t > m_meshNames;
};
