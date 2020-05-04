#pragma once
#include <string>
#include <vector>
#include "graphics.h"
#include "WindowManager.h"
#include "ShaderManager.h"
#include "Mesh.h"
#include "Square.h"
#include "ViewFrustum.h"


// Controls the shaders and render loops
class RenderSystem
{

public:
  RenderSystem();
  ~RenderSystem();

  void init();

  void start();
  void end();

  void setClearColour(int r, int g, int b);
  void setClearColour(float r, float g, float b);

  void setProjectionOrtho(float x, float y, float w, float h);
  void setProjectionPerspective(float hfov_deg, float near = 1.0f, float far = 1.0e6f);
  void setCameraPos(const glm::vec3& pos, const glm::vec3& lookAt, const glm::vec3& up = glm::vec3(0, 0, 1));

  float* getViewProj();

  // Helpers for drawing
  void bindSquare(Square* mesh);
  void bindMesh(Mesh* mesh);
  void bindMeshElement(Mesh* mesh, int element);
  bool testModelLocal(const glm::mat4& transform);
  void setModelLocal(const glm::mat4& transform);
  void drawMesh(); //glm::mat4& transform);

  // The window that we render to
  WindowManager& m_window = *WindowManager::getInstance();

  // Shader collection
  ShaderManager m_shaderManager;

  // Useful
  glm::vec3 createRay(float mouseX, float mouseY);

  // Rendering / Shaders
  void setProgramVec3(glm::vec3& v);

  glm::vec3 getScreenPos(glm::vec3 pos);

protected:

  // Unused for now
  // unsigned int m_default_framebuffer = 0;

  // Size of current mesh index buffer
  unsigned int m_triangleDrawSize = 0;

  glm::mat4 Projection;
  glm::mat4 View;
  glm::mat4 ViewProj;
  glm::vec3 mCameraPos = glm::vec3(0.f);

  glm::vec3 mClearColour = glm::vec3(142.0/255.0, 47.0/255.0, 21.0/255.0);

  ViewFrustum m_frustum;

  // G-buffer
  //GLuint* m_colBuffer;
  //GLuint* m_norBuffer;
  //GLuint* m_posBuffer;
};
