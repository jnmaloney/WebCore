#include "MeshBank.h"
#include <iostream>
#include <stdio.h>


MeshBank::MeshBank()
{
}


MeshBank::~MeshBank()
{
}


void MeshBank::add(std::string meshFileName, std::string textureFileName)
{
}


void MeshBank::add(std::string nameID, std::string meshFileName, std::string textureFileName)
{
  // Load mesh or get index
  if (m_meshFileIndex.find(meshFileName) == m_meshFileIndex.end())
  {
    m_geomData.push_back(NULL);
    m_meshFileIndex[meshFileName] = m_geomData.size() - 1;
  }

  // Load texture or get index
  if (m_textureFileIndex.find(textureFileName) == m_textureFileIndex.end())
  {
    m_textureData.push_back(NULL);
    m_textureFileIndex[textureFileName] = m_textureData.size() - 1;
  }

  // Use index to create mesh-texture pair
  m_meshObjects.push_back(
    std::make_pair(
      m_meshFileIndex[meshFileName],
      m_textureFileIndex[textureFileName]
    )
  );

  // Link the nameID to meshObjects index
  m_meshNames[nameID] = m_meshObjects.size() - 1;
}


void MeshBank::load()
{
  // Look for placeholders and perform full loading

  // Meshes
  for (auto i = m_meshFileIndex.begin(); i != m_meshFileIndex.end(); ++i)
  {
    if (m_geomData[i->second] == 0)
    {
      Mesh* mesh = new Mesh();
      std::cout << "Loading mesh " << i->first.c_str() << " to " << i->second << std::endl;
      mesh->load_obj(i->first.c_str());
      mesh->upload_obj();
      m_geomData[i->second] = mesh;
    }
  }

  // Textures
  for (auto i = m_textureFileIndex.begin(); i != m_textureFileIndex.end(); ++i)
  {
    if (m_textureData[i->second] == 0 && i->first.length() > 0)
    {
      Texture* texture = new Texture();
      texture->loadPng(i->first.c_str());
      m_textureData[i->second] = texture;
    }
  }
}


std::pair<Mesh*, Texture*> MeshBank::get(std::string id)
{
  size_t index = m_meshNames[id];
  std::pair<size_t, size_t> obj = m_meshObjects[index];
  //std::cout << "ID " << id.c_str() << " maps to " << index << std::endl;
  //std::cout << "ID " << id.c_str() << " maps to " << obj.first << std::endl;
  return std::make_pair(
    m_geomData[obj.first],
    m_textureData[obj.second]
  );
}
