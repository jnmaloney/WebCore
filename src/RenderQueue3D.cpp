#include "RenderQueue3D.h"
#include "Mesh.h"
#include <iostream>
#include "Texture.h"
#include "RenderSystem.h"


RenderQueue3D::RenderQueue3D()
{
}


RenderQueue3D::~RenderQueue3D()
{

}


void RenderQueue3D::clear()
{
  m_transforms.clear();
}


void RenderQueue3D::setMVP(glm::mat4 mvp)
{
  Transform t;
  t.x = mvp;
  m_transforms.push_back(t);
}

void RenderQueue3D::setMesh(Mesh* mesh)
{
  m_mesh = mesh;
}


void RenderQueue3D::submit()
{
}


void RenderQueue3D::draw(RenderSystem* rs)
{
  // TODO
  /*
  m_mesh->upload_obj();
  m_mesh->bind(rs);

  // For each transform
  for (auto const t : m_transforms)
  {
    // Set the local transform matrix
    glUniformMatrix4fv(rs->uniformML, 1, GL_FALSE, &t.x[0][0]);

    //
    //              ----     DRAW     ----
    //
    m_mesh->draw();
  }
  */
}
