#include "RenderSystem.h"
#include "shaders.h"
#include "Mesh.h"
#include <iostream>


RenderSystem::RenderSystem()
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


RenderSystem::~RenderSystem()
{


}


void RenderSystem::zoom(int i)
{
}


void RenderSystem::move(double x, double y)
{

}


void RenderSystem::setCameraPos(float x, float y, float z)
{
  mCameraPos.x = x;
  mCameraPos.y = y;
  mCameraPos.z = z;
}


void RenderSystem::setCameraPos(const glm::vec3& pos)
{
  mCameraPos = pos;
}


void RenderSystem::setCameraTarget(float x, float y, float z)
{

}


void RenderSystem::setViewSettings(double hfov, double near, double far)
{

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


void RenderSystem::modePersp()
{
  glm::mat4 VP(1.0);
  //VP = glm::perspective( 15.f, 640.f / 576.f, 0.1f, 10.f );
  // Camera View matrix
  View = glm::lookAt(
                //glm::vec3(mCameraPos.x, mCameraPos.y - 15.f, mCameraPos.z + 20.f), // Camera in World Space
                glm::vec3(mCameraPos.x + 5.f, mCameraPos.y + 5.f, mCameraPos.z + 20.f), // Camera in World Space
                glm::vec3(mCameraPos.x,  mCameraPos.y, mCameraPos.z), // looks at
                glm::vec3(0, 0, 1)  // Head is up (set to 0,-1,0 to look upside-down)
               );

  // Calculate ViewProj
  //glm::mat4 Projection = glm::perspective( 1.f, 640.f / 576.f, 0.1f, 10000.f );
  float aspect = (float)m_window.width / (float)m_window.height;
  glm::mat4 Projection2 = glm::perspective(
    1.f,
    aspect,
    0.1f,
    10000.f );
  VP = Projection2 * View;

  //glUniformMatrix4fv(uniformVP, 1, GL_FALSE, &VP[0][0]); // TODO ?
  Projection = VP; // save to member var
  m_shaderManager.update(this);


  //
  // Set frustum details
  //
  m_frustum.setCamInternals(
    1.f,
    aspect,
    0.1f,
    10000.f
  );

  m_frustum.setCamDef(
    glm::vec3(mCameraPos.x + 5.f, mCameraPos.y + 5.f, mCameraPos.z + 20.f), // Camera in World Space
    glm::vec3(mCameraPos.x,  mCameraPos.y, mCameraPos.z), // looks at
    glm::vec3(0, 0, 1)  // Head is up (set to 0,-1,0 to look upside-down)
  );


  //
  // Calculate Cursor Pos
  //
  glm::vec3 m_start;
  glm::vec3 m_end;
  glm::ivec4 viewport(0, 0, m_window.width, m_window.height);

  // window pos of mouse, Y is inverted on Windows
  glm::vec3 win((double)m_window.mousex, (double)(m_window.height - m_window.mousey), 0.0);

  // get point on the 'near' plane (third param is set to 0.0)
  m_start = glm::unProject(win, View, Projection, viewport);

  // get point on the 'far' plane (third param is set to 1.0)
  win.z = 1.0;
  m_end = glm::unProject(win, View, Projection, viewport);

  // now you can create a ray from m_start to m_end

  // Calculate some intersection point

  glm::vec3 m_dir = m_end - m_start;
  //(m_start + a * m_dir).z = 0;
  float a = m_dir.z == 0 ? 0 :
            -m_start.z / m_dir.z;
  m_cursorX = m_start.x + a * m_dir.x;
  m_cursorY = m_start.y + a * m_dir.y;
}


void RenderSystem::modeOrtho()
{
  glm::mat4 VP(1.0);
  VP = glm::ortho( 0.f, 1.f, 1.f, 0.f, -10.f, 10.f );

  glUniformMatrix4fv(uniformVP, 1, GL_FALSE, &VP[0][0]);
}


void RenderSystem::modeOrtho(float x, float y)
{
  glm::mat4 VP(1.0);
  VP = glm::ortho( 0.f, x, y, 0.f, -10.f, 10.f );

  glUniformMatrix4fv(uniformVP, 1, GL_FALSE, &VP[0][0]);
}


void RenderSystem::modeOrtho(float x, float y, float w, float h)
{
  glm::mat4 VP(1.0);
  VP = glm::ortho( x, x+w, y+h, y, -10.f, 10.f );

  glUniformMatrix4fv(uniformVP, 1, GL_FALSE, &VP[0][0]);
}


void RenderSystem::end()
{
}


void RenderSystem::setCursor(int x, int y)
{

}


bool RenderSystem::enableVertexPos(GLint program)
{
  if (program == programObject)
  {
      glEnableVertexAttribArray(attribute_v_coord);
      return true;
  }

  return false;
}


bool RenderSystem::enableVertexUV(GLint program)
{
  if (program == programObject)
  {
      glEnableVertexAttribArray(attribute_v_uv);
      return true;
  }

  return false;
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


void RenderSystem::drawMesh(glm::mat4& transform)
{
  // Frustum test first
  glm::vec3 p = glm::vec3(transform[3]);
  //glm::vec3 p(0.f);
  //std::cout << p.x << " " << p.y << " " << p.z << " " << m_frustum.testSphere(p, 0.0f) << std::endl;
  //std::cout << p.x << " " << p.y << " " << p.z << " " << m_frustum.pl[1].distance(p) << std::endl;

  if (m_frustum.testSphere(p, 1.0f) < 0) return;

  GLuint uniformML = m_shaderManager.getAttribute("uniformML");

  // Transform Model-Local
  glUniformMatrix4fv(uniformML, 1, GL_FALSE, &transform[0][0]);

  // Draw call (one submesh)
  glDrawElements(GL_TRIANGLES, m_triangleDrawSize, GL_UNSIGNED_SHORT, 0);
}
