#include "RenderSystem.h"
#include "shaders.h"
#include "Mesh.h"
#include <iostream>


RenderSystem::RenderSystem()
{
}


RenderSystem::~RenderSystem()
{


}


void RenderSystem::init()
{
  // GL Setup
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  // Shaders
  m_shaderManager.loadProgram(
    "Default",
    "data/shaders/base.vert",
    "data/shaders/base.frag"
  );
}


void RenderSystem::start()
{
  //glClearColor(0.f, 92.f / 255.f, 159.f / 255.f, 1.f); // "Skydiver"
  glClearColor(142.0/255.0, 47.0/255.0, 21.0/255.0, 1.0); // "Autumn"
  glViewport(0, 0, m_window.width, m_window.height);
  glClear( GL_COLOR_BUFFER_BIT );

  glDepthFunc(GL_LESS);
  //glDisable(GL_DEPTH_TEST);

  m_shaderManager.update(this);
}


void RenderSystem::setProjectionPerspective(float hfov_deg, float near, float far)
{
  //
  // Compute Proj matrix
  //
  float aspect = (float)m_window.width / (float)m_window.height;
  float hfov = glm::radians(hfov_deg);
  Projection = glm::perspective(
    hfov,
    aspect,
    near,
    far
  );

  //
  // Set frustum details
  //
  m_frustum.setCamInternals(
    hfov,
    aspect,
    near,
    far
  );

  ViewProj = Projection * View;
}


void RenderSystem::setCameraPos(const glm::vec3& pos, const glm::vec3& lookAt, const glm::vec3& up)
{
  //
  // Compute View matrix
  //
  View = glm::lookAt(
                pos,
                lookAt,
                up
               );
   //
   // Set frustum details
   //
   m_frustum.setCamDef(
    pos,
    lookAt,
    up
   );

 //
 // Set ViewProj
 //
  ViewProj = Projection * View;
}


void RenderSystem::end()
{
}


float* RenderSystem::getViewProj()
{
  return &ViewProj[0][0];
}


void RenderSystem::bindMesh(Mesh* mesh)
{
  GLuint attribute_v_coord = m_shaderManager.getAttribute("attribute_v_coord");
  GLuint attribute_v_uv = m_shaderManager.getAttribute("attribute_v_uv");

  // Vertex position
  glEnableVertexAttribArray(attribute_v_coord);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vbo_vertices); // TODO
  glVertexAttribPointer(
    attribute_v_coord,  // attribute
    4,                  // number of elements per vertex, here (x,y,z,w)
    GL_FLOAT,           // the type of each element
    GL_FALSE,           // take our values as-is
    0,                  // no extra data between each position
    0                   // offset of first element
  );

  // Vertex UV
  glEnableVertexAttribArray(attribute_v_uv);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vbo_uvs); // TODO
  glVertexAttribPointer(
    attribute_v_uv,     // attribute
    2,                  // number of elements per vertex, here (x,y,z)
    GL_FLOAT,           // the type of each element
    GL_FALSE,           // take our values as-is
    0,                  // no extra data between each position
    0                   // offset of first element
  );

  // Vertex normal
  // TODO

  // Set element 0
  //bindMeshElement(0);
}


void RenderSystem::bindMeshElement(Mesh* mesh, int element)
{
  // Element indices (one submesh)
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_matIboElements[element].elements);
  m_triangleDrawSize = mesh->m_matIboElements[element].size;
}


bool RenderSystem::testModelLocal(glm::mat4& transform)
{
  // Frustum test first
  glm::vec3 p = glm::vec3(transform[3]);
  if (m_frustum.testSphere(p, 1.0f) < 0) return false;

  // TODO
  static GLuint uniformML = m_shaderManager.getAttribute("uniformML");

  // Transform Model-Local
  glUniformMatrix4fv(uniformML, 1, GL_FALSE, &transform[0][0]);

  return true;
}


void RenderSystem::drawMesh() //glm::mat4& transform)
{
  // Draw call (one submesh)
  glDrawElements(GL_TRIANGLES, m_triangleDrawSize, GL_UNSIGNED_SHORT, 0);
}


glm::vec3 RenderSystem::createRay(float mouseX, float mouseY)
{
    // these positions must be in range [-1, 1], not [0, width] and [0, height]
    mouseX = 2.f * mouseX / m_window.width - 1.f;
    mouseY = 2.f * mouseY / m_window.height - 1.f;

    glm::mat4 invVP = glm::inverse(ViewProj);
    glm::vec4 screenPos = glm::vec4(mouseX, -mouseY, 1.0f, 1.0f);
    glm::vec4 worldPos = invVP * screenPos;

    //return glm::normalize(glm::vec3(worldPos));
    return glm::vec3(worldPos);
}


void RenderSystem::setProgramVec3(glm::vec3& v)
{
  m_shaderManager.setProgramVec3(v);
}


glm::vec3 RenderSystem::getScreenPos(glm::vec3 pos)
{
  //return ViewProj * glm::vec4(pos, 1.f);
  return glm::project(pos, glm::mat4(1.0), ViewProj, m_window.getViewport());
}
