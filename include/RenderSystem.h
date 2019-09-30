#pragma once
#include <string>
#include <vector>
#include "graphics.h"
#include "WindowManager.h"
#include "ShaderManager.h"
#include "Mesh.h"
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

    void setViewSettings(double hfov, double near = 1.0, double far = 1.0e6);

    void setCameraPos(float x, float y, float z);
    void setCameraPos(const glm::vec3& pos);
    void setCameraTarget(float x, float y, float z);

    bool enableVertexPos(GLint program);
    bool enableVertexUV(GLint program);

    // Move mouse cursor
    void setCursor(int x, int y);
    float m_cursorX = 0.f;
    float m_cursorY = 0.f;

    void modeOrtho();
    void modeOrtho(float x, float y);
    void modeOrtho(float x, float y, float w, float h);
    void modePersp();

  void setProjectionPerspective(float hfov_deg, float near = 1.0f, float far = 1.0e6f);
  void setCameraPos(const glm::vec3& pos, const glm::vec3& lookAt, const glm::vec3& up = glm::vec3(0, 0, 1));

  float* getViewProj();

  // New drawing scheme
  void bindMesh(Mesh* mesh);
  void bindMeshElement(Mesh* mesh, int element);
  void drawMesh(glm::mat4& transform);

  /*
    Non-UBO uniform updates
    Vertex buffer bindings (without changing formats)
    UBO binding
    Vertex format changes
    Texture bindings
    Fragment post-processing state changes
    Shader program changes
    Render target switches
  */
    // shader program
    // : vertex id
    // : normals id
    // : uv
    // : texture
    // MVP value (uniform)
    // Colour value (uniform)
    // Elements

  void move(double, double);

  // Camera move callback
  void zoom(int);
  GLint uniformML;
  GLint uniformVP;

  // Vars
  long m_shader;
  GLuint programObject; // 1 Texture
  GLuint programObject2; // dummy

  // View settings
  double m_cameraX = 0.0;
  double m_cameraY = 0.0;
  int m_zoomFactor = 3;
  float m_zoom = 0.5 + 0.5 * (1<<3);

  // The window that we render to
  WindowManager& m_window = *WindowManager::getInstance();

  // Shader collection
  ShaderManager m_shaderManager;

  // Uniforms NEW
  GLint attribute_v_coord;
  GLint attribute_v_uv;


protected:

  unsigned int m_default_framebuffer = 0;
  unsigned int m_triangleDrawSize = 0;

  glm::mat4 Projection;
  glm::mat4 View;
  glm::mat4 ViewProj;
  glm::vec3 mCameraPos = glm::vec3(0.f);

  ViewFrustum m_frustum;
};
