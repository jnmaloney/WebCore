#include "SceneBatch.h"
#include "RenderSystem.h"
#include "MeshBank.h"
#include <stdio.h>
#include <iostream>


SceneBatch::SceneBatch()
{

}


SceneBatch::~SceneBatch()
{

}


void SceneBatch::clear()
{
  // TODO
  m_programs.clear();
}


void SceneBatch::setProgramName(std::string programName)
{

}


void SceneBatch::addElement(std::string meshID, glm::mat4 xform, unsigned int attributeSetID)
{
  m_programs[m_currentProgramName][meshID].push_back(
    (TransformInfo)
    {
      xform, attributeSetID
    }
  );
}


void SceneBatch::draw(RenderSystem* rs, MeshBank* mb)
{
  // Each shader program in the queue
  for (auto a : m_programs)
  {
    // Each draw list for the shader program
    for (auto b : a.second)
    {
      // Get the mesh information for this draw list
      std::string id = b.first;
      TransformList xformList = b.second;
      auto c = mb->get(id);

      Mesh* mesh = c.first;
      Texture* texture = c.second;

      rs->bindMesh(mesh);
      if (texture) texture->bind();
      else glBindTexture(GL_TEXTURE_2D, 0);

      // Each sub-element of the mesh
      for (int i = 0; i < mesh->m_matIboElements.size(); ++i)
      {
        // Bind sub-mesh
        rs->bindMeshElement(mesh, i);

        // Each transform for this mesh
        for (auto xform : xformList)
        {
          rs->drawMesh(xform.xform);
        }
      }
    }
  }
}
