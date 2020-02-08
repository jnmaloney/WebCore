#include "SceneBatchSceneElement.h"
#include "RenderSystem.h"
#include "MeshBank.h"
#include <stdio.h>
#include <iostream>
#include "Palette.h"


SceneBatch0::SceneBatch0()
{
  DRAW_ELEMENT = true;
}


SceneBatch0::~SceneBatch0()
{

}


void SceneBatch0::clear()
{
  // TODO
  m_programs.clear();
}


void SceneBatch0::setProgramName(std::string programName)
{

}


void SceneBatch0::addElement(std::string meshID, glm::mat4 xform)
{
  m_programs[m_currentProgramName][meshID].push_back(
    (TransformInfo)
    {
      xform, NULL, maskID
    }
  );
}


void SceneBatch0::addElement(std::string meshID, glm::mat4 xform, Palette* palette)
{
  m_programs[m_currentProgramName][meshID].push_back(
    (TransformInfo)
    {
      xform, palette, maskID
    }
  );
}


void SceneBatch0::draw(RenderSystem* rs, MeshBank* mb)
{
  glm::vec3 defaultColour = glm::vec3(1);
  rs->setProgramVec3(/*"diffuse", */defaultColour);

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
          // Check the 'id-flag' of this element against our draw mask
          if (renderMask && renderMask->count(xform.maskID)) // TODO contains c++20
            continue;

          // Perform a cull test before setting shader vars
          if (rs->testModelLocal(xform.xform))
          {
            // Set diffuse colour for this submesh
            // TODO - should be optional - ?
            if (xform.palette)
              rs->setProgramVec3(/*"diffuse", */xform.palette->getAt(i));
            else
              rs->setProgramVec3(/*"diffuse", */defaultColour);

            // Draw the mesh
            rs->drawMesh();
          }
        }
      }
    }
  }
}
